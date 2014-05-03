#include "stdafx.h"
#include "acthere.h"
#include "../agreement.h"
#include "../../Common/vcpool.h"
#include "../actor.h"



int ActHere::GetType()
{
	return Agreement::PA_HERE;
}

void ActHere::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActHere::SendData(unsigned int uHostId)
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_pActor->SendData(uHostId, GetType(), pData);
}

