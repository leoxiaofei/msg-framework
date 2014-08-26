#include "stdafx.h"
#include "actansentry.h"
#include "..\..\Common\msgfmt.h"

bool ActAnsEntry::SendMsg(unsigned int uNetId)
{
	MsgFmt msgFmt;
	InitMsg(msgFmt);
	msgFmt.d->strAddition = "LEO";
	return SubmitMsg(msgFmt, uNetId);
}

bool ActAnsEntry::ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId)
{
	m_funcAnsEntry(uNetId);
	return false;
}

void ActAnsEntry::SetReceiveFunc(const FuncAnsEntry& funcAnsEntry)
{
	m_funcAnsEntry = funcAnsEntry;
}

