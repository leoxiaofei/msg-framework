#ifndef ACTCALL_H__
#define ACTCALL_H__

#include "Actbase.h"

class ActCall : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData();

};

#endif // ACTCALL_H__
