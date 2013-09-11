#ifndef DETECTOR_H__
#define DETECTOR_H__


#include <memory>
#include <queue>
#include <boost/asio/io_service.hpp>
#include <boost/signals2.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/udp.hpp>

struct UdpPacket;

class UdpMonitor
{
	class Impl;
public:
	UdpMonitor(boost::asio::io_service& io);
	~UdpMonitor(void);

	bool Listen(unsigned short sPort = 5123);

	void Broadcast(void* szData, unsigned int uSize, unsigned short uPort = 5123);
	void SendTo(unsigned int uOrder, void* szData, unsigned int uSize,
		const std::string& strAddr, unsigned short uPort = 5123);

	boost::signals2::signal<void(unsigned int, unsigned int)> *sg_SendError();
// 	boost::signals2::signal<void(unsigned int, std::tr1::shared_ptr<std::stringstream>)> *
// 		sg_ReceiveData();

protected:
	void ReadyRead();
	void ReadHandler( const boost::system::error_code& ec, 
		std::size_t packet_bytes );

	void BroadcastHandler( const boost::system::error_code& ec);

	void As_SendTo(unsigned int uOrder,
		const boost::asio::mutable_buffers_1& buffer, 
		const boost::asio::ip::udp::endpoint& point);
	void SendToHandler( const boost::system::error_code& ec);

	void SplitPacket(unsigned int uOrder, void* szData, 
		unsigned int uSize, std::queue<UdpPacket*>& queData);

	bool CheckPacket(UdpPacket* packet);
	void SendPacket(UdpPacket* packet, const boost::asio::ip::udp::endpoint& point);

	void CheckEmitReceive(unsigned int uOrder);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DETECTOR_H__
