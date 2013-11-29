#ifndef PROTOCOLBASE_H__
#define PROTOCOLBASE_H__

#include <memory>

class ProtocolBase
{
public:
	virtual ~ProtocolBase(){};
	virtual bool SendData(std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;
	virtual bool ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;

	virtual bool NeedReady() { return false; };
	virtual void GetReadyData(std::stringstream& ptStream) {};
	virtual void SetReadyData(std::stringstream& ptStream) {};

};


#endif // PROTOCOLBASE_H__
