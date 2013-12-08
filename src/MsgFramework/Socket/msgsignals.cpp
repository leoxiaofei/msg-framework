#include "stdafx.h"
#include "msgsignals.h"



class MsgSignals::Impl
{
public:
	SigReceive		sigReceive;
	SigSendResult	sigSendResult;
	SigConResult	sigConResult;
};

MsgSignals::MsgSignals()
: m_pImpl(new Impl)
{

}

MsgSignals::~MsgSignals()
{

}

void MsgSignals::EmitReceive( const std::string& strAddr, 
	unsigned int uPort, std::vector<char>* ptData )
{
	m_pImpl->sigReceive(strAddr, uPort, ptData);

}

void MsgSignals::ConnectReceive( const SlotReceive& pFunc )
{
	m_pImpl->sigReceive.connect(pFunc);
}

void MsgSignals::EmitSendResult(unsigned int uOrder, int nResultFlag)
{
	m_pImpl->sigSendResult(uOrder, nResultFlag);
}

void MsgSignals::ConnectSendResult( const SlotSendResult& pFunc )
{
	m_pImpl->sigSendResult.connect(pFunc);
}

void MsgSignals::ConnectConResult( const SlotConResult& pFunc )
{
	m_pImpl->sigConResult.connect(pFunc);
}

void MsgSignals::EmitConResult( const std::string& strAddr, unsigned int uPort, bool bSuccess )
{
	m_pImpl->sigConResult(strAddr, uPort, bSuccess);
}

