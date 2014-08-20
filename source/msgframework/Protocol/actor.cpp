#include "stdafx.h"
#include "actor.h"
#include <map>
#include "..\Tools\idcreater.hpp"
#include "act\actentry.h"

typedef std::map<unsigned short, ActBase*> MapAct;

class Actor::Impl
{
public:
	Impl(boost::asio::io_service& ios)
		: iosWork(ios)
		, icOrderId(0) {}

	boost::asio::io_service& iosWork;

// 	boost::mutex mxOrderId;
 	IdCreater<unsigned int> icOrderId;

	MapAct mapAct;
};


Actor::Actor(boost::asio::io_service& iosWork)
	: m_pImpl(new Impl(iosWork))
{
	Init();
}

Actor::~Actor()
{

}


void Actor::Init()
{
	RegAct<ActEntry>();
}

ActBase* Actor::GetActBase(unsigned short uType)
{
	ActBase* pBase(NULL);
	MapAct::const_iterator ciFind = m_pImpl->mapAct.find(uType);
	if (ciFind != m_pImpl->mapAct.end())
	{
		pBase = ciFind->second;
	}
	return pBase;
}

void Actor::RegActBase(unsigned short uType, ActBase* pBase)
{
	m_pImpl->mapAct[uType] = pBase;
}
