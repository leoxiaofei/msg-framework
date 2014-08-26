#include "stdafx.h"
#include "actor.h"
#include <map>
#include "..\Tools\idcreater.hpp"
#include "act\actentry.h"
#include "Act\actexit.h"
#include "Act\actansentry.h"
#include "dispatcher.h"

#include <boost/bind.hpp>

class Actor::Impl
{
public:
	Impl(boost::asio::io_service& ios)
		: iosWork(ios)
		, icOrderId(0)
		, pDispatcher(0){}

	boost::asio::io_service& iosWork;

// 	boost::mutex mxOrderId;
 	IdCreater<unsigned int> icOrderId;

	Dispatcher* pDispatcher;
};


Actor::Actor(boost::asio::io_service& iosWork)
	: m_pImpl(new Impl(iosWork))
{
}

Actor::~Actor()
{

}

void Actor::Online(unsigned int uNetId) const
{
	std::cout << "Online:" << uNetId << std::endl;
	if (ActAnsEntry* pAnsEntry = m_pImpl->pDispatcher->GetAct<ActAnsEntry>())
	{
		pAnsEntry->SendMsg(uNetId);
	}
}

void Actor::Offline(unsigned int uNetId) const
{
	std::cout << "Offline:" << uNetId << std::endl;
}

void Actor::AnsOnline(unsigned int uNetId) const
{

}

void Actor::SetDispatcher(Dispatcher* pDispatcher)
{
	m_pImpl->pDispatcher = pDispatcher;

	if (ActEntry* pActEntry = pDispatcher->GetAct<ActEntry>())
	{
		pActEntry->SetReceiveFunc(boost::bind(&Actor::Online, this, _1));
	}

	if (ActExit* pActExit = pDispatcher->GetAct<ActExit>())
	{
		pActExit->SetReceiveFunc(boost::bind(&Actor::Offline, this, _1));
	}

	if (ActAnsEntry* pAnsEntry = pDispatcher->GetAct<ActAnsEntry>())
	{
		pAnsEntry->SetReceiveFunc(boost::bind(&Actor::AnsOnline, this, _1));
	}
}

