#ifndef _ACTBASE_H__
#define _ACTBASE_H__

#include "../ipmsg.h"
#include <boost/function.hpp>

class MsgFmt;
class TrafficData;
typedef boost::function<void(const TrafficData& tfcData, unsigned int uNetId)> FuncSend;

#define ModeType(x) public: enum { Type = (x) }; virtual int GetType() const { return Type; } 


class ActBase
{
public:
	virtual int GetType() const = 0 ;
	virtual bool ReceiveMsg( MsgFmt* pMsgFmt, unsigned int uNetId ) = 0;

protected:
	void InitMsg(MsgFmt& msgFmt);
	bool SubmitMsg(const MsgFmt& msgFmt, unsigned int uNetId);
	virtual int GetOpt() const;

private:

	FuncSend funcSendUdp;
	friend class Dispatcher;
};


#endif // _ACTBASE_H__
