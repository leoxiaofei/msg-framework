#include "stdafx.h"
#include "ActProtReq.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"


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
	m_sendFunc(uHostId, GetType(), pData);
}

