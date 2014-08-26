#include "stdafx.h"
#include "actexit.h"

bool ActExit::ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId)
{

	m_funcExit(uNetId);
	return false;
}

void ActExit::SetReceiveFunc(FuncExit funcExit)
{
	m_funcExit = funcExit;
}

bool ActExit::SendMsg()
{
// 	MsgFmt* pMsgFmt = CreateMsg();
// 
// 	return SubmitMsg(pMsgFmt, 0);
	return false;
}

