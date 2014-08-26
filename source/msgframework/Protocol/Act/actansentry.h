#ifndef _ACTANSENTRY_H__
#define _ACTANSENTRY_H__



#include "actbase.h"

typedef boost::function<void(unsigned int)> FuncAnsEntry;

class ActAnsEntry : public ActBase
{
	ModeType(IPMSG_ANSENTRY);

public:
	bool SendMsg(unsigned int uNetId);
	virtual bool ReceiveMsg(MsgFmt* pMsgFmt, unsigned int uNetId);

	void SetReceiveFunc(const FuncAnsEntry& funcAnsEntry);

private:
	FuncAnsEntry m_funcAnsEntry;
};


#endif // _ACTANSENTRY_H__
