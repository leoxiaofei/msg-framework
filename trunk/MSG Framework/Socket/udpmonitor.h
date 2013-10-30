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
class UdpSession;
class MsgSignals;

class UdpMonitor
{
	class Impl;
public:
	UdpMonitor(boost::asio::io_service& io);
	~UdpMonitor(void);

	bool Listen(unsigned short sPort = 5123);

	void Broadcast(const std::tr1::shared_ptr<std::stringstream>& ptData, unsigned short uPort = 5123);
	void SendTo(unsigned int uOrder, const std::tr1::shared_ptr<std::stringstream>& ptData,
		const std::string& strAddr, unsigned short uPort = 5123);

	MsgSignals* GetSignals();

protected:
	void ReadyRead();
	void ReadHandler( const boost::system::error_code& ec, 
		std::size_t packet_bytes );

	void As_Broadcast(const std::tr1::shared_ptr<std::stringstream>& ptData, 
		const boost::asio::ip::udp::endpoint& point);
	void BroadcastPacket(UdpPacket* packet, const boost::asio::ip::udp::endpoint& point);
	void BroadcastHandler( const boost::system::error_code& ec);

	void As_SendTo(unsigned int uOrder,
		const std::tr1::shared_ptr<std::stringstream>& ptData, 
		const boost::asio::ip::udp::endpoint& point);
	void SendPacket(UdpPacket* packet, const boost::asio::ip::udp::endpoint& point);
	void SendToHandler( const boost::system::error_code& ec);

	void ReceiveData(std::tr1::shared_ptr<std::stringstream> ptData, 
		const boost::asio::ip::udp::endpoint& point);

	UdpSession* FindSession(const boost::asio::ip::udp::endpoint& point);
	UdpSession* CreateSession(const boost::asio::ip::udp::endpoint& point);

	void GetEpDesc(const boost::asio::ip::udp::endpoint& point, std::string& strDesc);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DETECTOR_H__
