#include "stdafx.h"
#include "Dispatcher.h"

#include <boost/bind.hpp>
#include "HostManager.h"
#include "Agreement.h"
#include <boost/thread.hpp>

void Dispatcher::as_TcpConnect(const std::string& strIp, unsigned short uPort)
{
	GetIOs().post(boost::bind(&Dispatcher::StartConnect, this,
		strIp, uPort, HostManager::TT_TCP));
}

void Dispatcher::as_UdpConnect(const std::string& strIp, unsigned short uPort)
{
	GetIOs().post(boost::bind(&Dispatcher::StartConnect, this,
		strIp, uPort, HostManager::TT_UDP));
}

// unsigned int Dispatcher::as_SendData(unsigned int uHostId, std::vector<char>* ptData)
// {
// 	boost::mutex::scoped_lock lock(GetOrderIdMutex());
// 	unsigned int uOrder = GetNewOrderId();
// 	GetIOs().post(boost::bind(&Dispatcher::SendData, this, uHostId, uOrder, Agreement::PA_APP, ptData));
// 	return uOrder;
// }

// void Dispatcher::as_BroadcastData(std::vector<char>* ptData)
// {
// 	GetIOs().post(boost::bind(&Dispatcher::BroadcastData, this, ptData));
// }

void Dispatcher::as_ReceiveTcpData(const std::string& strAddr, unsigned int uPort,
	std::vector<char>* ptData)
{
	GetIOs().post(boost::bind(&Dispatcher::RecTcpData, this,
		strAddr, uPort, ptData));
}

void Dispatcher::as_ReceiveUdpData(const std::string& strAddr,
	unsigned int uPort, std::vector<char>* ptData)
{
	GetIOs().post(boost::bind(&Dispatcher::RecUdpData, this,
		strAddr, uPort, ptData));
}