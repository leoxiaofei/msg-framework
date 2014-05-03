#ifndef ACTPROTRESP_H__
#define ACTPROTRESP_H__


#include "actbase.h"

class ActProtResp : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData(unsigned int uHostId);

};


#endif // ACTPROTRESP_H__
