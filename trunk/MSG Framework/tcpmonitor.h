#ifndef TCPMONITOR_H__
#define TCPMONITOR_H__

#include <memory>

class TcpMonitor
{
	class Impl;
public:
	TcpMonitor();
	~TcpMonitor();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // TCPMONITOR_H__
