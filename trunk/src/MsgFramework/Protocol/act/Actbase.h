#ifndef ACTBASE_H__
#define ACTBASE_H__

#include <boost\function.hpp>
#include <vector>

class ActBase
{
public:
	virtual ~ActBase(){};

	typedef boost::function<unsigned int (unsigned int, unsigned short,
		std::vector<char>*) > FuncSend;

	void SetSender(const FuncSend& sendFunc)
	{
		m_sendFunc = sendFunc;
	}

	virtual int GetType() = 0;
	virtual void ReceiveData(unsigned int uHostId, std::vector<char>* ptData) = 0;

protected:
	FuncSend m_sendFunc;
};


#endif // ACTBASE_H__
