#include "stdafx.h"
#include "ActConnect.h"
#include "..\..\Common\vcpool.h"
#include "..\Agreement.h"
#include "..\Actor.h"

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

