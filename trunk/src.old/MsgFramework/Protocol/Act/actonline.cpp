#include "stdafx.h"
#include "actonline.h"
#include "../agreement.h"
#include "../../Common/vcpool.h"
#include "../actor.h"
#include "../../Tools/vectordevice.h"
#include "../../Tools/generalserialize.hpp"
#include "../protset.h"


#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using boost::archive::binary_oarchive; // saving
using boost::archive::binary_iarchive; // loading

ActOnline::ActOnline(Actor* pActor)
: ActBase(pActor)
{

}


int ActOnline::GetType()
{
	return Agreement::PA_ONLINE;
}

void ActOnline::ReceiveData(unsigned int uHostId, std::vector<char>* ptData)
{
	std::vector<char>* pData = VcPool::Instance().New();
	Msg::MsgStream msgStream(*pData);
	unsigned short uRemoteVersion;
	std::vector<unsigned short> vecUseProtocol;
	msgStream >> uRemoteVersion;
	binary_iarchive ia(msgStream);
	ia >> vecUseProtocol;


}

void ActOnline::SendData()
{
	std::vector<char>* pData = VcPool::Instance().New();
	Msg::MsgStream msgStream(*pData);
	msgStream << ProtSet::Instance().GetLocalVersion();
	binary_oarchive oa(msgStream);
	oa << ProtSet::Instance().GetUseProtocol();
	m_pActor->SendData(0, GetType(), pData);
}

