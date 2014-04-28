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

	///接收信号
	typedef boost::signals2::signal<void(unsigned int ,
		std::vector<char>*)> SigReceive;
	typedef SigReceive::slot_type SlotReceive;

	void ConnectReceive(const SlotReceive& pFunc);
	void EmitReceive(unsigned int uHostId, std::vector<char>* ptData);

	///发送结果信号
	typedef boost::signals2::signal<void(unsigned int, int)> SigSendResult;
	typedef SigSendResult::slot_type SlotSendResult;

	void ConnectSendResult(const SlotSendResult& pFunc);
	void EmitSendResult(unsigned int uOrder, int uResultFlag);

	///连接结果信号
	typedef boost::signals2::signal<void(unsigned int, bool)> SigConResult;
	typedef SigConResult::slot_type SlotConResult;
	void ConnectConResult(const SlotConResult& pFunc);
	void EmitConResult(unsigned int uHostId, bool bSuccess);

	///连接中断
	typedef boost::signals2::signal<void(unsigned int)> SigBreakOff;
	typedef SigBreakOff::slot_type SlotBreakOff;
	void ConnectBreakOff(const SlotBreakOff& pFunc);
	void EmitBreakOff(unsigned int uHostId);


private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // UDPSIGNALS_H__
