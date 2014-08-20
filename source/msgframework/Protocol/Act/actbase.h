#ifndef _ACTBASE_H__
#define _ACTBASE_H__

#include "../ipmsg.h"

#define ModeType(x) public: enum { Type = (x) }; virtual int GetType() { return Type; } 

class MsgFmt;

class ActBase
{
public:
	virtual int GetType() = 0;
	virtual bool ReceiveMsg( MsgFmt* pMsgFmt ) = 0;

protected:
	MsgFmt* CreateMsg();
	bool SendMsg(MsgFmt* pMsgFmt);

};


#endif // _ACTBASE_H__
