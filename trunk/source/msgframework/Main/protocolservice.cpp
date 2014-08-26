#include "stdafx.h"
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
		, dispatcher(iosWork)
		, actor(iosWork)
	{}

	//////////////////////////////////////////////////////////////////////////
	boost::asio::io_service iosWork;								///io_service对象
	boost::scoped_ptr<boost::asio::io_service::work> wkWork;		///是用于防止iosWork为空时线程结束的对象。
	boost::shared_ptr<boost::thread> thdWork;


	Dispatcher dispatcher;
	Actor      actor;

};

ProtocolService::ProtocolService()
: m_pImpl(new Impl)
{
	Init();
}

ProtocolService::~ProtocolService()
{

}

void ProtocolService::Init()
{
	m_pImpl->actor.SetDispatcher(&m_pImpl->dispatcher);
}

void ProtocolService::Start()
{
	m_pImpl->thdWork = boost::make_shared<boost::thread>(boost::bind(&boost::asio::io_service::run, &m_pImpl->iosWork));
}

void ProtocolService::Wait()
{
	m_pImpl->thdWork->join();
}

void ProtocolService::Exit()
{
	m_pImpl->iosWork.stop();
}

Dispatcher* ProtocolService::GetDispatcher() const
{
	return &m_pImpl->dispatcher;
}

Actor* ProtocolService::GetActor() const
{
	return &m_pImpl->actor;
}

