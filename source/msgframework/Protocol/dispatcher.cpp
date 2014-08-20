#include "stdafx.h"
#include "dispatcher.h"
#include "..\Common\trafficdata.h"
#include <ostream>
#include "..\Common\msgfmt.h"
#include "actor.h"
#include "..\Tools\mspool.hpp"
#include "act\actbase.h"

typedef MsPool<struct pool_tag, MsgFmt > MFP;


class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios)
		: iosWork(ios)
		, actor(ios){}

	boost::asio::io_service& iosWork;
	Actor actor;
};

Dispatcher::Dispatcher(boost::asio::io_service& ios)
: m_pImpl(new Impl(ios))
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId)
{
	std::cout << tfcData.GetData()->data() << std::endl;

	MsgFmt* pFmt = MFP::New();
	pFmt->Clear();
	std::vector<char>* pData = tfcData.GetData();
	pFmt->Parse(*pData);
	if (ActBase* pBase = m_pImpl->actor.GetActBase(pFmt->uMode))
	{
		pBase->ReceiveMsg(pFmt);
	}
	MFP::Free(pFmt);

}

boost::asio::io_service& Dispatcher::GetIOs()
{
	return m_pImpl->iosWork;
}