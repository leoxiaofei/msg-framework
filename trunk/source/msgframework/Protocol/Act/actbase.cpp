#include "stdafx.h"
#include "actbase.h"

#include "..\..\Tools\mspool.hpp"
#include "..\..\Common\msgfmt.h"
#include "..\..\Common\trafficdata.h"
#include "..\..\Common\globaldata.h"
#include "../../Common/msgver.h"
#include <algorithm>
#include <boost/shared_ptr.hpp>


bool ActBase::SubmitMsg(const MsgFmt& msgFmt, unsigned int uNetId)
{
	TrafficData td;
	msgFmt.Packet(*td.GetData());
	funcSendUdp(td, uNetId);
	return true;
}

void ActBase::InitMsg(MsgFmt& msgFmt)
{
	MsgFmtData* d = msgFmt.d;
	d->uMode = GetType();
	d->uOpt = GetOpt();
	d->strUser = GD::strUserName;
	d->strComputer = GD::strComputer;
	GD::uLastBagNum = std::max<unsigned int>((unsigned int)time(NULL), GD::uLastBagNum + 1);
	d->uBagNum = GD::uLastBagNum;
	d->ptMsgVer = GD::ptMsgVar;
}

int ActBase::GetOpt() const
{
	return 0;
}

