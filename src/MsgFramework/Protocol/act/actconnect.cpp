#include "stdafx.h"
#include "actconnect.h"
#include "..\..\Common\vcpool.h"
#include "..\agreement.h"
#include "..\actor.h"

ActConnect::ActConnect(Actor* pActor) 
: ActBase(pActor)
{

}

int ActConnect::GetType()
{
	return Agreement::PA_CONNECT;
}

void ActConnect::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{
	///TODO:数据清理

}

void ActConnect::SendData(unsigned int uHostId)
{
	m_pActor->SendData(uHostId, GetType(), VcPool::Instance().New());
}

