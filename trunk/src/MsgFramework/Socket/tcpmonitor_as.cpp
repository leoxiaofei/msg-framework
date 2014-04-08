#include "stdafx.h"
#include "tcpmonitor.h"

#include <boost\asio\ip\tcp.hpp>
#include <boost/signals2.hpp>

using namespace boost::asio;


void TcpMonitor::as_SendTo(unsigned int uOrder, std::vector<char>* ptData, unsigned int uHostId)
{
	GetIOs().post(boost::bind(&TcpMonitor::SendTo, this, uOrder, ptData, uHostId));
}
