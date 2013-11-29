#include "stdafx.h"
#include "ProtSet.h"
#include "ProtocolBase.h"

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

	///vecProtDisp->准备接收器


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

