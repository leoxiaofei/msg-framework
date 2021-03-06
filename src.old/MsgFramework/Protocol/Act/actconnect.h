#ifndef ACTCONNECT_H__
#define ACTCONNECT_H__

#include "actbase.h"

class ActConnect : public ActBase
{
public:
	ActConnect(Actor* pActor);
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData(unsigned int uHostId);

};

#endif // ACTCONNECT_H__
