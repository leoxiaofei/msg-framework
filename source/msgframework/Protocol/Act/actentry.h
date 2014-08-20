#ifndef _ACTENTRY_H__
#define _ACTENTRY_H__

#include "actbase.h"

class ActEntry : public ActBase
{
	ModeType(IPMSG_BR_ENTRY);

public:
	virtual bool ReceiveMsg(MsgFmt* pMsgFmt);

};


#endif // _ACTENTRY_H__
