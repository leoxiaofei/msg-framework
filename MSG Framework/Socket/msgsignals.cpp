#include "stdafx.h"
#include "msgsignals.h"



class MsgSignals::Impl
{
public:
	SigReceive sigReceive;
	SigError   sigError;
	SigConResult sigConResult;
};

MsgSignals::MsgSignals()
: m_pImpl(new Impl)
{

}

MsgSignals::~MsgSignals()
{

}

void MsgSignals::EmitReceive( const std::string& strAddr, 
	unsigned int uPort, const std::tr1::shared_ptr<std::stringstream>& ptData )
{
	m_pImpl->sigReceive(strAddr, uPort, ptData);

}

void MsgSignals::ConnectReceive( const SlotReceive& pFunc )
{
	m_pImpl->sigReceive.connect(pFunc);
}

void MsgSignals::EmitSendError( unsigned int uOrder, unsigned int uErrorFlag )
{
	m_pImpl->sigError(uOrder, uErrorFlag);
}

void MsgSignals::ConnectSendError( const SlotError& pFunc )
{
	m_pImpl->sigError.connect(pFunc);
}

void MsgSignals::ConnectConResult( const SlotConResult& pFunc )
{
	m_pImpl->sigConResult.connect(pFunc);
}

void MsgSignals::EmitConResult( const std::string& strAddr, unsigned int uPort, bool bSuccess )
{
	m_pImpl->sigConResult(strAddr, uPort, bSuccess);
}

