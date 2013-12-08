#include "stdafx.h"
#include "vcpool.h"

VcPool::VcPool()
{

}

VcPool::~VcPool()
{

}

std::vector<char>* VcPool::New()
{
	std::vector<char>* pData = MsgObjectPool<std::vector<char> >::New();
	if (!pData)
	{
		pData = new std::vector<char>();
	}
	pData->clear();
	return pData;
}

