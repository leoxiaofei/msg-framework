#include "stdafx.h"
#include "udpmonitor.h"

#include <boost/asio/ip/udp.hpp>
#include <boost/signals2.hpp>
#include "../Common/hostmanager.h"
#include "../Common/hostinfo.h"

using namespace boost::asio;

void UdpMonitor::as_SendTo(unsigned int uOrder, std::vector<char>* ptData, unsigned int uHostId)
{
	GetIOs().post(boost::bind(&UdpMonitor::SendTo, this, uOrder, ptData, uHostId));

}

void UdpMonitor::as_Broadcast(std::vector<char>* ptData, unsigned short uPort)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
	GetIOs().post(boost::bind(&UdpMonitor::Broadcast, this,
		ptData, senderEndpoint));
}