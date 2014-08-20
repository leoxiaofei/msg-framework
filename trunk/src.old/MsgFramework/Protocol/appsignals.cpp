#include "stdafx.h"
#include "appsignals.h"

class AppSignals::Impl
{
public:
	SigReceive sigReceive;
	SigError   sigError;
	SigConResult sigConResult;

};

AppSignals::AppSignals()
: m_pImpl(new Impl)
{

}

AppSignals::~AppSignals()
{

}

void AppSignals::ConnectReceive( const SlotReceive& pFunc )
{
	m_pImpl->sigReceive.connect(pFunc);
}

void AppSignals::EmitReceive( unsigned int uHostId, std::vector<char>* ptData )
{
	m_pImpl->sigReceive(uHostId, ptData);
}

void AppSignals::ConnectConResult( const SlotConResult& pFunc )
{
	m_pImpl->sigConResult.connect(pFunc);
}

void AppSignals::EmitConResult( const std::string& strAddr, unsigned int uPort, unsigned int uHostId )
{
	m_pImpl->sigConResult(strAddr, uPort, uHostId);
}

void AppSignals::ConnectSendError( const SlotError& pFunc )
{
	m_pImpl->sigError.connect(pFunc);
}

void AppSignals::EmitSendError( unsigned int uOrder, unsigned int uErrorFlag )
{
	m_pImpl->sigError(uOrder, uErrorFlag);
}

