#ifndef _ACTENTRY_H__
#define _ACTENTRY_H__

#include "actbase.h"

typedef boost::function<void(unsigned int)> FuncEntry;

class ActEntry : public ActBase
{
	ModeType(IPMSG_BR_ENTRY);

public:
	bool SendMsg();
	virtual bool ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId);

	void SetReceiveFunc(FuncEntry funcEntry);

private:
	FuncEntry m_funcEntry;
};


#endif // _ACTENTRY_H__
