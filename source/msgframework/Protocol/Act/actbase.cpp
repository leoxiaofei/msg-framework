#include "stdafx.h"
#include "actbase.h"

#include "..\..\Tools\mspool.hpp"
#include "..\..\Common\msgfmt.h"

typedef MsPool<struct pool_tag, MsgFmt > MFP;


MsgFmt* ActBase::CreateMsg()
{
	MsgFmt* pMsgFmt = MFP::New();
	pMsgFmt->Clear();
	
	return pMsgFmt;
}

bool ActBase::SendMsg(MsgFmt* pMsgFmt)
{
	return false;
}

