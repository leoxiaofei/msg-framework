#include "stdafx.h"
#include "ProtSet.h"
#include "ProtocolBase.h"
#include "ProtManager.h"

typedef std::vector<std::tr1::shared_ptr<ProtocolBase> > ProtCont;


class ProtSet::Impl
{
public:
	ProtCont contSender;
	ProtCont contReceiver;

};


ProtSet::ProtSet()
: m_pImpl(new Impl)
{

}

ProtSet::~ProtSet()
{

}

void ProtSet::Prepare(unsigned short uVersion, const std::vector<unsigned short>& vecProtDisp)
{
	///uVersion->准备发送器
	ProtManager::Instance().GetLoacalProtocal(uVersion, m_pImpl->contSender);

	///vecProtDisp->准备接收器
	ProtManager::Instance().GetRemoteProtocal(vecProtDisp, m_pImpl->contReceiver);

}

bool ProtSet::NeedReady()
{
	bool bRet(false);
	for (ProtCont::const_iterator citor = m_pImpl->contSender.begin();
		citor != m_pImpl->contSender.end(); ++citor)
	{
		if ((*citor)->NeedReady())
		{
			bRet = true;
			break;
		}
	}
	return bRet;
}

