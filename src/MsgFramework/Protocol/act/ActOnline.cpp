#include "stdafx.h"
#include "ActOnline.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"

int ActOnline::GetType()
{
	return Agreement::PA_ONLINE;
}

void ActOnline::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActOnline::SendData()
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_sendFunc(0, GetType(), pData);
}

