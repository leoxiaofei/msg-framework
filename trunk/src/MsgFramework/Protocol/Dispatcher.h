#ifndef DISPATCHER_H__
#define DISPATCHER_H__

#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>

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


	typedef boost::function<void(unsigned int, unsigned short,
		std::vector<char>*) > FuncReceive;

	void SetReceiver(const FuncReceive& receiveFunc);
	void SendData(unsigned int uHostId, unsigned int uOrder, unsigned short eActType,
		std::vector<char>* ptData);
	void BroadcastData(unsigned short eActType, std::vector<char>* ptData);

public: ///App调用
	void as_UdpConnect(const std::string& strIp, unsigned short uPort);
	void as_TcpConnect(const std::string& strIp, unsigned short uPort);
	//void as_BroadcastData(std::vector<char>* ptData);
	//unsigned int as_SendData(unsigned int uHostId, std::vector<char>* ptData);

protected:
	void StartConnect(const std::string& strIp, unsigned short uPort, int eType);

public: ///Socket调用
	void as_ReceiveUdpData(const std::string& strAddr, unsigned int uPort, 
		std::vector<char>* ptData);
	void as_ReceiveTcpData(const std::string& strAddr, unsigned int uPort, 
		std::vector<char>* ptData);
	void as_TcpConResult(const std::string& strAddr, unsigned int uPort, 
		bool bSuccess);
	void as_UdpConResult(const std::string& strAddr, unsigned int uPort, 
		bool bSuccess);

protected:
	void RecUdpData(const std::string& strAddr, unsigned int uPort,
		std::vector<char>* ptData);
	void RecTcpData(const std::string& strAddr, unsigned int uPort,
		std::vector<char>* ptData);

	void RecData(unsigned int uHostId, std::vector<char>* ptData);

	HostInfo* TakeHostInfo(const std::string& strAddr, unsigned int uPort, int eType);

	boost::asio::io_service& GetIOs();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DISPATCHER_H__
