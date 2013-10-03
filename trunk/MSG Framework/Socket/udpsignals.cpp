#include "stdafx.h"
#include "udpsignals.h"



class UdpSignals::Impl
{
public:
	SigReceive sigReceive;

};

UdpSignals::UdpSignals()
: m_pImpl(new Impl)
{

}

UdpSignals::~UdpSignals()
{

}

void UdpSignals::EmitReceive( const std::string& strAddr, 
	unsigned int uPort, std::tr1::shared_ptr<std::stringstream> ptData )
{
	m_pImpl->sigReceive(strAddr, uPort, ptData);

}

void UdpSignals::ConnectReceive( const SlotReceive& pFunc )
{
	m_pImpl->sigReceive.connect(pFunc);
}

