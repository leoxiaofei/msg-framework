#include "stdafx.h"
#include "ActCall.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"



int ActCall::GetType()
{
	return Agreement::PA_CALL;
}

void ActCall::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActCall::SendData()
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_sendFunc(0, GetType(), pData);
}

