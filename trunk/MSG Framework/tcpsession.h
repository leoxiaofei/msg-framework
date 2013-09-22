#ifndef TCPSESSION_H__
#define TCPSESSION_H__

#include "MsgObjectPool.hpp"
#include <boost\asio\ip\tcp.hpp>

struct SendTcpPacket;

class TcpSession
{
	class Impl;
public:
	TcpSession(boost::asio::io_service& io, MsgObjectPool<SendTcpPacket>& pPool);
	~TcpSession();

	void Connected(std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket);
	void SendData(unsigned int uOrder, void* szData, unsigned int uSize);

protected:
	void StartReceive();

	void ReceiveHead();
	void ReceiveBody(unsigned int uRemain);

	void ReceiveHeadHandler( const boost::system::error_code& ec, std::size_t packet_bytes );
	void ReceiveBodyHandler( const boost::system::error_code& ec, std::size_t packet_bytes );

	void As_Send(SendTcpPacket* buf);
	void StartSend();

	void SendHead(SendTcpPacket* pPacket);
	void SendBody(SendTcpPacket* pPacket);
	void SendHeadHandler( const boost::system::error_code& ec, std::size_t packet_bytes );
	void SendBodyHandler( const boost::system::error_code& ec, std::size_t packet_bytes );


protected:
	void InitRPacket();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // TCPSESSION_H__
