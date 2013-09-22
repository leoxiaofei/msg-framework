#include "stdafx.h"
#include "tcpmonitor.h"
#include "tcpsession.h"
#include "common/tcppacket.h"

#include <boost/bind.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/signals2.hpp>
#include <unordered_map>

using namespace boost::asio;
using namespace boost::signals2;
using boost::system::error_code;
using std::tr1::shared_ptr;

typedef std::tr1::unordered_map<std::string, shared_ptr<TcpSession> > HsSession;

class TcpMonitor::Impl
{
public:
	Impl(io_service& io)
		: ios(io)
	{}

	io_service& ios;
	shared_ptr<ip::tcp::acceptor> ptAcceptor;
	ip::tcp::endpoint             epReceive;
	HsSession hsSession;
	MsgObjectPool<SendTcpPacket> mopPackPool;
};

TcpMonitor::TcpMonitor(io_service& io)
: m_pImpl(new Impl(io))
{
	Listen();
}

TcpMonitor::~TcpMonitor()
{

}

bool TcpMonitor::Listen( unsigned short sPort /*= 5123*/ )
{
	m_pImpl->ptAcceptor = shared_ptr<ip::tcp::acceptor>(new ip::tcp::acceptor(
		m_pImpl->ios, ip::tcp::endpoint(ip::tcp::v4(), sPort)));
	m_pImpl->ptAcceptor->set_option(ip::tcp::acceptor::reuse_address(true)); 
	ReadyAccept();
	return true;
}

void TcpMonitor::ReadyAccept()
{
	shared_ptr<ip::tcp::socket> ptSock(new ip::tcp::socket(m_pImpl->ios));

	m_pImpl->ptAcceptor->async_accept(*ptSock, m_pImpl->epReceive,
		boost::bind(&TcpMonitor::AcceptHandler, this, placeholders::error, ptSock));
}

void TcpMonitor::AcceptHandler( const boost::system::error_code& ec, 
	std::tr1::shared_ptr<ip::tcp::socket> ptSocket )
{
	if(ec)
	{
		return;
	}

	AssociateSession(ptSocket, m_pImpl->epReceive);
	
}

void TcpMonitor::Connect( const std::string& strAddr, 
	unsigned short sPort /*= 5123*/ )
{
	shared_ptr<ip::tcp::socket> ptSock(new ip::tcp::socket(m_pImpl->ios));
	shared_ptr<ip::tcp::endpoint> ptEndPoint(new ip::tcp::endpoint(ip::address::from_string(strAddr), sPort));
	ptSock->async_connect(*ptEndPoint,
		boost::bind(&TcpMonitor::ConnectHandler, this, placeholders::error, ptSock, ptEndPoint));
}

void TcpMonitor::ConnectHandler( const boost::system::error_code& ec, 
	std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket,
	std::tr1::shared_ptr<boost::asio::ip::tcp::endpoint> ptEndPoint )
{
	if(ec)
	{
		return;
	}

	AssociateSession(ptSocket, *ptEndPoint);
}

void TcpMonitor::AssociateSession( 
	const std::tr1::shared_ptr<boost::asio::ip::tcp::socket>& ptSocket,
	boost::asio::ip::tcp::endpoint& epReceive )
{
	shared_ptr<TcpSession> ptSession(new TcpSession(m_pImpl->ios, m_pImpl->mopPackPool));
	ptSession->Connected(ptSocket);

	std::stringstream ss;
	ss<<epReceive.address().to_string()
	  <<":"
	  <<epReceive.port();

	std::string strDes;
	ss>>strDes;
	m_pImpl->hsSession[strDes] = ptSession;
}

void TcpMonitor::SendTo( unsigned int uOrder, void* szData, unsigned int uSize,
	const std::string& strAddr, unsigned short uPort /*= 5123*/ )
{
	std::stringstream ss;
	ss<<strAddr
	  <<":"
	  <<uPort;

	std::string strDes;
	ss>>strDes;

	HsSession::iterator iFind = m_pImpl->hsSession.find(strDes);
	if(iFind != m_pImpl->hsSession.end())
	{
		iFind->second->SendData(uOrder, szData, uSize);
	}

}

