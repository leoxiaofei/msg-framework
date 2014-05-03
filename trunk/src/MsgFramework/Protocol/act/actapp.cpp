#include "stdafx.h"
#include "actapp.h"
#include "../agreement.h"
#include "../../Common/vcpool.h"
#include "../actor.h"


ActApp::ActApp(Actor* pActor)
: ActBase(pActor)
{

}

int ActApp::GetType()
{
	return Agreement::PA_APP;
}

void ActApp::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{
	std::cout << (*ptData).data() << std::endl;
}

void ActApp::SendData(unsigned int uHostId)
{
	std::vector<char>* pData = VcPool::Instance().New();
	m_pActor->SendData(uHostId, GetType(), pData);
}


