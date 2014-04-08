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

void MsgSignals::EmitReceive(unsigned int uHostId, std::vector<char>* ptData)
{
	m_pImpl->sigReceive(uHostId, ptData);
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

void MsgSignals::EmitConResult(unsigned int uHostId, bool bSuccess)
{
	m_pImpl->sigConResult(uHostId, bSuccess);
}

