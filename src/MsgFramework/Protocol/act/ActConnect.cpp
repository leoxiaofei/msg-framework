#include "stdafx.h"
#include "ActConnect.h"
#include "..\..\Common\vcpool.h"
#include "..\Agreement.h"

int ActConnect::GetType()
{
	return Agreement::PA_CONNECT;
}

void ActConnect::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{
	///TODO:��������

}

void ActConnect::SendData(unsigned int uHostId)
{
	m_sendFunc(uHostId, GetType(), VcPool::Instance().New());
}

