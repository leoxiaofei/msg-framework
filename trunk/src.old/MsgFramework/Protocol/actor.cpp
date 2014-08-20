#include "stdafx.h"
#include "actor.h"
#include "../Tools/idcreater.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

#include "Act/actbase.h"
#include "Act/actconnect.h"
#include "Act/actonline.h"
#include "Act/actapp.h"

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
	if (ActBase* pActBase = GetActBase(eActType))
	{
		pActBase->ReceiveData(uHostId, ptData);
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
	ActBase* p = new ActConnect(this);
	m_pImpl->mapAct[p->GetType()] = p;

	p = new ActOnline(this);
	m_pImpl->mapAct[p->GetType()] = p;

	p = new ActApp(this);
	m_pImpl->mapAct[p->GetType()] = p;
}

ActBase* Actor::GetActBase(unsigned short uType)
{
	ActBase* pRet(NULL);

	std::map<unsigned short, ActBase*>::const_iterator iFind =
		m_pImpl->mapAct.find(uType);

	if (iFind != m_pImpl->mapAct.end())
	{
		pRet = iFind->second;
	}

	return pRet;
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