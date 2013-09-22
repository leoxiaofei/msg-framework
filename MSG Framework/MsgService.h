#ifndef NETSERVICE_H__
#define NETSERVICE_H__

class UdpMonitor;
class TcpMonitor;

class MsgService
{
	class Impl;
public:
	MsgService(void);
	~MsgService(void);

	void Wait();
	void Exit();

	UdpMonitor* GetUdp();
	TcpMonitor* GetTcp();

private:
	boost::scoped_ptr<Impl> m_pImpl;
};

#endif // NETSERVICE_H__
