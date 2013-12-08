#ifndef ACTONLINE_H__
#define ACTONLINE_H__


#include "Actbase.h"

class ActOnline : public ActBase
{
public:
	virtual int GetType();
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData);

	void SendData();

};

#endif // ACTONLINE_H__
