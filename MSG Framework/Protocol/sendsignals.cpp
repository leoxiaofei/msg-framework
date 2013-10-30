#include "stdafx.h"

#include "sendsignals.h"


class SendSignals::Impl
{
public:
	SigSend sigSendUdp;
	SigSend sigSendTcp;
	SigBroadcast sigBroadcast;
};

SendSignals::SendSignals()
: m_pImpl(new Impl)
{

}

SendSignals::~SendSignals()
{

}

void SendSignals::ConnectSendUdp( const SlotSend& pFunc )
{
	m_pImpl->sigSendUdp.connect(pFunc);
}

void SendSignals::EmitSendUdp( unsigned int uOrder, const std::tr1::shared_ptr<std::stringstream>& ptData,
	const std::string& strAddr, unsigned short uPort )
{
	m_pImpl->sigSendUdp(uOrder, ptData, strAddr, uPort);
}

void SendSignals::ConnectSendTcp( const SlotSend& pFunc )
{
	m_pImpl->sigSendTcp.connect(pFunc);
}

void SendSignals::EmitSendTcp( unsigned int uOrder, const std::tr1::shared_ptr<std::stringstream>& ptData,
	const std::string& strAddr, unsigned short uPort )
{
	m_pImpl->sigSendTcp(uOrder, ptData, strAddr, uPort);
}

void SendSignals::ConnectBroadcast( const SlotBroadcast& pFunc )
{
	m_pImpl->sigBroadcast.connect(pFunc);
}

void SendSignals::EmitBroadcast( const std::tr1::shared_ptr<std::stringstream>& ptData )
{
	m_pImpl->sigBroadcast(ptData);
}

