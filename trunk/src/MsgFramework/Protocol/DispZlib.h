#ifndef DISPZLIB_H__
#define DISPZLIB_H__

#include "ProtocolBase.h"


class DispZlib : public ProtocolBase
{
public:
	virtual bool SendData(std::tr1::shared_ptr<std::stringstream>& ptStream);
	virtual bool ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream);
	virtual int  GetType();

};


#endif // DISPZLIB_H__
