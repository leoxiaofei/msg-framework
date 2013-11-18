#ifndef PROTOCOLBASE_H__
#define PROTOCOLBASE_H__

#include <memory>

class ProtocolBase
{
public:
	virtual ~ProtocolBase();
	virtual bool SendData(std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;
	virtual bool ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;

	virtual bool NeedReady() = 0;
	virtual void GetReadyData(std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;
	virtual void SetReadyData(const std::tr1::shared_ptr<std::stringstream>& ptStream) = 0;
	virtual bool IsReady() = 0;

};


#endif // PROTOCOLBASE_H__
