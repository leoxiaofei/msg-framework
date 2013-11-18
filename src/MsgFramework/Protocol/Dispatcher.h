#ifndef DISPATCHER_H__
#define DISPATCHER_H__

#include <boost/asio/io_service.hpp>

class SocketSignals;
class AppSignals;
class HostInfo;

class Dispatcher
{
	class Impl;
public:
	Dispatcher(boost::asio::io_service& ios);
	~Dispatcher();

	SocketSignals* GetSocketSignals();
	AppSignals* GetAppSignals();

public: ///App调用
	void UdpConnect(const std::string& strIp, unsigned short uPort);
	void TcpConnect(const std::string& strIp, unsigned short uPort);
	void BroadcastData(std::tr1::shared_ptr<std::stringstream> ptData);
	unsigned int SendData(unsigned int uHostId, std::tr1::shared_ptr<std::stringstream> ptData);

protected:
	void As_StartConnect(const std::string& strIp, unsigned short uPort, int eType);
	void As_SendData(unsigned int uHostId, unsigned int uOrder, 
		std::tr1::shared_ptr<std::stringstream> ptData);
	void As_BroadcastData(std::tr1::shared_ptr<std::stringstream> ptData);

public: ///Socket调用
	void ReceiveUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);
	void ReceiveTcpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);
	void TcpConResult(const std::string& strAddr, unsigned int uPort, 
		bool bSuccess);
	void UdpConResult(const std::string& strAddr, unsigned int uPort, 
		bool bSuccess);

protected:
	void As_RecUdpData(const std::string& strAddr, unsigned int uPort,
		std::tr1::shared_ptr<std::stringstream> ptData);
	void As_RecTcpData(const std::string& strAddr, unsigned int uPort,
		std::tr1::shared_ptr<std::stringstream> ptData);

	HostInfo* TakeHostInfo(const std::string& strAddr, unsigned int uPort, int eType);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DISPATCHER_H__
