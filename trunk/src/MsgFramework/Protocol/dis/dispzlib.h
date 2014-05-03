#ifndef DISPZLIB_H__
#define DISPZLIB_H__

#include "protocolbase.h"


class DispZlib : public ProtocolBase
{
public:
	virtual bool SendData(std::vector<char>*& pData);

	virtual bool ReceiveData(std::vector<char>*& pData);

	virtual int  GetType();

};


#endif // DISPZLIB_H__
