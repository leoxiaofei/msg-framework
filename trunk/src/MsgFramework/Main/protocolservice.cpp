#include "StdAfx.h"
#include "protocolservice.h"

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../Protocol/dispatcher.h"
#include "../Protocol/actor.h"

class ProtocolService::Impl
{
public:
	Impl()
	: wkWork(new boost::asio::io_service::work(iosWork))
	, thdWork(new boost::thread(
		boost::bind(&boost::asio::io_service::run, &iosWork)))
	, dispatcher(iosWork)
	, actor(iosWork)
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
	Actor      actor;
};

ProtocolService::ProtocolService(void)
: m_pImpl(new Impl)
{

	m_pImpl->dispatcher.SetReceiver(boost::bind(&Actor::ReceiveData, m_pImpl->actor, _1, _2, _3));
	m_pImpl->actor.SetSender(boost::bind(&Dispatcher::SendData, m_pImpl->dispatcher, _1, _2, _3, _4));
	m_pImpl->actor.SetBroadcastor(boost::bind(&Dispatcher::BroadcastData, m_pImpl->dispatcher, _1, _2));
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

Actor* ProtocolService::GetActor()
{
	return &m_pImpl->actor;
}

