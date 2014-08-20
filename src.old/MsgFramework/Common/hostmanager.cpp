#include "stdafx.h"

#include "hostmanager.h"

#include "hostinfo.h"

#include "../Tools/msgobjectpool.hpp"
#include "../Tools/idcreater.hpp"

#include <unordered_map>
#include <map>
#include <boost/thread/mutex.hpp>

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
	boost::mutex mxHost;


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
	boost::mutex::scoped_lock lock(m_pImpl->mxHost);
	HostInfo* pRet(NULL);
	MapIdHost::iterator iFind = m_pImpl->mapIdHost.find(uHostId);
	if (iFind != m_pImpl->mapIdHost.end())
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
	boost::mutex::scoped_lock lock(m_pImpl->mxHost);
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

HostInfo* HostManager::TakeHost(const std::string& strAddr, unsigned int uPort, TransType eType)
{
	boost::mutex::scoped_lock lock(m_pImpl->mxHost);
	HostInfo* pHostInfo = FindHost(strAddr, uPort, eType);
	if (pHostInfo == NULL)
	{
		pHostInfo = NewHost(strAddr, uPort, eType);
	}
	return pHostInfo;
}

HostInfo* HostManager::FindHost(const std::string& strIp, unsigned short uPort, TransType eType)
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

HostInfo* HostManager::NewHost(const std::string& strIp, unsigned short uPort, TransType eType)
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