#ifndef ACTHERE_H__
#define ACTHERE_H__

#include "Actbase.h"

class ActHere : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData(unsigned int uHostId);

};

#endif // ACTHERE_H__
