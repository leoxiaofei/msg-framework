#include "stdafx.h"
#include "udpmonitor.h"

#include <boost/asio/ip/udp.hpp>
#include <boost/signals2.hpp>

using namespace boost::asio;

void UdpMonitor::as_SendTo(unsigned int uOrder, std::vector<char>* ptData,
	const std::string& strAddr, unsigned short uPort /*= 2425*/)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::from_string(strAddr), uPort);
	GetIOs().post(boost::bind(&UdpMonitor::SendTo, this,
		uOrder, ptData, senderEndpoint));
}

void UdpMonitor::as_Broadcast(std::vector<char>* ptData, unsigned short uPort)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
	GetIOs().post(boost::bind(&UdpMonitor::Broadcast, this,
		ptData, senderEndpoint));
}