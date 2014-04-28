#include "stdafx.h"
#include "ActHere.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"
#include "../Actor.h"



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

