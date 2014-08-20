#include "stdafx.h"
#include "actprotreq.h"
#include "../agreement.h"
#include "../../Common/vcpool.h"
#include "../actor.h"


int ActProtReq::GetType()
{
	return Agreement::PA_PROT_REQ;
}

void ActProtReq::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActProtReq::SendData(unsigned int uHostId)
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_pActor->SendData(uHostId, GetType(), pData);
}

