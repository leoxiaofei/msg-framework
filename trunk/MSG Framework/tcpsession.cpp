#include "stdafx.h"

#include "tcpsession.h"
#include "common/tcppacket.h"
#include "common/rcvdtcppacket.h"

#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <queue>

using namespace boost::asio;
using std::tr1::shared_ptr;

class TcpSession::Impl
{
public:
	Impl(io_service& io, MsgObjectPool<SendTcpPacket>& pool)
	: ios(io) 
	, mopPackPool(pool)
	{}

	shared_ptr<ip::tcp::socket> ptSocket;
	std::tr1::array<char, 10240> arBuffer;

	io_service& ios;
	MsgObjectPool<SendTcpPacket>& mopPackPool;
	std::queue<SendTcpPacket*> quSendPacket;

	RcvdTcpPacket rcvdPacket;
};

TcpSession::TcpSession(boost::asio::io_service& io, MsgObjectPool<SendTcpPacket>& pPool)
: m_pImpl(new Impl(io, pPool))
{
}

TcpSession::~TcpSession()
{

}

void TcpSession::Connected( std::tr1::shared_ptr<ip::tcp::socket> ptSocket )
{
	m_pImpl->ptSocket = ptSocket;

	StartReceive();
}

void TcpSession::StartReceive()
{
	m_pImpl->rcvdPacket.ptStream.reset();
	ReceiveHead();
}


void TcpSession::ReceiveHead()
{
	m_pImpl->ptSocket->async_receive(buffer(m_pImpl->arBuffer, sizeof(TcpPacket)), 
		boost::bind(&TcpSession::ReceiveHeadHandler, this, 
		placeholders::error, placeholders::bytes_transferred));
}


void TcpSession::ReceiveBody(unsigned int uRemain)
{
	m_pImpl->ptSocket->async_receive(buffer(m_pImpl->arBuffer, 
		uRemain > m_pImpl->arBuffer.size() ? m_pImpl->arBuffer.size() : uRemain),
		boost::bind(&TcpSession::ReceiveBodyHandler, this, 
		placeholders::error, placeholders::bytes_transferred));
}

void TcpSession::ReceiveHeadHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		std::cout<<ec.message();
		return;
	}

	if (sizeof(TcpPacket) == packet_bytes)
	{
		TcpPacket packet;
		memcpy_s(&packet, packet_bytes, m_pImpl->arBuffer.data(), packet_bytes);
		if (packet.sType == 0xFFDD)
		{
			InitRPacket();
			m_pImpl->rcvdPacket.uTotal = packet.uSize;
			ReceiveBody(packet.uSize);
		}
	}
}

void TcpSession::ReceiveBodyHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		return;
	}

	m_pImpl->rcvdPacket.uCurrent += packet_bytes;
	m_pImpl->rcvdPacket.ptStream->write(m_pImpl->arBuffer.data(), packet_bytes);

	if ( m_pImpl->rcvdPacket.uCurrent != m_pImpl->rcvdPacket.uTotal)
	{
		ReceiveBody(m_pImpl->rcvdPacket.uTotal - m_pImpl->rcvdPacket.uCurrent);
	}
	else
	{
		///TODO:完整收到消息，提交数据

		StartReceive();
	}
}

void TcpSession::SendData( unsigned int uOrder, void* szData, unsigned int uSize )
{
	SendTcpPacket* pPacket = m_pImpl->mopPackPool.New();
	if (pPacket == NULL)
	{
		pPacket = new SendTcpPacket;
	}
	pPacket->uCur = 0;
	pPacket->uOrder = uOrder;
	pPacket->vecData.resize(uSize);
	std::copy((unsigned char*)szData, (unsigned char*)szData + uSize, 
		pPacket->vecData.begin());

	m_pImpl->ios.post(boost::bind(&TcpSession::As_Send, this, pPacket));
}

void TcpSession::InitRPacket()
{
	RcvdTcpPacket& packet = m_pImpl->rcvdPacket;
	packet.uCurrent = 0;
	packet.uTotal   = 0;
	packet.ptStream.reset(new std::stringstream);
}

void TcpSession::As_Send(SendTcpPacket* buf )
{
	m_pImpl->quSendPacket.push(buf);
	if (m_pImpl->quSendPacket.size() == 1)
	{
		SendHead(buf);
	}
}

void TcpSession::StartSend()
{
	if (!m_pImpl->quSendPacket.empty())
	{
		SendTcpPacket* pPacket = m_pImpl->quSendPacket.front();
		if(pPacket->uCur != 0)
		{
			SendBody(pPacket);
		}
		else
		{
			SendHead(pPacket);
		}
	}
}

void TcpSession::SendHeadHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		return;
	}

	SendTcpPacket* pPacket = m_pImpl->quSendPacket.front();
	SendBody(pPacket);
}

void TcpSession::SendBodyHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		return;
	}

	SendTcpPacket* pPacket = m_pImpl->quSendPacket.front();
	pPacket->uCur += packet_bytes;
	if (pPacket->uCur == pPacket->vecData.size())
	{
		m_pImpl->quSendPacket.pop();
		m_pImpl->mopPackPool.Recycle(pPacket);
	}
	StartSend();
}

void TcpSession::SendHead(SendTcpPacket* pPacket)
{
	TcpPacket head = {pPacket->vecData.size(), 0xFFDD};
	m_pImpl->ptSocket->async_send(buffer((void*)&head, sizeof(head)), 
		boost::bind(&TcpSession::SendHeadHandler, this, 
		placeholders::error, placeholders::bytes_transferred));
}

void TcpSession::SendBody(SendTcpPacket* pPacket)
{
	m_pImpl->ptSocket->async_send(buffer(pPacket->vecData.data() + pPacket->uCur,
		pPacket->vecData.size() - pPacket->uCur), 
		boost::bind(&TcpSession::SendBodyHandler, this, 
		placeholders::error, placeholders::bytes_transferred));
}
