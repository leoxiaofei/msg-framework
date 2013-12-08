#include "stdafx.h"
#include "ActProtResp.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"



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
	m_sendFunc(uHostId, GetType(), pData);
}

