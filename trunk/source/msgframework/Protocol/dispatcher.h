#ifndef _DISPATCHER_H__
#define _DISPATCHER_H__

#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>

class TrafficData;

class Dispatcher
{
	class Impl;
public:
	Dispatcher(boost::asio::io_service& ios);
	~Dispatcher();

protected:
	void ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId);

	boost::asio::io_service& GetIOs();

public: ///Socketµ÷ÓÃ
	void as_ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId);

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _DISPATCHER_H__
