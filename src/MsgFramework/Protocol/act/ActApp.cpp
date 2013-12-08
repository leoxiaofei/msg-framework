#include "stdafx.h"
#include "ActApp.h"
#include "../Agreement.h"
#include "../../Common/vcpool.h"


int ActApp::GetType()
{
	return Agreement::PA_APP;
}

void ActApp::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{

}

void ActApp::SendData(unsigned int uHostId)
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_sendFunc(uHostId, GetType(), pData);
}

