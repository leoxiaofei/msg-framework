#include "stdafx.h"
#include "Actor.h"
#include "../Tools/IdCreater.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

#include "act/Actbase.h"
#include "act/ActConnect.h"
#include "act/ActOnline.h"
#include "act/ActApp.h"

class Actor::Impl
{
public:
	Impl(boost::asio::io_service& ios)
		: iosWork(ios)
		, icOrderId(0) {}

	boost::asio::io_service& iosWork;

	boost::mutex mxOrderId;
	IdCreater<unsigned int> icOrderId;

	FuncSend sendFunc;
	FuncBroadcast broadcastFunc;

	std::map<unsigned short, ActBase*> mapAct;
};

Actor::Actor(boost::asio::io_service& iosWork)
: m_pImpl(new Impl(iosWork))
{
	Init();
}

Actor::~Actor()
{

}

void Actor::SetSender(const FuncSend& sendFunc)
{
	m_pImpl->sendFunc = sendFunc;
}

void Actor::SetBroadcastor(const FuncBroadcast& broadcastFunc)
{
	m_pImpl->broadcastFunc = broadcastFunc;
}

void Actor::ReceiveData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData)
{
	std::map<unsigned short, ActBase*>::const_iterator iFind =
		m_pImpl->mapAct.find(eActType);
	if (iFind != m_pImpl->mapAct.end())
	{
		iFind->second->ReceiveData(uHostId, ptData);
	}
}

unsigned int Actor::SendData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData)
{
	unsigned int uOrder = 0;

	if (uHostId != 0)
	{
		boost::mutex::scoped_lock lock(m_pImpl->mxOrderId);
		uOrder = m_pImpl->icOrderId();
		m_pImpl->sendFunc(uHostId, uOrder, eActType, ptData);
	}
	else
	{
		m_pImpl->broadcastFunc(eActType, ptData);

	}
	
	return uOrder;
}

unsigned int Actor::as_SendData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData)
{
	unsigned int uOrder(0);

	if (uHostId)
	{
		boost::mutex::scoped_lock lock(m_pImpl->mxOrderId);
		uOrder = m_pImpl->icOrderId();
		m_pImpl->iosWork.post(boost::bind(m_pImpl->sendFunc, uHostId, uOrder, eActType, ptData));
	}
	else
	{
		m_pImpl->iosWork.post(boost::bind(m_pImpl->broadcastFunc, eActType, ptData));
	}

	return uOrder;
}

void Actor::Init()
{
	ActBase* p = new ActConnect();
	m_pImpl->mapAct[p->GetType()] = p;
	p->SetActor(this);

	p = new ActOnline();
	m_pImpl->mapAct[p->GetType()] = p;
	p->SetActor(this);

	p = new ActApp();
	m_pImpl->mapAct[p->GetType()] = p;
	p->SetActor(this);
}





/*
unsigned int Dispatcher::SendData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData)
{
boost::mutex::scoped_lock lock(GetOrderIdMutex());
unsigned int uOrder = m_pImpl->icOrderId();
Dispatcher::SendData(uHostId, uOrder, eActType, ptData);
return uOrder;
}
*/