#include "stdafx.h"
#include "udpmonitor.h"

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/tags/tagged.hpp>
#include "../Tools/idcreater.hpp"
#include "../Common/trafficdata.h"

using namespace boost::asio;
using boost::shared_ptr;

typedef boost::bimap<ip::udp::endpoint, unsigned int> UdpEndPoint;

class UdpMonitor::Impl
{
public:
	Impl(io_service& io)
	: ios(io)
	, icNetId(0)
	{}

	io_service& ios;
	shared_ptr<ip::udp::socket> ptListen;
	ip::udp::endpoint epReceive;
	UdpEndPoint biUdpEndPoint;

	IdCreater<unsigned int> icNetId;

	FuncReceive funcReceive;
};

UdpMonitor::UdpMonitor(boost::asio::io_service& io)
: m_pImpl(new Impl(io))
{
}

UdpMonitor::~UdpMonitor()
{

}

bool UdpMonitor::Listen(unsigned short uPort)
{
	bool bRet(false);
	try
	{
		m_pImpl->ptListen = boost::make_shared<ip::udp::socket>
			(m_pImpl->ios, ip::udp::endpoint(ip::udp::v4(), uPort));
		m_pImpl->ptListen->set_option(socket_base::broadcast(true));
		m_pImpl->ptListen->set_option(ip::udp::socket::reuse_address(true));
		ReadyRead();
		bRet = true;
	}
	catch (boost::system::system_error& e)
	{
	}
	catch (...)
	{
	}

	return bRet;
}

void UdpMonitor::ReadyRead()
{
	TrafficData tfcData;
	std::vector<char>* pData = tfcData.GetData();
	pData->assign(1024, 0);
	m_pImpl->ptListen->async_receive_from(buffer(*pData), m_pImpl->epReceive,
		boost::bind(&UdpMonitor::ReadHandler, this, placeholders::error, placeholders::bytes_transferred, tfcData));
}

void UdpMonitor::ReadHandler(const boost::system::error_code& ec, std::size_t packet_bytes, const TrafficData& tfcData)
{
	if (ec)
	{
		return;
	}

	unsigned int uNetId(0);

	UdpEndPoint::left_const_iterator lciFind = m_pImpl->biUdpEndPoint.left.find(m_pImpl->epReceive);
	if (lciFind != m_pImpl->biUdpEndPoint.left.end())
	{
		uNetId = lciFind->second;
	}
	else
	{
		uNetId = m_pImpl->icNetId();
		m_pImpl->biUdpEndPoint.insert(UdpEndPoint::value_type(m_pImpl->epReceive, uNetId));
	}

	tfcData.GetData()->resize(packet_bytes);
	m_pImpl->funcReceive(tfcData, uNetId);

	ReadyRead();
}

void UdpMonitor::SetReceiveFunc(const FuncReceive& funcReceive)
{
	m_pImpl->funcReceive = funcReceive;
}

void UdpMonitor::SendData(const TrafficData& tfcData, unsigned int uNetId)
{
	UdpEndPoint::right_const_iterator rciFind = m_pImpl->biUdpEndPoint.right.find(uNetId);
	if (rciFind != m_pImpl->biUdpEndPoint.right.end())
	{
		std::vector<char>* pData = tfcData.GetData();
		m_pImpl->ptListen->async_send_to(buffer(*pData), rciFind->second,
			boost::bind(&UdpMonitor::SendHandler, this, placeholders::error, tfcData));
	}
}

void UdpMonitor::BroadcastData(const TrafficData& tfcData)
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), 2425);
	std::vector<char>* pData = tfcData.GetData();
	m_pImpl->ptListen->async_send_to(buffer(*pData), senderEndpoint,
		boost::bind(&UdpMonitor::SendHandler, this, placeholders::error, tfcData));
}

void UdpMonitor::SendHandler(const boost::system::error_code& ec, const TrafficData& tfcData)
{
	if (ec)
	{
		return;
	}
}
