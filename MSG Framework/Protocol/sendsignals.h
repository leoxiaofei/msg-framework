#ifndef SENDSIGNALS_H__
#define SENDSIGNALS_H__

#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <memory>

class SendSignals
{
	class Impl;
public:
	SendSignals();
	~SendSignals();

	typedef boost::signals2::signal<void(unsigned int, 
		const std::tr1::shared_ptr<std::stringstream>& ,
		const std::string&, unsigned short)> SigSend;
	typedef SigSend::slot_type SlotSend;

	void ConnectSendUdp(const SlotSend& pFunc);
	void EmitSendUdp(unsigned int uOrder, const std::tr1::shared_ptr<std::stringstream>& ptData,
		const std::string& strAddr, unsigned short uPort);

	void ConnectSendTcp(const SlotSend& pFunc);
	void EmitSendTcp(unsigned int uOrder, const std::tr1::shared_ptr<std::stringstream>& ptData,
		const std::string& strAddr, unsigned short uPort);


	typedef boost::signals2::signal<void(const std::tr1::shared_ptr<std::stringstream>&)> SigBroadcast;
	typedef SigBroadcast::slot_type SlotBroadcast;

	void ConnectBroadcast(const SlotBroadcast& pFunc);
	void EmitBroadcast(const std::tr1::shared_ptr<std::stringstream>& ptData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // SENDSIGNALS_H__
