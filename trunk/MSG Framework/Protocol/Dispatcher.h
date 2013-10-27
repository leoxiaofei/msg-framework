#ifndef DISPATCHER_H__
#define DISPATCHER_H__

#include <boost/asio/io_service.hpp>

class Dispatcher
{
	class Impl;
public:
	Dispatcher(boost::asio::io_service& ios);
	~Dispatcher();

public: ///App调用
	bool SendData(unsigned int uHostId, std::tr1::shared_ptr<std::stringstream> ptData);
	bool BroadcastData(std::tr1::shared_ptr<std::stringstream> ptData);

public: ///Socket调用
	void ReceiveUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

protected:
	void As_RecUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DISPATCHER_H__
