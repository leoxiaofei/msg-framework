#ifndef APPSIGNALS_H__
#define APPSIGNALS_H__

#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <memory>

class AppSignals
{
	class Impl;
public:
	AppSignals();
	~AppSignals();

	typedef boost::signals2::signal<void(unsigned int, 
		std::vector<char>* )> SigReceive;
	typedef SigReceive::slot_type SlotReceive;

	void ConnectReceive(const SlotReceive& pFunc);
	void EmitReceive(unsigned int uHostId, std::vector<char>* ptData);

	typedef boost::signals2::signal<void(const std::string&, unsigned int, unsigned int)> SigConResult;
	typedef SigConResult::slot_type SlotConResult;

	void ConnectConResult(const SlotConResult& pFunc);
	void EmitConResult(const std::string& strAddr, unsigned int uPort, unsigned int uHostId);

	typedef boost::signals2::signal<void(unsigned int, unsigned int)> SigError;
	typedef SigError::slot_type SlotError;

	void ConnectSendError(const SlotError& pFunc);
	void EmitSendError(unsigned int uOrder, unsigned int uErrorFlag);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // APPSIGNALS_H__
