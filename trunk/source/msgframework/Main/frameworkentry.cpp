// MSG Framework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "frameworkentry.h"
#include "msgservice.h"
#include "protocolservice.h"
#include "..\Protocol\dispatcher.h"
#include "..\Socket\udpmonitor.h"
#include "..\Common\trafficdata.h"

#include <boost/bind.hpp>
#include <vector>
#include "../Tools/vectordevice.h"
#include "../Common/globaldata.h"
#include "../Common/msgver.h"

int MsgFrameEntry( int argc, _TCHAR* argv[] )
{
	GD::strUserName = "leoxiaofei";
	GD::strComputer = "Xiaofei-E31230";
	FeiQVer* pFeiQVer = new FeiQVer;
	pFeiQVer->strMacAddr = "001122334455";
	pFeiQVer->uAvatar = 1;
	pFeiQVer->uRank = 128;
	pFeiQVer->uUnknow1 = 0;
	pFeiQVer->uUnknow2 = 0;
	pFeiQVer->uUnknow3 = 0;
	pFeiQVer->uUnknow4 = 4001;
	pFeiQVer->uUnknow5 = 9;
	GD::ptMsgVar = boost::shared_ptr<MsgVerBase>(pFeiQVer);

	MsgService srv;
	ProtocolService prot;
	srv.Start();
	prot.Start();
	srv.GetUdpMonitor()->Listen(2425);
	srv.GetUdpMonitor()->SetReceiveFunc(boost::bind(&Dispatcher::as_ReceiveUdpData, prot.GetDispatcher(), _1, _2));
	prot.GetDispatcher()->SetUdpSendFunc(
		boost::bind(&UdpMonitor::BroadcastData, srv.GetUdpMonitor(), _1),
		boost::bind(&UdpMonitor::SendData, srv.GetUdpMonitor(), _1, _2));
// 	prot.Exit();
// 	srv.Exit();
	prot.Wait();
 	srv.Wait();
	return 0;
}


