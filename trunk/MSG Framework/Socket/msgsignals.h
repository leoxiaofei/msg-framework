#ifndef UDPSIGNALS_H__
#define UDPSIGNALS_H__

#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <memory>

class MsgSignals
{
	class Impl;
public:
	MsgSignals();
	~MsgSignals();

	typedef boost::signals2::signal<void(const std::string&, unsigned int, 
		const std::tr1::shared_ptr<std::stringstream>&)> SigReceive;
	typedef SigReceive::slot_type SlotReceive;

	void ConnectReceive(const SlotReceive& pFunc);
	void EmitReceive(const std::string& strAddr, unsigned int uPort, 
		const std::tr1::shared_ptr<std::stringstream>& ptData);


	typedef boost::signals2::signal<void(unsigned int, unsigned int)> SigError;
	typedef SigError::slot_type SlotError;

	void ConnectSendError(const SlotError& pFunc);
	void EmitSendError(unsigned int uOrder, unsigned int uErrorFlag);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // UDPSIGNALS_H__
