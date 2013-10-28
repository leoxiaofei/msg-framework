#include "stdafx.h"

#include "HostManager.h"

#include "HostInfo.h"

#include "../Tools/MsgObjectPool.hpp"
#include "../Tools/IdCreater.hpp"

#include <unordered_map>
#include <map>

typedef std::tr1::unordered_map<std::string, HostInfo*> HsIpHost;
typedef std::map<unsigned int, HostInfo*>               MapIdHost;

class HostManager::Impl
{
public:
	MsgObjectPool<HostInfo> mopHostPool;
	HsIpHost hsIpHost;
	MapIdHost mapIdHost;
	IdCreater<unsigned int> icHost;
};

HostManager::HostManager()
{

}

HostManager::~HostManager()
{

}

HostInfo* HostManager::FindHost( const std::string& strIp, unsigned short uPort )
{
	HostInfo* pRet(NULL);
	std::string strTemp;
	std::stringstream ss;
	ss<<strIp<<uPort;
	ss>>strTemp;
	HsIpHost::iterator iFind = m_pImpl->hsIpHost.find(strTemp);
	if (iFind != m_pImpl->hsIpHost.end())
	{
		pRet = iFind->second;
	}
	return pRet;
}

HostInfo* HostManager::FindHost( unsigned int uHostId )
{
	HostInfo* pRet(NULL);
	MapIdHost::iterator iFind = m_pImpl->mapIdHost.find(uHostId);
	if (iFind != m_pImpl->mapIdHost.end())
	{
		pRet = iFind->second;
	}
	return pRet;
}

unsigned int HostManager::NewHost( const std::string& strIp, unsigned short uPort )
{
	HostInfo* pHostInfo = m_pImpl->mopHostPool.New();
	if (pHostInfo == NULL)
	{
		pHostInfo = new HostInfo;
	}
	pHostInfo->strIp = strIp;
	pHostInfo->uPort = uPort;
	pHostInfo->uHostId = m_pImpl->icHost();
	AddHost(pHostInfo);
	return pHostInfo->uHostId;
}

void HostManager::AddHost( HostInfo* pHostInfo )
{
	std::string strTemp;
	std::stringstream ss;
	ss<<pHostInfo->strIp<<pHostInfo->uPort;
	ss>>strTemp;
	m_pImpl->hsIpHost[strTemp] = pHostInfo;
	m_pImpl->mapIdHost[pHostInfo->uHostId] = pHostInfo;
}


void HostManager::RemoveHost( const HostInfo* pHostInfo )
{
	std::string strTemp;
	std::stringstream ss;
	ss<<pHostInfo->strIp<<pHostInfo->uPort;
	ss>>strTemp;
	m_pImpl->hsIpHost.erase(strTemp);
	m_pImpl->mapIdHost.erase(pHostInfo->uHostId);
}

void HostManager::DeleteHost( unsigned int uHostId )
{
	HostInfo* pHostInfo = FindHost(uHostId);
	if (pHostInfo)
	{
		RemoveHost(pHostInfo);
		m_pImpl->mopHostPool.Recycle(pHostInfo);
	}
}

void HostManager::DeleteHost( const std::string& strIp, unsigned short uPort )
{
	HostInfo* pHostInfo = FindHost(strIp, uPort);
	if (pHostInfo)
	{
		RemoveHost(pHostInfo);
		m_pImpl->mopHostPool.Recycle(pHostInfo);		
	}
}
