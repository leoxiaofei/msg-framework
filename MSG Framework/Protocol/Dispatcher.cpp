#include "stdafx.h"

#include "Dispatcher.h"
#include <boost/bind.hpp>

class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios):iosWork(ios){}
	boost::asio::io_service& iosWork;

};

Dispatcher::Dispatcher(boost::asio::io_service& ios)
: m_pImpl(new Impl(ios))
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::ReceiveUdpData( const std::string& strAddr, 
	unsigned int uPort, std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->iosWork.post(boost::bind(&Dispatcher::As_RecUdpData, this,
		strAddr, uPort, ptData));
}

void Dispatcher::As_RecUdpData( const std::string& strAddr, 
	unsigned int uPort, std::tr1::shared_ptr<std::stringstream> ptData )
{
	///分析来源

	///解析包

	///上传
}

bool Dispatcher::SendData( unsigned int uHostId, std::tr1::shared_ptr<std::stringstream> ptData )
{

}

bool Dispatcher::BroadcastData( std::tr1::shared_ptr<std::stringstream> ptData )
{

}

