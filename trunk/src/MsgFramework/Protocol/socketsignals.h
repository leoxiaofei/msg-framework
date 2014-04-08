#ifndef SENDSIGNALS_H__
#define SENDSIGNALS_H__

#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <memory>

class SocketSignals
{
	class Impl;
public:
	SocketSignals();
	~SocketSignals();

	typedef boost::signals2::signal<void(unsigned int, 
		std::vector<char>* , unsigned int)> SigSend;
	typedef SigSend::slot_type SlotSend;

	void ConnectSendUdp(const SlotSend& pFunc);
	void EmitSendUdp(unsigned int uOrder, std::vector<char>* ptData,
		unsigned int uHostId);

	void ConnectSendTcp(const SlotSend& pFunc);
	void EmitSendTcp(unsigned int uOrder, std::vector<char>* ptData,
		unsigned int uHostId);

	typedef boost::signals2::signal<void(std::vector<char>*)> SigBroadcast;
	typedef SigBroadcast::slot_type SlotBroadcast;

	void ConnectBroadcast(const SlotBroadcast& pFunc);
	void EmitBroadcast(std::vector<char>* ptData);


	typedef boost::signals2::signal<void(unsigned int)> SigConnect;
	typedef SigConnect::slot_type SlotConnect;
	void ConnectTcpConnect(const SlotConnect& pFunc);
	void EmitTcpConnect(unsigned int uHostId);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // SENDSIGNALS_H__
