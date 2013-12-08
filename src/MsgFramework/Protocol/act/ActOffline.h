#ifndef ACTOFFLINE_H__
#define ACTOFFLINE_H__

#include "Actbase.h"

class ActOffline : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData();

};


#endif // ACTOFFLINE_H__
