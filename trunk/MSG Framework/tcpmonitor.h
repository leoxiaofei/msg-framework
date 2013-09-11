#ifndef TCPMONITOR_H__
#define TCPMONITOR_H__

#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/tcp.hpp>



class TcpMonitor
{
	class Impl;
public:
	TcpMonitor(boost::asio::io_service& io);
	~TcpMonitor();

	bool Listen(unsigned short sPort = 5123);

protected:
	void ReadyAccept();
	void AcceptHandler(const boost::system::error_code& ec, 
		std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // TCPMONITOR_H__
