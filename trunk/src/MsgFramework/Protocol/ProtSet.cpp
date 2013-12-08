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

void ProtSet::GetReadyData(std::vector<char>& data)
{
	Msg::MsgStream msgStream(data);
	for (ProtCont::const_iterator citor = m_pImpl->contReceiver.begin();
		citor != m_pImpl->contReceiver.end(); ++citor)
	{
		if ((*citor)->NeedReady())
		{
			(*citor)->GetReadyData(msgStream);
		}
	}
}

void ProtSet::SetReadyData(std::vector<char>& data)
{
	Msg::MsgStream msgStream(data);
	for (ProtCont::const_iterator citor = m_pImpl->contSender.begin();
		citor != m_pImpl->contSender.end(); ++citor)
	{
		if ((*citor)->NeedReady())
		{
			(*citor)->SetReadyData(msgStream);
		}
	}
}

