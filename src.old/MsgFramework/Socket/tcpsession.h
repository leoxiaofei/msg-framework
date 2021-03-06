#ifndef TCPSESSION_H__
#define TCPSESSION_H__

#include <boost/asio/ip/tcp.hpp>
#include <boost/function.hpp>

template <class T>
class MsgObjectPool;

struct SendTcpPacket;

class TcpSession
{
	class Impl;
public:
	TcpSession(boost::asio::io_service& io, MsgObjectPool<SendTcpPacket>& pPool);
	~TcpSession();

	void Connected(std::tr1::shared_ptr<boost::asio::ip::tcp::socket> ptSocket, unsigned int uHostId);
	void SendData(unsigned int uOrder, const char* szData, unsigned int uSize);

	typedef boost::function<void(std::vector<char>*, unsigned int)> FuncReceive;
	typedef boost::function<void(unsigned int, int)> FuncResult;
	typedef boost::function<void(unsigned int)> FuncBreakOff;

	void SetReceiveFunc(const FuncReceive& pFunc);

	void SetResultFunc(const FuncResult& pFunc);

	void SetBreakOffFunc(const FuncBreakOff& pFunc);

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
