#include "stdafx.h"
#include "tcpmonitor.h"


#include <boost\bind.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\signals2.hpp>

using namespace boost::asio;
using namespace boost::signals2;
using boost::system::error_code;
using std::tr1::shared_ptr;


class TcpMonitor::Impl
{
public:
	Impl(io_service& io)
		: ios(io)
	{}

	io_service& ios;
	shared_ptr<ip::tcp::acceptor> ptAcceptor;
	//ip::tcp::endpoint epReceive;

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

	m_pImpl->ptAcceptor->async_accept(*ptSock, 
		boost::bind(&TcpMonitor::AcceptHandler, this, placeholders::error, ptSock));
}

void TcpMonitor::AcceptHandler( const boost::system::error_code& ec, 
	std::tr1::shared_ptr<ip::tcp::socket> ptSocket )
{

}

