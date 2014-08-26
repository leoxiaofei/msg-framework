#ifndef _ACTSENDMSG_H__
#define _ACTSENDMSG_H__


#include "actbase.h"

typedef boost::function<void(unsigned int)> FuncAnsEntry;

class ActSendMsg : public ActBase
{
	ModeType(IPMSG_SENDMSG);

public:
	bool SendMsg(unsigned int uNetId);
	virtual bool ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId);

	void SetReceiveFunc(const FuncAnsEntry& funcAnsEntry);

private:
	FuncAnsEntry m_funcAnsEntry;
};



#endif // _ACTSENDMSG_H__
