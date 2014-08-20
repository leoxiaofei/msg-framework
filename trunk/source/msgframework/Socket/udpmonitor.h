#ifndef _UDPMONITOR_H__
#define _UDPMONITOR_H__

#include <boost/scoped_ptr.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>

class TrafficData;

typedef boost::function<void(const TrafficData& tfcData, unsigned int uNetId)> FuncReceive;

class UdpMonitor
{
	class Impl;
public:
	UdpMonitor(boost::asio::io_service& io);
	~UdpMonitor();


	bool Listen(unsigned short sPort);
	
	void BroadcastData(const TrafficData& tfcData);
	void SendData(const TrafficData& tfcData, unsigned int uNetId);

	void SetReceiveFunc(const FuncReceive& funcReceive);

protected:
	void ReadyRead();
	void ReadHandler(const boost::system::error_code& ec, std::size_t packet_bytes, const TrafficData& tfcData);
	void SendHandler(const boost::system::error_code& ec, const TrafficData& tfcData);

private:
	boost::scoped_ptr<Impl> m_pImpl;
};



#endif // _UDPMONITOR_H__
