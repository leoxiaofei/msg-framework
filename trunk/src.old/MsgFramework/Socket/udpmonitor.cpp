#include "stdafx.h"
#include "udpmonitor.h"

#include "udppacket.h"
#include "rcvdudppacket.h"
#include "udpsession.h"
#include "../Tools/msgobjectpool.hpp"

#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/ip/udp.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <assert.h>
#include <unordered_map>
#include <iosfwd>
#include "msgsignals.h"
#include "../Common/vcpool.h"
#include "../Common/HostManager.h"
#include "../Common/HostInfo.h"

using namespace boost::asio;
using namespace boost::signals2;
using boost::system::error_code;
using std::tr1::shared_ptr;

typedef std::map<unsigned int, UdpSession* >  MapSession;

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

	MsgSignals udpSig;

	MapSession mapSession;

	MsgObjectPool<UdpPacket> mopPackPool;
	MsgObjectPool<UdpSession> mopSession;
};

UdpMonitor::UdpMonitor( boost::asio::io_service& io )
: m_pImpl(new Impl(io))
{
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
	//////////////////////////////////////////////////////////////////////////
	///接收消息
	HostInfo* pInfo = HostManager::Instance().TakeHost(m_pImpl->epReceive.address().to_string(), 
		m_pImpl->epReceive.port(), HostManager::TT_UDP);
	UdpSession* pSession = FindSession(pInfo->uHostId);
	if (!pSession)
	{
		pSession = CreateSession(pInfo);
	}

	pSession->ReceiveData(m_pImpl->arBuffer.data(), packet_bytes);
	//////////////////////////////////////////////////////////////////////////
	ReadyRead();
}



void UdpMonitor::SendTo( unsigned int uOrder, std::vector<char>* ptData, unsigned int uHostId)
{
	const char* szData = ptData->data();
	std::size_t uSize = ptData->size();

	//////////////////////////////////////////////////////////////////////////
	///发送消息
	UdpSession* pSession = FindSession(uHostId);
	if (!pSession)
	{
		HostInfo* pHostInfo = HostManager::Instance().FindHost(uHostId);
		pSession = CreateSession(pHostInfo);
	}

	pSession->SendData(uOrder, szData, uSize);
	//////////////////////////////////////////////////////////////////////////
	VcPool::Instance().Recycle(ptData);
}



void UdpMonitor::Broadcast( std::vector<char>* ptData,
	const boost::asio::ip::udp::endpoint& point )
{
	const char* szData = ptData->data();
	std::size_t uSize = ptData->size();
	assert(uSize < SPLIT_SIZE);
	UdpPacket* pData = m_pImpl->mopPackPool.New();
	if (pData == NULL)
	{
		pData = new UdpPacket;
	}
	pData->uOrder = 0;
	pData->uCurrent = 1;
	pData->uTotal = 1;
	pData->uUsed = uSize;
	memcpy_s(pData->szData, SPLIT_SIZE, szData, uSize);
	BroadcastPacket(pData, point);
	VcPool::Instance().Recycle(ptData);
}

void UdpMonitor::BroadcastPacket( UdpPacket* packet, const boost::asio::ip::udp::endpoint& point )
{
	m_pImpl->ptSock->async_send_to(buffer((void*)packet, packet->uUsed + 10), point,
		boost::bind(&UdpMonitor::BroadcastHandler, this, placeholders::error));
	m_pImpl->mopPackPool.Recycle(packet);
}

void UdpMonitor::BroadcastHandler( const boost::system::error_code& ec)
{
}

void UdpMonitor::SendPacket( UdpPacket* packet, const boost::asio::ip::udp::endpoint& point )
{
	m_pImpl->ptSock->async_send_to(buffer((void*)packet, packet->uUsed + 10), point,
		boost::bind(&UdpMonitor::SendToHandler, this, placeholders::error));
}

void UdpMonitor::SendToHandler( const boost::system::error_code& ec )
{
	if (ec)
	{
		return;
	}
	ec;
}

UdpSession* UdpMonitor::FindSession(unsigned int uHostId)
{
	UdpSession* pSession(NULL);
	MapSession::iterator iFind = m_pImpl->mapSession.find(uHostId);
	if (iFind != m_pImpl->mapSession.end())
	{
		pSession = iFind->second;
	}
	return pSession;
}

UdpSession* UdpMonitor::CreateSession(const HostInfo* pHostInfo)
{
	UdpSession* pSession = m_pImpl->mopSession.New();
	if (!pSession)
	{
		pSession = new UdpSession(m_pImpl->mopPackPool);
		pSession->SetSendFunc(boost::bind(&UdpMonitor::SendPacket, this, _1, _2));
		pSession->SetReceiveFunc(boost::bind(&UdpMonitor::ReceiveData, this, _1, _2));
		pSession->SetResultFunc(boost::bind(&UdpMonitor::SendResult, this, _1, _2));
	}

	ip::udp::endpoint senderEndpoint(ip::address_v4::from_string(pHostInfo->strIp), pHostInfo->uPort);
	pSession->SetEndPoint(senderEndpoint, pHostInfo->uHostId);
	m_pImpl->mapSession[pHostInfo->uHostId] = pSession;
	return pSession;
}



MsgSignals* UdpMonitor::GetSignals()
{
	return &m_pImpl->udpSig;
}

void UdpMonitor::ReceiveData( std::vector<char>* ptData, unsigned int uHostId)
{
	m_pImpl->udpSig.EmitReceive(uHostId, ptData);
}

boost::asio::io_service& UdpMonitor::GetIOs()
{
	return m_pImpl->ios;
}

void UdpMonitor::SendResult(unsigned int uOrder, int nResultFlag)
{
	m_pImpl->udpSig.EmitSendResult(uOrder, nResultFlag);
}




// signal<void(unsigned int, unsigned int)>* UdpMonitor::sg_SendError()
// {
// 	return &m_pImpl->sigSendError;
// }

// signal<void(unsigned int, shared_ptr<std::stringstream>)>* UdpMonitor::sg_ReceiveData()
// {
// 	return &m_pImpl->sigReceiveData;
// }

