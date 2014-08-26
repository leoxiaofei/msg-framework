#include "stdafx.h"
#include "actentry.h"
#include "..\..\Common\msgfmt.h"

#include <iostream>
#include <string>

bool ActEntry::SendMsg()
{
	MsgFmt msgFmt;
	InitMsg(msgFmt);
	msgFmt.d->strAddition = "LEO";
	return SubmitMsg(msgFmt, 0);
}

bool ActEntry::ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId)
{
// 	std::cout << pMsgFmt->uBagNum << std::endl;
// 	std::cout << pMsgFmt->strUser << std::endl;
// 	std::cout << pMsgFmt->strComputer << std::endl;
// 	std::cout << pMsgFmt->uMode << std::endl;
// 	std::cout << pMsgFmt->uOpt << std::endl;
// 	std::cout << pMsgFmt->strAddition << std::endl;
//	std::reverse(pMsgFmt->strUser.begin(), pMsgFmt->strUser.end());
// 	std::reverse(pMsgFmt->strComputer.begin(), pMsgFmt->strComputer.end());
// 	SubmitMsg(pMsgFmt, uNetId);

	m_funcEntry(uNetId);

	return false;
}

void ActEntry::SetReceiveFunc(FuncEntry funcEntry)
{
	m_funcEntry = funcEntry;
}
