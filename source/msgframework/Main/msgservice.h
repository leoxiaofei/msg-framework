#ifndef _MSGSERVICE_H__
#define _MSGSERVICE_H__

#include <boost/scoped_ptr.hpp>

class UdpMonitor;

class MsgService
{
	class Impl;
public:
	MsgService();
	~MsgService();

	void Start();
	void Wait();
	void Exit();

	UdpMonitor* GetUdpMonitor() const;

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _MSGSERVICE_H__
