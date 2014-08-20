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
// 	void as_UdpConnect(const std::string& strIp, unsigned short uPort);
// 	void as_TcpConnect(const std::string& strIp, unsigned short uPort);
	//void as_BroadcastData(std::vector<char>* ptData);
	//unsigned int as_SendData(unsigned int uHostId, std::vector<char>* ptData);
	void as_Connect(unsigned int uHostId);

protected:
	void StartConnect(unsigned int uHostId);

public: ///Socket调用
	void as_ReceiveUdpData(unsigned int uHostId, std::vector<char>* ptData);
	void as_ReceiveTcpData(unsigned int uHostId, std::vector<char>* ptData);
	void as_TcpConResult(unsigned int uHostId,	bool bSuccess);
	void as_UdpConResult(unsigned int uHostId,	bool bSuccess);

protected:
	void RecUdpData(unsigned int uHostId, std::vector<char>* ptData);
	void RecTcpData(unsigned int uHostId, std::vector<char>* ptData);

	void RecData(unsigned int uHostId, std::vector<char>* ptData);

	boost::asio::io_service& GetIOs();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DISPATCHER_H__
