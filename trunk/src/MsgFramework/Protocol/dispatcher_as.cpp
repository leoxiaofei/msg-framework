#include "stdafx.h"
#include "dispatcher.h"
#include "../Common/hostmanager.h"
#include "agreement.h"

#include <boost/bind.hpp>
#include <boost/thread.hpp>

// void Dispatcher::as_TcpConnect(const std::string& strIp, unsigned short uPort)
// {
// 	GetIOs().post(boost::bind(&Dispatcher::StartConnect, this,
// 		strIp, uPort, HostManager::TT_TCP));
// }
// 
// void Dispatcher::as_UdpConnect(const std::string& strIp, unsigned short uPort)
// {
// 	GetIOs().post(boost::bind(&Dispatcher::StartConnect, this,
// 		strIp, uPort, HostManager::TT_UDP));
// }

void Dispatcher::as_Connect(unsigned int uHostId)
{
	GetIOs().post(boost::bind(&Dispatcher::StartConnect, this, uHostId));
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

void Dispatcher::as_ReceiveTcpData(unsigned int uHostId, std::vector<char>* ptData)
{
	GetIOs().post(boost::bind(&Dispatcher::RecTcpData, this, uHostId, ptData));
}

void Dispatcher::as_ReceiveUdpData(unsigned int uHostId, std::vector<char>* ptData)
{
	GetIOs().post(boost::bind(&Dispatcher::RecUdpData, this, uHostId, ptData));
}