#include "stdafx.h"
#include "actoffline.h"
#include "../agreement.h"
#include "../../Common/vcpool.h"
#include "../actor.h"



int ActOffline::GetType()
{
	return Agreement::PA_OFFLINE;
}

void ActOffline::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActOffline::SendData()
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_pActor->SendData(0, GetType(), pData);
}

