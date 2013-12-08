#ifndef DETECTOR_H__
#define DETECTOR_H__


#include <memory>
#include <queue>
#include <boost/asio/io_service.hpp>
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

	bool Listen(unsigned short sPort);

	void as_Broadcast(std::vector<char>* ptData, unsigned short uPort);
	void as_SendTo(unsigned int uOrder, std::vector<char>* ptData,
		const std::string& strAddr, unsigned short uPort);

	MsgSignals* GetSignals();

protected:
	void ReadyRead();
	void ReadHandler( const boost::system::error_code& ec, 
		std::size_t packet_bytes );

	void Broadcast(std::vector<char>* ptData, const boost::asio::ip::udp::endpoint& point);
	void BroadcastPacket(UdpPacket* packet, const boost::asio::ip::udp::endpoint& point);
	void BroadcastHandler( const boost::system::error_code& ec);

	void SendTo(unsigned int uOrder, std::vector<char>* ptData, 
		const boost::asio::ip::udp::endpoint& point);
	void SendPacket(UdpPacket* packet, const boost::asio::ip::udp::endpoint& point);
	void SendToHandler( const boost::system::error_code& ec);


	void SendResult(unsigned int uOrder, int nResultFlag);

	void ReceiveData(std::vector<char>* ptData, 
		const boost::asio::ip::udp::endpoint& point);

	UdpSession* FindSession(const boost::asio::ip::udp::endpoint& point);
	UdpSession* CreateSession(const boost::asio::ip::udp::endpoint& point);

	void GetEpDesc(const boost::asio::ip::udp::endpoint& point, std::string& strDesc);

	boost::asio::io_service& GetIOs();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DETECTOR_H__
