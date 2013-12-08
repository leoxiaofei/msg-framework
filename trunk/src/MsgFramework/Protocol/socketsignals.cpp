#include "stdafx.h"

#include "socketsignals.h"


class SocketSignals::Impl
{
public:
	SigSend sigSendUdp;
	SigSend sigSendTcp;
	SigBroadcast sigBroadcast;
	SigConnect sigTcpConnect;
};

SocketSignals::SocketSignals()
: m_pImpl(new Impl)
{

}

SocketSignals::~SocketSignals()
{

}

void SocketSignals::ConnectSendUdp( const SlotSend& pFunc )
{
	m_pImpl->sigSendUdp.connect(pFunc);
}

void SocketSignals::EmitSendUdp( unsigned int uOrder, std::vector<char>* ptData,
	const std::string& strAddr, unsigned short uPort )
{
	m_pImpl->sigSendUdp(uOrder, ptData, strAddr, uPort);
}

void SocketSignals::ConnectSendTcp( const SlotSend& pFunc )
{
	m_pImpl->sigSendTcp.connect(pFunc);
}

void SocketSignals::EmitSendTcp( unsigned int uOrder, std::vector<char>* ptData,
	const std::string& strAddr, unsigned short uPort )
{
	m_pImpl->sigSendTcp(uOrder, ptData, strAddr, uPort);
}

void SocketSignals::ConnectBroadcast( const SlotBroadcast& pFunc )
{
	m_pImpl->sigBroadcast.connect(pFunc);
}

void SocketSignals::EmitBroadcast( std::vector<char>* ptData )
{
	m_pImpl->sigBroadcast(ptData);
}

void SocketSignals::ConnectTcpConnect( const SlotConnect& pFunc )
{
	m_pImpl->sigTcpConnect.connect(pFunc);
}

void SocketSignals::EmitTcpConnect( const std::string& strIp, unsigned short uPort )
{
	m_pImpl->sigTcpConnect(strIp, uPort);
}

