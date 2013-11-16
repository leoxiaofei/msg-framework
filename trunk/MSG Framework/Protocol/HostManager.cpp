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
	Impl():icHost(0){}
	MsgObjectPool<HostInfo> mopHostPool;
	HsIpHost hsIpHost[TT_TOTAL];
	MapIdHost mapIdHost;
	IdCreater<unsigned int> icHost;
};

HostManager::HostManager()
: m_pImpl(new Impl)
{

}

HostManager::~HostManager()
{

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

HostInfo* HostManager::FindHost( const std::string& strIp, unsigned short uPort, TransType eType )
{
	HostInfo* pRet(NULL);
	std::string strTemp = GetHsDesc(strIp, uPort);
	HsIpHost::iterator iFind = m_pImpl->hsIpHost[eType].find(strTemp);
	if (iFind != m_pImpl->hsIpHost[eType].end())
	{
		pRet = iFind->second;
	}
	return pRet;
}

void HostManager::AddHost( HostInfo* pHostInfo )
{
	std::string strTemp = GetHsDesc(pHostInfo->strIp, pHostInfo->uPort);
	m_pImpl->hsIpHost[GetHostType(pHostInfo)][strTemp] = pHostInfo;
	m_pImpl->mapIdHost[pHostInfo->uHostId] = pHostInfo;
}


void HostManager::RemoveHost( const HostInfo* pHostInfo )
{
	std::string strTemp = GetHsDesc(pHostInfo->strIp, pHostInfo->uPort);
	m_pImpl->hsIpHost[GetHostType(pHostInfo)].erase(strTemp);
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

void HostManager::DeleteHost( const std::string& strIp, unsigned short uPort, TransType eType )
{
	HostInfo* pHostInfo = FindHost(strIp, uPort, eType);
	if (pHostInfo)
	{
		RemoveHost(pHostInfo);
		m_pImpl->mopHostPool.Recycle(pHostInfo);		
	}
}

HostInfo* HostManager::NewHost( const std::string& strIp, unsigned short uPort, TransType eType )
{
	HostInfo* pHostInfo = m_pImpl->mopHostPool.New();
	if (pHostInfo == NULL)
	{
		pHostInfo = new HostInfo;
	}
	pHostInfo->strIp = strIp;
	pHostInfo->uPort = uPort;
	pHostInfo->uHostId = m_pImpl->icHost();
	if (eType == TT_TCP)
	{
		pHostInfo->uHostId |= 0x80000000;
	}
	AddHost(pHostInfo);
	return pHostInfo;
}

HostManager::TransType HostManager::GetHostType( const HostInfo* pHostInfo )
{
	return (pHostInfo->uHostId & 0x80000000) ? TT_TCP : TT_UDP;
}

std::string HostManager::GetHsDesc( const std::string& strIp, unsigned short uPort )
{
	std::string strTemp;
	std::stringstream ss;
	ss<<strIp<<":"<<uPort;
	ss>>strTemp;
	return strTemp;
}

// unsigned int HostManager::NewHost( const std::string& strIp, unsigned short uPort )
// {
// 	HostInfo* pHostInfo = m_pImpl->mopHostPool.New();
// 	if (pHostInfo == NULL)
// 	{
// 		pHostInfo = new HostInfo;
// 	}
// 	pHostInfo->strIp = strIp;
// 	pHostInfo->uPort = uPort;
// 	pHostInfo->uHostId = m_pImpl->icHost();
// 	AddHost(pHostInfo);
// 	return pHostInfo->uHostId;
// }

// HostInfo* HostManager::FindHost( const std::string& strIp, unsigned short uPort )
// {
// 	HostInfo* pRet(NULL);
// 	std::string strTemp;
// 	std::stringstream ss;
// 	ss<<strIp<<uPort;
// 	ss>>strTemp;
// 	HsIpHost::iterator iFind = m_pImpl->hsIpHost.find(strTemp);
// 	if (iFind != m_pImpl->hsIpHost.end())
// 	{
// 		pRet = iFind->second;
// 	}
// 	return pRet;
// }
// void HostManager::DeleteHost( const std::string& strIp, unsigned short uPort )
// {
// 	HostInfo* pHostInfo = FindHost(strIp, uPort);
// 	if (pHostInfo)
// 	{
// 		RemoveHost(pHostInfo);
// 		m_pImpl->mopHostPool.Recycle(pHostInfo);		
// 	}
// }
