#ifndef _ACTEXIT_H__
#define _ACTEXIT_H__


#include "actbase.h"

typedef boost::function<void(unsigned int)> FuncExit;

class ActExit : public ActBase
{
	ModeType(IPMSG_BR_EXIT);

public:
	bool SendMsg();

	virtual bool ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId);

	void SetReceiveFunc(FuncExit funcExit);

private:
	FuncExit m_funcExit;
};



#endif // _ACTEXIT_H__
