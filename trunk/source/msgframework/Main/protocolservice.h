#ifndef _PROTOCOLSERVICE_H__
#define _PROTOCOLSERVICE_H__

#include <boost/scoped_ptr.hpp>

class Dispatcher;
class Actor;

class ProtocolService
{
	class Impl;
public:
	ProtocolService();
	~ProtocolService();

	void Start();
	void Wait();
	void Exit();

	Dispatcher* GetDispatcher() const;
	Actor*      GetActor() const;

protected:
	void Init();

private:
	boost::scoped_ptr<Impl> m_pImpl;
};



#endif // _PROTOCOLSERVICE_H__
