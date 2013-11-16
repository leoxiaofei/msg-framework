#include "stdafx.h"

#include "Dispatcher.h"
#include <boost/bind.hpp>
#include <sstream>
#include "HostManager.h"
#include "HostInfo.h"
#include "socketsignals.h"
#include "appsignals.h"

class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios):iosWork(ios){}
	boost::asio::io_service& iosWork;
	SocketSignals sendSignals;
	AppSignals    appSignals;
};

Dispatcher::Dispatcher(boost::asio::io_service& ios)
: m_pImpl(new Impl(ios))
{

}

Dispatcher::~Dispatcher()
{

}

SocketSignals* Dispatcher::GetSocketSignals()
{
	return &m_pImpl->sendSignals;
}

AppSignals* Dispatcher::GetAppSignals()
{
	return &m_pImpl->appSignals;
}

unsigned int Dispatcher::SendData( unsigned int uHostId, std::tr1::shared_ptr<std::stringstream> ptData )
{
	static unsigned int uOrder(0);
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_SendData, this,
		uHostId, ++uOrder, ptData));
	return uOrder;
}

void Dispatcher::As_SendData( unsigned int uHostId, unsigned int uOrder, 
	std::tr1::shared_ptr<std::stringstream> ptData )
{
	HostInfo* pHostInfo = HostManager::Instance().FindHost(uHostId);
	if (pHostInfo)
	{
		switch(HostManager::GetHostType(pHostInfo))
		{
		case HostManager::TT_UDP:
			m_pImpl->sendSignals.EmitSendUdp(uOrder, ptData, pHostInfo->strIp, pHostInfo->uPort);
			break;
		case HostManager::TT_TCP:
			m_pImpl->sendSignals.EmitSendTcp(uOrder, ptData, pHostInfo->strIp, pHostInfo->uPort);
			break;
		default:
			break;
		}
	}
	/// TODO:如果没有找到，报错
}

void Dispatcher::BroadcastData( std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_BroadcastData, this, ptData));
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
	HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_UDP);
	///解析包
	std::string strTemp = ptData->str();
	std::cout<<strTemp.size()<<std::endl;
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
	HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_TCP);

	std::string strTemp = ptData->str();
	std::cout<<strTemp.size()<<std::endl;
}

void Dispatcher::TcpConnect( const std::string& strIp, unsigned short uPort )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_StartConnect, this,
		strIp, uPort, HostManager::TT_TCP));
}

void Dispatcher::UdpConnect( const std::string& strIp, unsigned short uPort )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_StartConnect, this,
		strIp, uPort, HostManager::TT_UDP));
}

void Dispatcher::TcpConResult( const std::string& strAddr, unsigned int uPort, bool bSuccess )
{
	unsigned int uHostId(0);
	if (bSuccess)
	{
		HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_TCP);
		uHostId = pHostInfo->uHostId;
	}
	m_pImpl->appSignals.EmitConResult(strAddr, uPort, uHostId);
}

void Dispatcher::UdpConResult( const std::string& strAddr, unsigned int uPort, bool bSuccess )
{
	unsigned int uHostId(0);
	if (bSuccess)
	{
		HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_UDP);
		uHostId = pHostInfo->uHostId;
	}
	m_pImpl->appSignals.EmitConResult(strAddr, uPort, uHostId);
}

void Dispatcher::As_StartConnect( const std::string& strIp, unsigned short uPort, int eType )
{
	switch(eType)
	{
	case HostManager::TT_TCP:
		{
			m_pImpl->sendSignals.EmitTcpConnect(strIp, uPort);
		}
		break;
	case HostManager::TT_UDP:
		{

		}
		break;
	default:
		break;
	}
}

void Dispatcher::As_BroadcastData( std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->sendSignals.EmitBroadcast(ptData);
}

HostInfo* Dispatcher::TakeHostInfo( const std::string& strAddr, unsigned int uPort, int eType )
{
	HostInfo* pHostInfo = HostManager::Instance().FindHost(strAddr, uPort, HostManager::TT_TCP);
	if (pHostInfo == NULL)
	{
		pHostInfo = HostManager::Instance().NewHost(strAddr, uPort, HostManager::TT_TCP);
	}
	return pHostInfo;
}


