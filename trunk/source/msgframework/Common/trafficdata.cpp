#include "stdafx.h"
#include "trafficdata.h"
#include "..\Tools\mspool.hpp"


typedef MsPool<struct pool_tag, std::vector<char> > VCP;

class TrafficData::Impl
{
public:
	Impl()
	: pData(VCP::New())
	{
		pData->resize(0);
	}

	~Impl()
	{
		VCP::Free(pData);
	}

	std::vector<char>* pData;
};

TrafficData::TrafficData()
: m_pImpl(new Impl)
{

}

TrafficData::~TrafficData()
{
}

std::vector<char>* TrafficData::GetData() const
{
	return m_pImpl->pData;
}

