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


int MsgFrameEntry( int argc, _TCHAR* argv[] )
{
	MsgService srv;
	ProtocolService prot;
	srv.Start();
	prot.Start();
	srv.GetUdpMonitor()->Listen(2425);
	srv.GetUdpMonitor()->SetReceiveFunc(boost::bind(&Dispatcher::as_ReceiveUdpData, prot.GetDispatcher(), _1, _2));

// 	prot.Exit();
// 	srv.Exit();
	prot.Wait();
 	srv.Wait();
	return 0;
}


