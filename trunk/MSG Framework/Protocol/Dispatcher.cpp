#include "stdafx.h"

#include "Dispatcher.h"
#include <boost/bind.hpp>
#include "HostManager.h"
#include "HostInfo.h"
#include "sendsignals.h"

class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios):iosWork(ios){}
	boost::asio::io_service& iosWork;
	SendSignals sendSignals;
};

Dispatcher::Dispatcher(boost::asio::io_service& ios)
: m_pImpl(new Impl(ios))
{

}

Dispatcher::~Dispatcher()
{

}

bool Dispatcher::SendData( unsigned int uHostId, unsigned int uOrder, 
	std::tr1::shared_ptr<std::stringstream> ptData )
{
	bool bRet(false);
	HostInfo* pHostInfo = HostManager::Instance().FindHost(uHostId);
	if (pHostInfo)
	{
		switch(HostManager::GetHostType(pHostInfo))
		{
		case HostManager::TT_UDP:
			m_pImpl->sendSignals.EmitSendUdp(uOrder, ptData, pHostInfo->strIp, pHostInfo->uPort);
			bRet = true;
			break;
		case HostManager::TT_TCP:
			m_pImpl->sendSignals.EmitSendTcp(uOrder, ptData, pHostInfo->strIp, pHostInfo->uPort);
			bRet = true;
			break;
		default:
			break;
		}
	}
	return bRet;
}

bool Dispatcher::BroadcastData( std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->sendSignals.EmitBroadcast(ptData);
	return true;
}

void Dispatcher::ReceiveUdpData( const std::string& strAddr, 
	unsigned int uPort, std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_RecUdpData, this,
		strAddr, uPort, ptData));
}

void Dispatcher::As_RecUdpData( const std::string& strAddr, unsigned int uPort,
	std::tr1::shared_ptr<std::stringstream> ptData )
{
	///分析来源
	HostInfo* pHostInfo = HostManager::Instance().FindHost(strAddr, uPort, HostManager::TT_UDP);
	if (pHostInfo == NULL)
	{
		unsigned int uHostId = HostManager::Instance().NewHost(strAddr, uPort, HostManager::TT_UDP);
		pHostInfo = HostManager::Instance().FindHost(uHostId);
	}
	///解析包

	///上传
}

void Dispatcher::ReceiveTcpData( const std::string& strAddr, unsigned int uPort, 
	std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_RecTcpData, this,
		strAddr, uPort, ptData));
}

void Dispatcher::As_RecTcpData( const std::string& strAddr, unsigned int uPort,
	std::tr1::shared_ptr<std::stringstream> ptData )
{
	HostInfo* pHostInfo = HostManager::Instance().FindHost(strAddr, uPort, HostManager::TT_TCP);
	if (pHostInfo == NULL)
	{
		unsigned int uHostId = HostManager::Instance().NewHost(strAddr, uPort, HostManager::TT_TCP);
		pHostInfo = HostManager::Instance().FindHost(uHostId);
	}
}

SendSignals* Dispatcher::GetSignals()
{
	return &m_pImpl->sendSignals;
}

unsigned int Dispatcher::UdpConnect( const std::string& strIp, unsigned short uPort )
{
	return 0;
}

unsigned int Dispatcher::TcpConnect( const std::string& strIp, unsigned short uPort )
{
	return 0;
}

