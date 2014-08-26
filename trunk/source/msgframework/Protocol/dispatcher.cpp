#include "stdafx.h"
#include "dispatcher.h"
#include "..\Common\trafficdata.h"
#include "..\Common\msgfmt.h"
#include "Act\actbase.h"
#include "Act\actentry.h"
#include "Act\actexit.h"
#include "Act\actansentry.h"
#include <boost/bind.hpp>
#include <map>

typedef std::map<unsigned short, ActBase*> MapAct;

class Dispatcher::Impl
{
public:
	Impl(boost::asio::io_service& ios)
		: iosWork(ios)
	{}

	boost::asio::io_service& iosWork;
	MapAct mapAct;

	FuncBroadcast funcBroadcast;
	FuncSend funcSend;

	std::map<unsigned short, std::string> mapMode;
	std::map<unsigned short, std::string> mapOpt;
	std::map<unsigned short, std::string> mapSendOpt;
};

Dispatcher::Dispatcher(boost::asio::io_service& ios)
: m_pImpl(new Impl(ios))
{
	InitAct();

	m_pImpl->mapMode.insert(std::make_pair(IPMSG_NOOPERATION, "IPMSG_NOOPERATION"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_BR_ENTRY, "IPMSG_BR_ENTRY"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_BR_EXIT, "IPMSG_BR_EXIT"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_ANSENTRY, "IPMSG_ANSENTRY"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_BR_ABSENCE, "IPMSG_BR_ABSENCE"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_BR_ISGETLIST, "IPMSG_BR_ISGETLIST"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_OKGETLIST, "IPMSG_OKGETLIST"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETLIST, "IPMSG_GETLIST"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_ANSLIST, "IPMSG_ANSLIST"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_BR_ISGETLIST2, "IPMSG_BR_ISGETLIST2"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_SENDMSG, "IPMSG_SENDMSG"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_RECVMSG, "IPMSG_RECVMSG"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_READMSG, "IPMSG_READMSG"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_DELMSG, "IPMSG_DELMSG"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_ANSREADMSG, "IPMSG_ANSREADMSG"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETINFO, "IPMSG_GETINFO"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_SENDINFO, "IPMSG_SENDINFO"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETABSENCEINFO, "IPMSG_GETABSENCEINFO"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_SENDABSENCEINFO, "IPMSG_SENDABSENCEINFO"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETFILEDATA, "IPMSG_GETFILEDATA"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_RELEASEFILES, "IPMSG_RELEASEFILES"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETDIRFILES, "IPMSG_GETDIRFILES"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_GETPUBKEY, "IPMSG_GETPUBKEY"));
	m_pImpl->mapMode.insert(std::make_pair(IPMSG_ANSPUBKEY, "IPMSG_ANSPUBKEY"));


	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_ABSENCEOPT, "IPMSG_ABSENCEOPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_SERVEROPT, "IPMSG_SERVEROPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_DIALUPOPT, "IPMSG_DIALUPOPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_FILEATTACHOPT, "IPMSG_FILEATTACHOPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_ENCRYPTOPT, "IPMSG_ENCRYPTOPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_UTF8OPT, "IPMSG_UTF8OPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_CAPUTF8OPT, "IPMSG_CAPUTF8OPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_ENCEXTMSGOPT, "IPMSG_ENCEXTMSGOPT"));
	m_pImpl->mapOpt.insert(std::make_pair(IPMSG_CLIPBOARDOPT, "IPMSG_CLIPBOARDOPT"));

	/*  option for send command  */
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_SENDCHECKOPT, "IPMSG_SENDCHECKOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_SECRETOPT, "IPMSG_SECRETOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_BROADCASTOPT, "IPMSG_BROADCASTOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_MULTICASTOPT, "IPMSG_MULTICASTOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_AUTORETOPT, "IPMSG_AUTORETOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_RETRYOPT, "IPMSG_RETRYOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_PASSWORDOPT, "IPMSG_PASSWORDOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_NOLOGOPT, "IPMSG_NOLOGOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_NOADDLISTOPT, "IPMSG_NOADDLISTOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_READCHECKOPT, "IPMSG_READCHECKOPT"));
	m_pImpl->mapSendOpt.insert(std::make_pair(IPMSG_SECRETEXOPT, "IPMSG_SECRETEXOPT"));



}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId)
{
// 	std::cout << "ReceiveUdpData" << std::endl;
// 	std::cout << tfcData.GetData()->data() << std::endl;

	MsgFmt fmt;
	std::vector<char>* pData = tfcData.GetData();
	fmt.Parse(*pData);
	std::cout << m_pImpl->mapMode[fmt.d->uMode] << std::endl;
	std::cout << m_pImpl->mapOpt[fmt.d->uOpt] << std::endl;
	std::cout << m_pImpl->mapSendOpt[fmt.d->uOpt] << std::endl;
	if (ActBase* pBase = GetActBase(fmt.d->uMode))
	{
		pBase->ReceiveMsg(&fmt, uNetId);
	}
}

boost::asio::io_service& Dispatcher::GetIOs()
{
	return m_pImpl->iosWork;
}

void Dispatcher::SetUdpSendFunc(const FuncBroadcast& funcBroadcast, const FuncSend& funcSend)
{
	m_pImpl->funcBroadcast = funcBroadcast;
	m_pImpl->funcSend = funcSend;
}

void Dispatcher::SendUdpData(const TrafficData& tfcData, unsigned int uNetId)
{
// 	std::cout << "SendUdpData" << std::endl;
// 	std::cout << tfcData.GetData()->data() << std::endl;
	uNetId == 0
		? m_pImpl->funcBroadcast(tfcData)
		: m_pImpl->funcSend(tfcData, uNetId);
}

void Dispatcher::InitAct()
{
	RegAct<ActEntry>();
	RegAct<ActExit>();
	RegAct<ActAnsEntry>();
}

void Dispatcher::RegActBase(unsigned short uType, ActBase* pBase)
{
	m_pImpl->mapAct[uType] = pBase;
	pBase->funcSendUdp = boost::bind(&Dispatcher::SendUdpData, this, _1, _2);
}

ActBase* Dispatcher::GetActBase(unsigned short uType)
{
	ActBase* pBase(NULL);
	MapAct::const_iterator ciFind = m_pImpl->mapAct.find(uType);
	if (ciFind != m_pImpl->mapAct.end())
	{
		pBase = ciFind->second;
	}
	return pBase;
}

