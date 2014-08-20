#include "stdafx.h"
#include "protproc.h"
#include "protset.h"
#include "Dis/protocolbase.h"

typedef std::vector<std::tr1::shared_ptr<ProtocolBase> > ProtCont;


class ProtProc::Impl
{
public:
	ProtCont contSender;
	ProtCont contReceiver;

};


ProtProc::ProtProc()
: m_pImpl(new Impl)
{

}

ProtProc::~ProtProc()
{

}

void ProtProc::Prepare(unsigned short uVersion, const std::vector<unsigned short>& vecProtDisp)
{
	///uVersion->准备发送器
	ProtSet::Instance().GetLocalProtocal(uVersion, m_pImpl->contSender);

	///vecProtDisp->准备接收器
	ProtSet::Instance().GetRemoteProtocal(vecProtDisp, m_pImpl->contReceiver);

}

void ProtProc::GetReadyData(std::vector<char>& data)
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

void ProtProc::SetReadyData(std::vector<char>& data)
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

