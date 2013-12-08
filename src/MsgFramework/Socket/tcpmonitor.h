#ifndef TCPMONITOR_H__
#define TCPMONITOR_H__

#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/tcp.hpp>

class MsgSignals;

class TcpMonitor
{
	class Impl;
public:
	TcpMonitor(boost::asio::io_service& io);
	~TcpMonitor();

	bool Listen(unsigned short sPort);
	
	void Connect(const std::string& strAddr, unsigned short sPort);

	void as_SendTo(unsigned int uOrder, std::vector<char>* ptData,
		const std::string& strAddr, unsigned short uPort);

	MsgSignals* GetSignals() const;

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

	void SendTo(unsigned int uOrder, std::vector<char>* ptData,
		const boost::asio::ip::tcp::endpoint& senderEndpoint);

	void ReceiveData(std::vector<char>* ptData, 
		const boost::asio::ip::tcp::endpoint& point);

	void SendResult(unsigned int uOrder, int nResultFlag);


	boost::asio::io_service& GetIOs();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // TCPMONITOR_H__
