#ifndef _SKCONVERT_H__
#define _SKCONVERT_H__

#include <memory>
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\ip\udp.hpp>

class HostInfo;

namespace SkConvert
{
	std::tr1::shared_ptr<boost::asio::ip::tcp::endpoint> TcpEndpoint(const HostInfo* pHostInfo);
	std::tr1::shared_ptr<boost::asio::ip::udp::endpoint> UdpEndpoint(const HostInfo* pHostInfo);

	void SetHostInfo(const boost::asio::ip::tcp::endpoint& ep, HostInfo* pHostInfo);
	void SetHostInfo(const boost::asio::ip::udp::endpoint& ep, HostInfo* pHostInfo);
}


#endif // _SKCONVERT_H__
