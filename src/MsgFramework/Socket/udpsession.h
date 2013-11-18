#ifndef UDPSESSION_H__
#define UDPSESSION_H__

#include <boost/asio/ip/udp.hpp>
#include <boost/function.hpp>
#include <queue>


template <class T>
class MsgObjectPool;
struct UdpPacket;

class UdpSession
{
	class Impl;
public:
	UdpSession(MsgObjectPool<UdpPacket> &mopPackPool);
	~UdpSession();

	typedef boost::function<void(std::tr1::shared_ptr<std::stringstream>, 
		const boost::asio::ip::udp::endpoint&)> FuncReceive;
	typedef boost::function<void ( UdpPacket* ,
		const boost::asio::ip::udp::endpoint& )> FuncSend;

	void SetEndPoint(const boost::asio::ip::udp::endpoint& point);
	void SetSendFunc(const FuncSend& pFunc);
	void SetReceiveFunc(const FuncReceive& pFunc);

	void Clear();

	void SendData(unsigned int uOrder, const char* szData, std::size_t packet_bytes);
	void ReceiveData(const char* szData, std::size_t packet_bytes);

protected:
	bool CheckPacket(UdpPacket* packet);
	void CheckEmitReceive(unsigned int uOrder);

	void SplitPacket(unsigned int uOrder, const void* szData, 
		unsigned int uSize, std::queue<UdpPacket*>& queData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};


#endif // UDPSESSION_H__
