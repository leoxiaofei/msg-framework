#include "stdafx.h"
#include "skconvert.h"
#include "..\Common\hostinfo.h"

using std::tr1::shared_ptr;
using namespace boost::asio;

std::tr1::shared_ptr<boost::asio::ip::tcp::endpoint> SkConvert::TcpEndpoint(const HostInfo* pHostInfo)
{
	shared_ptr<ip::tcp::endpoint> ptEndPoint(new ip::tcp::endpoint(ip::address::from_string(pHostInfo->strIp), pHostInfo->uPort));
	return ptEndPoint;
}

std::tr1::shared_ptr<boost::asio::ip::udp::endpoint> SkConvert::UdpEndpoint(const HostInfo* pHostInfo)
{
	shared_ptr<ip::udp::endpoint> ptEndPoint(new ip::udp::endpoint(ip::address::from_string(pHostInfo->strIp), pHostInfo->uPort));
	return ptEndPoint;
}


