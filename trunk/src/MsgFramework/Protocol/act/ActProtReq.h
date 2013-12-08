#ifndef ACTPROTREQ_H__
#define ACTPROTREQ_H__


#include "Actbase.h"

class ActProtReq : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData(unsigned int uHostId);

};



#endif // ACTPROTREQ_H__
