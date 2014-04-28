#include "stdafx.h"
#include "ActProtResp.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"
#include "../Actor.h"



int ActProtResp::GetType()
{
	return Agreement::PA_PROT_RESP;
}

void ActProtResp::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActProtResp::SendData(unsigned int uHostId)
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_pActor->SendData(uHostId, GetType(), pData);
}

