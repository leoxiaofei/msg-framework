#include "stdafx.h"
#include "udpmonitor.h"

#include "common/udppacket.h"
#include "common/rcvdudppacket.h"
#include "MsgObjectPool.hpp"

#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/ip/udp.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <assert.h>

using namespace boost::asio;
using namespace boost::signals2;
using boost::system::error_code;
using std::tr1::shared_ptr;

class UdpMonitor::Impl
{
public:
	Impl(io_service& io)
		: ios(io)
	{}

	io_service& ios;
	ip::udp::endpoint epReceive;
	shared_ptr<ip::udp::socket> ptSock;
	std::tr1::array<char, 1024> arBuffer;

	signal<void(unsigned int, unsigned int)> sigSendError;
	signal<void(unsigned int, std::tr1::shared_ptr<std::stringstream>)> sigReceiveData;
	
	std::map<unsigned int, unsigned int> mapTimeOut;
	std::map<unsigned int, std::queue<UdpPacket*> > mapReadyData;
	MsgObjectPool<UdpPacket> mopPackPool;
	
	std::map<unsigned int, RcvdUdpPacket> mapReceiveData;
};

UdpMonitor::UdpMonitor( boost::asio::io_service& io )
: m_pImpl(new Impl(io))
{
	Listen();
}

UdpMonitor::~UdpMonitor( void )
{

}


bool UdpMonitor::Listen(unsigned short uPort)
{
	bool bRet(false);
	try
	{
		m_pImpl->ptSock = shared_ptr<ip::udp::socket>
			(new ip::udp::socket(m_pImpl->ios, ip::udp::endpoint(ip::udp::v4(), uPort)));
		m_pImpl->ptSock->set_option(socket_base::broadcast(true));
		m_pImpl->ptSock->set_option(ip::udp::socket::reuse_address(true));
		ReadyRead();
		bRet = true;
	}
	catch (boost::system::system_error& e)
	{
	}
	catch (...)
	{
	}

	return bRet;
}

void UdpMonitor::ReadyRead()
{
	m_pImpl->ptSock->async_receive_from(buffer(m_pImpl->arBuffer), m_pImpl->epReceive,
		boost::bind(&UdpMonitor::ReadHandler, this, placeholders::error, placeholders::bytes_transferred));
}

void UdpMonitor::ReadHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		return;
	}

	UdpPacket* pData = m_pImpl->mopPackPool.New();
	if (pData == NULL)
	{
		pData = new UdpPacket;
	}
	memcpy_s(pData, sizeof(UdpPacket), m_pImpl->arBuffer.data(), packet_bytes);
	do
	{
		if(!CheckPacket(pData))
		{
			break;
		}

		if ( pData->uUsed == 0 ) ///应答包
		{
			std::map<unsigned int, std::queue<UdpPacket*> >::iterator
				iFind = m_pImpl->mapReadyData.find(pData->uOrder);
			
			if ( iFind != m_pImpl->mapReadyData.end() )
			{
				UdpPacket* p = iFind->second.front();
				if (   p->uCurrent == pData->uCurrent 
					&& p->uTotal == pData->uTotal )
				{
					iFind->second.pop();
					m_pImpl->mopPackPool.Recycle(p);

					if (!iFind->second.empty())
					{
						///存在下一个数据
						SendPacket(iFind->second.front(), m_pImpl->epReceive);
					}
					else
					{
						m_pImpl->mapReadyData.erase(iFind);
					}
				}
			}
		}
		else  ///数据包
		{
			///保存数据
			std::map<unsigned int, RcvdUdpPacket>::iterator iFind = 
				m_pImpl->mapReceiveData.find(pData->uOrder);
			if(iFind == m_pImpl->mapReceiveData.end())
			{
				///新数据
				if (pData->uCurrent != 1)
				{
					break;
				}
				RcvdUdpPacket& rPacket = m_pImpl->mapReceiveData[pData->uOrder];
				rPacket.uCurrent = pData->uCurrent;
				rPacket.uTotal   = pData->uTotal;
				rPacket.ptStream->write((char*)pData->szData, pData->uUsed);
			}
			else
			{
				///后续数据
				RcvdUdpPacket& rPacket = iFind->second;
				if (pData->uTotal != rPacket.uTotal)
				{
					break;
				}
				if (rPacket.uCurrent < pData->uCurrent)
				{
					assert(rPacket.uCurrent + 1 == pData->uCurrent);
					rPacket.uCurrent = pData->uCurrent;
					rPacket.ptStream->write((char*)pData->szData, pData->uUsed);
				}
			}
			CheckEmitReceive(pData->uOrder);
			///发送应答消息
			pData->uUsed = 0;
			SendPacket(pData, m_pImpl->epReceive);
		}
	}while(0);

	m_pImpl->mopPackPool.Recycle(pData);
	ReadyRead();
}

void UdpMonitor::Broadcast(void* szData, unsigned int uSize, unsigned short uPort)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
	m_pImpl->ptSock->async_send_to(buffer(szData, uSize), senderEndpoint,
		boost::bind(&UdpMonitor::BroadcastHandler, this, placeholders::error));
}

void UdpMonitor::BroadcastHandler( const boost::system::error_code& ec)
{
}

void UdpMonitor::SendTo(unsigned int uOrder, void* szData, unsigned int uSize, 
					   const std::string& strAddr, unsigned short uPort /*= 2425*/ )
{

	ip::udp::endpoint senderEndpoint(ip::address_v4::from_string(strAddr), uPort);
	m_pImpl->ios.post(boost::bind(&UdpMonitor::As_SendTo, this,
		uOrder, buffer(szData, uSize), senderEndpoint));
}

void UdpMonitor::SendToHandler( const boost::system::error_code& ec )
{
	if (ec)
	{
		return;
	}
	ec;
}



void UdpMonitor::SplitPacket( unsigned int uOrder, void* szData, 
	unsigned int uSize, std::queue<UdpPacket*>& queData )
{
	unsigned int uPos(0);
	unsigned int uCopy(0);
	unsigned int uTotal = uSize / SPLIT_SIZE + 1;
	unsigned int uCurrent(0);

	do 
	{
		UdpPacket* pData = m_pImpl->mopPackPool.New();
		if (pData == NULL)
		{
			pData = new UdpPacket;
		}

		pData->uOrder = uOrder;
		pData->uCurrent = ++uCurrent;
		pData->uTotal = uTotal;
		uCopy = uTotal == uCurrent ? uSize - uPos: SPLIT_SIZE;
		pData->uUsed = uCopy;
		memcpy_s(pData->szData, SPLIT_SIZE, (unsigned char*)szData + uPos, uCopy);
		uPos += uCopy;

		queData.push(pData);

	} while (uPos < uSize);

}

void UdpMonitor::As_SendTo( unsigned int uOrder,
	const boost::asio::mutable_buffers_1& buf, 
	const boost::asio::ip::udp::endpoint& point )
{
	std::size_t s1 = boost::asio::buffer_size(buf);
	void* p1 = boost::asio::buffer_cast<void*>(buf);
	std::queue<UdpPacket*>& queData = m_pImpl->mapReadyData[uOrder];
	SplitPacket(uOrder, p1, s1, queData);

	SendPacket(queData.front(), point);
}

bool UdpMonitor::CheckPacket( UdpPacket* packet )
{
	bool bRet(false);

	do 
	{
		if (   packet->uOrder == 0
			|| packet->uTotal == 0
			|| packet->uCurrent == 0 )
		{
			break;
		}

		if ( packet->uCurrent > packet->uTotal )
		{
			break;
		}

		if ( packet->uUsed > SPLIT_SIZE )
		{
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

void UdpMonitor::SendPacket( UdpPacket* packet, const boost::asio::ip::udp::endpoint& point )
{
	m_pImpl->ptSock->async_send_to(buffer((void*)packet, packet->uUsed + 10), point,
		boost::bind(&UdpMonitor::SendToHandler, this, placeholders::error));
}

signal<void(unsigned int, unsigned int)>* UdpMonitor::sg_SendError()
{
	return &m_pImpl->sigSendError;
}

// signal<void(unsigned int, shared_ptr<std::stringstream>)>* UdpMonitor::sg_ReceiveData()
// {
// 	return &m_pImpl->sigReceiveData;
// }

void UdpMonitor::CheckEmitReceive( unsigned int uOrder )
{
	std::map<unsigned int, RcvdUdpPacket>::iterator iFind = 
		m_pImpl->mapReceiveData.find(uOrder);
	if(iFind != m_pImpl->mapReceiveData.end())
	{
		RcvdUdpPacket& rPacket = iFind->second;
		if (rPacket.uCurrent == rPacket.uTotal)
		{
			m_pImpl->sigReceiveData(uOrder, rPacket.ptStream);
			//m_pImpl->sigSendError(0,1);
			m_pImpl->mapReceiveData.erase(iFind);
		}
	}
}
