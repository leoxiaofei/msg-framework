#include "stdafx.h"

#include "Dispatcher.h"
#include <boost/bind.hpp>
#include <sstream>
#include "socketsignals.h"
#include "../Common/vcpool.h"
#include "../Common/hostmanager.h"
#include "../Common/hostinfo.h"

class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios)
	: iosWork(ios) {}

	boost::asio::io_service& iosWork;
	SocketSignals sendSignals;

	FuncReceive receiveFunc;
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


void Dispatcher::SendData(unsigned int uHostId, unsigned int uOrder, unsigned short eActType,
	std::vector<char>* ptData )
{
	HostInfo* pHostInfo = HostManager::Instance().FindHost(uHostId);
	if (pHostInfo)
	{
		unsigned int nOffSize = sizeof(eActType);
		ptData->resize(ptData->size() + nOffSize);
		std::copy(ptData->begin(), ptData->begin() + nOffSize, ptData->end() - nOffSize);
		std::copy((char*)&eActType, (char*)&eActType + nOffSize, ptData->begin());

		switch(HostManager::GetHostType(pHostInfo))
		{
		case HostManager::TT_UDP:
			m_pImpl->sendSignals.EmitSendUdp(uOrder, ptData, uHostId);
			break;
		case HostManager::TT_TCP:
			m_pImpl->sendSignals.EmitSendTcp(uOrder, ptData, uHostId);
			break;
		default:
			assert(false);
			break;
		}
	}
	/// TODO:如果没有找到，报错
}

void Dispatcher::RecUdpData(unsigned int uHostId, std::vector<char>* ptData )
{
	///分析来源
	//HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_UDP);
	///解析包
	RecData(uHostId, ptData);
}


void Dispatcher::RecTcpData(unsigned int uHostId, std::vector<char>* ptData )
{
	///分析来源
	//HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_TCP);
	///解析包
	RecData(uHostId, ptData);
}


void Dispatcher::RecData(unsigned int uHostId, std::vector<char>* ptData)
{
	unsigned short eActType;
	unsigned int nOffSize = sizeof(eActType);
	if (ptData->size() >= nOffSize)
	{
		std::copy(ptData->begin(), ptData->begin() + nOffSize, (char*)&eActType);
		std::copy(ptData->end() - nOffSize, ptData->end(), ptData->begin());
		ptData->resize(ptData->size() - nOffSize);

		///TODO:上传
		m_pImpl->receiveFunc(uHostId, eActType, ptData);
		///
	}
	else
	{
		///TODO:错误
	}

	VcPool::Instance().Recycle(ptData);
}


void Dispatcher::as_TcpConResult(unsigned int uHostId, bool bSuccess)
{
// 	unsigned int uHostId(0);
// 	if (bSuccess)
// 	{
// 		HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_TCP);
// 		uHostId = pHostInfo->uHostId;
// 	}
	//m_pImpl->appSignals.EmitConResult(strAddr, uPort, uHostId);
}

void Dispatcher::as_UdpConResult(unsigned int uHostId, bool bSuccess)
{
// 	unsigned int uHostId(0);
// 	if (bSuccess)
// 	{
// 		HostInfo* pHostInfo = TakeHostInfo(strAddr, uPort, HostManager::TT_UDP);
// 		uHostId = pHostInfo->uHostId;
// 	}
	//m_pImpl->appSignals.EmitConResult(strAddr, uPort, uHostId);
}

void Dispatcher::StartConnect( const std::string& strIp, unsigned short uPort, int eType )
{
	switch(eType)
	{
	case HostManager::TT_TCP:
		{
		HostInfo* pHostInfo = HostManager::Instance().TakeHost(strIp, uPort, HostManager::TT_TCP);
		m_pImpl->sendSignals.EmitTcpConnect(pHostInfo->uHostId);
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

void Dispatcher::BroadcastData(unsigned short eActType, std::vector<char>* ptData)
{
	unsigned int nOffSize = sizeof(eActType);
	ptData->resize(ptData->size() + nOffSize);
	std::copy(ptData->begin(), ptData->begin() + nOffSize, ptData->end() - nOffSize);
	std::copy((char*)&eActType, (char*)&eActType + nOffSize, ptData->begin());
	m_pImpl->sendSignals.EmitBroadcast(ptData);
}

boost::asio::io_service& Dispatcher::GetIOs()
{
	return m_pImpl->iosWork;
}

void Dispatcher::SetReceiver(const FuncReceive& receiveFunc)
{
	m_pImpl->receiveFunc = receiveFunc;
}


