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
	
	void Connect(const std::string& strAddr, unsigned short sPort = 5123);

	void SendTo(unsigned int uOrder, void* szData, unsigned int uSize,
		const std::string& strAddr, unsigned short uPort = 5123);

protected:
	void ReadyAccept();
	void AcceptHandler(const boost::system::error_code& ec, 
		std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket);

	void ConnectHandler(const boost::system::error_code& ec, 
		std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket,
		std::tr1::shared_ptr<boost::asio::ip::tcp::endpoint> ptEndPoint);

	void AssociateSession(
		const std::tr1::shared_ptr<boost::asio::ip::tcp::socket>& ptSocket,
		const boost::asio::ip::tcp::endpoint& epReceive);

	void GetEpDesc(const boost::asio::ip::tcp::endpoint& point, std::string& strDesc);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // TCPMONITOR_H__
