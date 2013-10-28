#include "stdafx.h"
#include "udpmonitor.h"

#include "udppacket.h"
#include "rcvdudppacket.h"
#include "udpsession.h"
#include "../Tools/MsgObjectPool.hpp"

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

using namespace boost::asio;
using namespace boost::signals2;
using boost::system::error_code;
using std::tr1::shared_ptr;

typedef std::tr1::unordered_map<std::string, UdpSession* > HsSession;

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

// 	signal<void(unsigned int, unsigned int)> sigSendError;
	MsgSignals udpSig;

	HsSession hsSession;

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
	UdpSession* pSession = FindSession(m_pImpl->epReceive);
	if (!pSession)
	{
		pSession = CreateSession(m_pImpl->epReceive);
	}

	pSession->ReceiveData(m_pImpl->arBuffer.data(), packet_bytes);
	//////////////////////////////////////////////////////////////////////////
	ReadyRead();
}

void UdpMonitor::SendTo(unsigned int uOrder, void* szData, unsigned int uSize, 
					   const std::string& strAddr, unsigned short uPort /*= 2425*/ )
{

	ip::udp::endpoint senderEndpoint(ip::address_v4::from_string(strAddr), uPort);
	m_pImpl->ios.post(boost::bind(&UdpMonitor::As_SendTo, this,
		uOrder, buffer(szData, uSize), senderEndpoint));
}

void UdpMonitor::As_SendTo( unsigned int uOrder,
	const boost::asio::mutable_buffers_1& buf, 
	const boost::asio::ip::udp::endpoint& point )
{
	char* p1 = boost::asio::buffer_cast<char*>(buf);
	std::size_t s1 = boost::asio::buffer_size(buf);

	//////////////////////////////////////////////////////////////////////////
	///发送消息
	UdpSession* pSession = FindSession(point);
	if (!pSession)
	{
		pSession = CreateSession(point);
	}

	pSession->SendData(uOrder, p1, s1);
	//////////////////////////////////////////////////////////////////////////
}

void UdpMonitor::Broadcast(void* szData, unsigned int uSize, unsigned short uPort)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
	m_pImpl->ios.post(boost::bind(&UdpMonitor::As_Broadcast, this,
		buffer(szData, uSize), senderEndpoint));
}

void UdpMonitor::As_Broadcast( const boost::asio::mutable_buffers_1& buffer,
	const boost::asio::ip::udp::endpoint& point )
{
	char* szData = boost::asio::buffer_cast<char*>(buffer);
	std::size_t uSize = boost::asio::buffer_size(buffer);
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

UdpSession* UdpMonitor::FindSession( const boost::asio::ip::udp::endpoint& point )
{
	UdpSession* pSession(NULL);
	std::string strEp;
	GetEpDesc(point, strEp);
	HsSession::iterator iFind = m_pImpl->hsSession.find(strEp);
	if (iFind != m_pImpl->hsSession.end())
	{
		pSession = iFind->second;
	}
	return pSession;
}

UdpSession* UdpMonitor::CreateSession( const boost::asio::ip::udp::endpoint& point )
{
	UdpSession* pSession = m_pImpl->mopSession.New();
	if (!pSession)
	{
		pSession = new UdpSession(m_pImpl->mopPackPool);
		pSession->SetSendFunc(boost::bind(&UdpMonitor::SendPacket, this, _1, _2));
		pSession->SetReceiveFunc(boost::bind(&UdpMonitor::ReceiveData, this, _1, _2));
	}
	pSession->SetEndPoint(point);
	std::string strEp;
	GetEpDesc(point, strEp);
	m_pImpl->hsSession[strEp] = pSession;
	return pSession;
}

void UdpMonitor::GetEpDesc( const boost::asio::ip::udp::endpoint& point, std::string& strDesc )
{
	std::stringstream ss;
	ss << point;
	ss >> strDesc;
}

MsgSignals* UdpMonitor::GetSignals()
{
	return &m_pImpl->udpSig;
}

void UdpMonitor::ReceiveData( std::tr1::shared_ptr<std::stringstream> ptData, 
	const boost::asio::ip::udp::endpoint& point )
{
	m_pImpl->udpSig.EmitReceive(point.address().to_string(), point.port(), ptData);
}




// signal<void(unsigned int, unsigned int)>* UdpMonitor::sg_SendError()
// {
// 	return &m_pImpl->sigSendError;
// }

// signal<void(unsigned int, shared_ptr<std::stringstream>)>* UdpMonitor::sg_ReceiveData()
// {
// 	return &m_pImpl->sigReceiveData;
// }

