#include "StdAfx.h"
#include "ProtocolService.h"

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "Protocol/Dispatcher.h"

class ProtocolService::Impl
{
public:
	Impl()
	: wkWork(new boost::asio::io_service::work(iosWork))
	, thdWork(new boost::thread(
		boost::bind(&boost::asio::io_service::run, &iosWork)))
	, dispatcher(iosWork)
	{}

	~Impl()
	{
		wkWork.reset();
		if (thdWork)
			thdWork->join();
	}
	
	//////////////////////////////////////////////////////////////////////////
	///工作者线程
	boost::asio::io_service iosWork;
	boost::scoped_ptr<boost::asio::io_service::work> wkWork;
	boost::scoped_ptr<boost::thread> thdWork;

	//////////////////////////////////////////////////////////////////////////
	///
	Dispatcher dispatcher;
	
};

ProtocolService::ProtocolService(void)
: m_pImpl(new Impl)
{
}

ProtocolService::~ProtocolService(void)
{

}

void ProtocolService::Exit()
{
	m_pImpl->iosWork.stop();
	m_pImpl->thdWork->join();
}

Dispatcher* ProtocolService::GetDispatcher()
{
	return &m_pImpl->dispatcher;
}

