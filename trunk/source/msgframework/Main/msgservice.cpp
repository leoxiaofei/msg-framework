#include "stdafx.h"

#include "msgservice.h"

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../Socket/udpmonitor.h"

typedef std::vector<boost::shared_ptr<boost::thread> > ThreadContainer;
class MsgService::Impl
{
public:
	Impl()
	: uThreadPoolSize(2)
	, wkWork(new boost::asio::io_service::work(iosWork))
	, udpMonitor(iosWork)
	{}

	//////////////////////////////////////////////////////////////////////////
	boost::asio::io_service iosWork;								///io_service����
	boost::scoped_ptr<boost::asio::io_service::work> wkWork;		///�����ڷ�ֹiosWorkΪ��ʱ�߳̽����Ķ���

	unsigned int uThreadPoolSize;									///�̳߳ش�С
	ThreadContainer contThread;										///�߳�����

	UdpMonitor udpMonitor;
};

MsgService::MsgService()
: m_pImpl(new Impl)
{
}

MsgService::~MsgService()
{

}

void MsgService::Start()
{
	for (unsigned int ix = 0; ix != m_pImpl->uThreadPoolSize; ++ix)
	{
		m_pImpl->contThread.push_back(boost::make_shared<boost::thread>
			(boost::bind(&boost::asio::io_service::run, &m_pImpl->iosWork)));
	}
}

void MsgService::Exit()
{
	m_pImpl->iosWork.stop();
}

void MsgService::Wait()
{
	for (ThreadContainer::const_iterator citor = m_pImpl->contThread.begin();
		citor != m_pImpl->contThread.end(); ++citor)
	{
		(*citor)->join();
	}
}

UdpMonitor* MsgService::GetUdpMonitor() const
{
	return &m_pImpl->udpMonitor;
}
