#include "stdafx.h"
#include "ActOffline.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"



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
	m_sendFunc(0, GetType(), pData);
}

