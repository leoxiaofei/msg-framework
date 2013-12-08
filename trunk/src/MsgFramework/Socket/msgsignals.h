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
		std::vector<char>*)> SigReceive;
	typedef SigReceive::slot_type SlotReceive;

	void ConnectReceive(const SlotReceive& pFunc);
	void EmitReceive(const std::string& strAddr, unsigned int uPort, 
		std::vector<char>* ptData);

	typedef boost::signals2::signal<void(const std::string&, unsigned int, bool)> SigConResult;
	typedef SigConResult::slot_type SlotConResult;
	void ConnectConResult(const SlotConResult& pFunc);
	void EmitConResult(const std::string& strAddr, unsigned int uPort, bool bSuccess);

	typedef boost::signals2::signal<void(unsigned int, int)> SigSendResult;
	typedef SigSendResult::slot_type SlotSendResult;

	void ConnectSendResult(const SlotSendResult& pFunc);
	void EmitSendResult(unsigned int uOrder, int uResultFlag);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // UDPSIGNALS_H__
