#ifndef PROTOCOLBASE_H__
#define PROTOCOLBASE_H__

#include "../../Tools/vectordevice.h"


class ProtocolBase
{
public:
	virtual ~ProtocolBase(){};
	virtual bool SendData(std::vector<char>*& pData) = 0;
	virtual bool ReceiveData(std::vector<char>*& pData) = 0;
	virtual int GetType() = 0;

	virtual bool NeedReady() { return false; };
	virtual void GetReadyData(Msg::MsgStream& stream) {};
	virtual void SetReadyData(Msg::MsgStream& stream) {};

};


#endif // PROTOCOLBASE_H__
