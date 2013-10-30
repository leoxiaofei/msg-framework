#ifndef DISPATCHER_H__
#define DISPATCHER_H__

#include <boost/asio/io_service.hpp>

class SendSignals;

class Dispatcher
{
	class Impl;
public:
	Dispatcher(boost::asio::io_service& ios);
	~Dispatcher();

	SendSignals* GetSignals();

public: ///App调用
	unsigned int UdpConnect(const std::string& strIp, unsigned short uPort);
	unsigned int TcpConnect(const std::string& strIp, unsigned short uPort);
	bool SendData(unsigned int uHostId, unsigned int uOrder, 
		std::tr1::shared_ptr<std::stringstream> ptData);
	bool BroadcastData(std::tr1::shared_ptr<std::stringstream> ptData);

public: ///Socket调用
	void ReceiveUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);
	void ReceiveTcpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

protected:
	void As_RecUdpData(const std::string& strAddr, unsigned int uPort,
		std::tr1::shared_ptr<std::stringstream> ptData);
	void As_RecTcpData(const std::string& strAddr, unsigned int uPort,
		std::tr1::shared_ptr<std::stringstream> ptData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DISPATCHER_H__
