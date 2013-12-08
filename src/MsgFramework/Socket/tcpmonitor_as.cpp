#include "stdafx.h"
#include "tcpmonitor.h"

#include <boost\asio\ip\tcp.hpp>
#include <boost/signals2.hpp>

using namespace boost::asio;


void TcpMonitor::as_SendTo(unsigned int uOrder, std::vector<char>* ptData, 
	const std::string& strAddr, unsigned short uPort)
{
	ip::tcp::endpoint senderEndpoint(ip::address_v4::from_string(strAddr), uPort);
	GetIOs().post(boost::bind(&TcpMonitor::SendTo, this,
		uOrder, ptData, senderEndpoint));
}
