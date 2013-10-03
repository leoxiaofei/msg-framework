#ifndef UDPSIGNALS_H__
#define UDPSIGNALS_H__

#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <memory>

class UdpSignals
{
	class Impl;
public:
	UdpSignals();
	~UdpSignals();

	typedef boost::signals2::signal<void(const std::string&, unsigned int, 
		std::tr1::shared_ptr<std::stringstream>)> SigReceive;
	typedef SigReceive::slot_type SlotReceive;

	void ConnectReceive(const SlotReceive& pFunc);

protected:
	void EmitReceive(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
	friend class UdpMonitor;
};

#endif // UDPSIGNALS_H__
