#include "StdAfx.h"
#include "MsgService.h"

#include "../Socket/tcpmonitor.h"
#include "../Socket/udpmonitor.h"

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>


class MsgService::Impl
{
public:
	Impl()
		: wkWork(new boost::asio::io_service::work(iosWork))
		, thdWork(new boost::thread(
			boost::bind(&boost::asio::io_service::run, &iosWork)))
		, udpMsg(iosWork)
		, tcpMsg(iosWork)
	{}

	//////////////////////////////////////////////////////////////////////////
	///工作者线程
	boost::asio::io_service iosWork;
	boost::scoped_ptr<boost::asio::io_service::work> wkWork;
	boost::scoped_ptr<boost::thread> thdWork;

	UdpMonitor udpMsg;
	TcpMonitor tcpMsg;
};

MsgService::MsgService(void)
: m_pImpl(new Impl)
{

}


MsgService::~MsgService(void)
{
}

void MsgService::Exit()
{
	m_pImpl->iosWork.stop();
	m_pImpl->thdWork->join();
}

void MsgService::Wait()
{
	m_pImpl->thdWork->join();
}

UdpMonitor* MsgService::GetUdp()
{
	return &m_pImpl->udpMsg;
}

TcpMonitor* MsgService::GetTcp()
{
	return &m_pImpl->tcpMsg;
}
