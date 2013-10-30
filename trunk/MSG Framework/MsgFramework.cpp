// MSG Framework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MsgFramework.h"
#include "MsgService.h"

#include "Socket/tcpmonitor.h"
#include "Socket/udpmonitor.h"

#include <windows.h>
#include "ProtocolService.h"
#include "Protocol/Dispatcher.h"
#include "Socket/msgsignals.h"
#include "Protocol/sendsignals.h"

char* sz = 
	"Welcome to the Boost C++ Libraries\n"
	"Boost provides free peer-reviewed portable C++ source libraries.\n"
	"We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.\n"
	"We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are already included in the C++ Standards Committee's Library Technical Report (TR1) and will be included in the upcoming revision of the C++ Standard. More Boost libraries are proposed for the upcoming TR2.\n"
	"Changes in this release\n"
	"This release includes three new libraries (Log, TTI and TypeErasure), as well as updates to many existing libraries. See Release History for more information.\n"
	"Getting Started\n"
	"If Boost hasn't already been installed on your system, follow the Getting Started Guide to complete the installation. But if you've reached to this point by installing Boost from a Windows pre-build executable or a pre-built Linux and Unix distribution package, that's already been completed. Likewise, if you're reading this on your organization's internal web server, the installation is probably already complete.\n"
	"Contents\n"
	"The release directory tree contains almost all of Boost; documentation, sources, headers, scripts, tools, and everything else a Boost user might need!\n"
	"Library Documentation\n"
	"The starting point for the documentation of individual libraries is the Libraries page, which gives a brief description of each library and links to its documentation.\n"
	"Web Site\n"
	"Some general interest or often changing Boost information lives only on the Boost web site. The release contains links to the site, so while browsing it you'll see occasional broken links if you aren't connected to the Internet. But everything needed to use the Boost libraries is contained within the release.\n"
	"Background\n"
	"Read the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.\n"
	"Community\n"
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.\n"
	"Welcome to the Boost C++ Libraries\n"
	"Boost provides free peer-reviewed portable C++ source libraries.\n"
	"We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.\n"
	"We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are already included in the C++ Standards Committee's Library Technical Report (TR1) and will be included in the upcoming revision of the C++ Standard. More Boost libraries are proposed for the upcoming TR2.\n"
	"Changes in this release\n"
	"This release includes three new libraries (Log, TTI and TypeErasure), as well as updates to many existing libraries. See Release History for more information.\n"
	"Getting Started\n"
	"If Boost hasn't already been installed on your system, follow the Getting Started Guide to complete the installation. But if you've reached to this point by installing Boost from a Windows pre-build executable or a pre-built Linux and Unix distribution package, that's already been completed. Likewise, if you're reading this on your organization's internal web server, the installation is probably already complete.\n"
	"Contents\n"
	"The release directory tree contains almost all of Boost; documentation, sources, headers, scripts, tools, and everything else a Boost user might need!\n"
	"Library Documentation\n"
	"The starting point for the documentation of individual libraries is the Libraries page, which gives a brief description of each library and links to its documentation.\n"
	"Web Site\n"
	"Some general interest or often changing Boost information lives only on the Boost web site. The release contains links to the site, so while browsing it you'll see occasional broken links if you aren't connected to the Internet. But everything needed to use the Boost libraries is contained within the release.\n"
	"Background\n"
	"Read the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.\n"
	"Community\n"
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.\n"
	"Welcome to the Boost C++ Libraries\n"
	"Boost provides free peer-reviewed portable C++ source libraries.\n"
	"We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.\n"
	"We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are already included in the C++ Standards Committee's Library Technical Report (TR1) and will be included in the upcoming revision of the C++ Standard. More Boost libraries are proposed for the upcoming TR2.\n"
	"Changes in this release\n"
	"This release includes three new libraries (Log, TTI and TypeErasure), as well as updates to many existing libraries. See Release History for more information.\n"
	"Getting Started\n"
	"If Boost hasn't already been installed on your system, follow the Getting Started Guide to complete the installation. But if you've reached to this point by installing Boost from a Windows pre-build executable or a pre-built Linux and Unix distribution package, that's already been completed. Likewise, if you're reading this on your organization's internal web server, the installation is probably already complete.\n"
	"Contents\n"
	"The release directory tree contains almost all of Boost; documentation, sources, headers, scripts, tools, and everything else a Boost user might need!\n"
	"Library Documentation\n"
	"The starting point for the documentation of individual libraries is the Libraries page, which gives a brief description of each library and links to its documentation.\n"
	"Web Site\n"
	"Some general interest or often changing Boost information lives only on the Boost web site. The release contains links to the site, so while browsing it you'll see occasional broken links if you aren't connected to the Internet. But everything needed to use the Boost libraries is contained within the release.\n"
	"Background\n"
	"Read the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.\n"
	"Community\n"
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.\n"
	"Welcome to the Boost C++ Libraries\n"
	"Boost provides free peer-reviewed portable C++ source libraries.\n"
	"We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.\n"
	"We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are already included in the C++ Standards Committee's Library Technical Report (TR1) and will be included in the upcoming revision of the C++ Standard. More Boost libraries are proposed for the upcoming TR2.\n"
	"Changes in this release\n"
	"This release includes three new libraries (Log, TTI and TypeErasure), as well as updates to many existing libraries. See Release History for more information.\n"
	"Getting Started\n"
	"If Boost hasn't already been installed on your system, follow the Getting Started Guide to complete the installation. But if you've reached to this point by installing Boost from a Windows pre-build executable or a pre-built Linux and Unix distribution package, that's already been completed. Likewise, if you're reading this on your organization's internal web server, the installation is probably already complete.\n"
	"Contents\n"
	"The release directory tree contains almost all of Boost; documentation, sources, headers, scripts, tools, and everything else a Boost user might need!\n"
	"Library Documentation\n"
	"The starting point for the documentation of individual libraries is the Libraries page, which gives a brief description of each library and links to its documentation.\n"
	"Web Site\n"
	"Some general interest or often changing Boost information lives only on the Boost web site. The release contains links to the site, so while browsing it you'll see occasional broken links if you aren't connected to the Internet. But everything needed to use the Boost libraries is contained within the release.\n"
	"Background\n"
	"Read the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.\n"
	"Community\n"
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.\n"
	"Welcome to the Boost C++ Libraries\n"
	"Boost provides free peer-reviewed portable C++ source libraries.\n"
	"We emphasize libraries that work well with the C++ Standard Library. Boost libraries are intended to be widely useful, and usable across a broad spectrum of applications. The Boost license encourages both commercial and non-commercial use.\n"
	"We aim to establish \"existing practice\" and provide reference implementations so that Boost libraries are suitable for eventual standardization. Ten Boost libraries are already included in the C++ Standards Committee's Library Technical Report (TR1) and will be included in the upcoming revision of the C++ Standard. More Boost libraries are proposed for the upcoming TR2.\n"
	"Changes in this release\n"
	"This release includes three new libraries (Log, TTI and TypeErasure), as well as updates to many existing libraries. See Release History for more information.\n"
	"Getting Started\n"
	"If Boost hasn't already been installed on your system, follow the Getting Started Guide to complete the installation. But if you've reached to this point by installing Boost from a Windows pre-build executable or a pre-built Linux and Unix distribution package, that's already been completed. Likewise, if you're reading this on your organization's internal web server, the installation is probably already complete.\n"
	"Contents\n"
	"The release directory tree contains almost all of Boost; documentation, sources, headers, scripts, tools, and everything else a Boost user might need!\n"
	"Library Documentation\n"
	"The starting point for the documentation of individual libraries is the Libraries page, which gives a brief description of each library and links to its documentation.\n"
	"Web Site\n"
	"Some general interest or often changing Boost information lives only on the Boost web site. The release contains links to the site, so while browsing it you'll see occasional broken links if you aren't connected to the Internet. But everything needed to use the Boost libraries is contained within the release.\n"
	"Background\n"
	"Read the introductory material to help you understand what Boost is about and to help in educating your organization about Boost.\n"
	"Community\n"
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.\n"
	;

int MsgFrameMain( int argc, _TCHAR* argv[] )
{
	MsgService msg;

	UdpMonitor* udp = msg.GetUdp();
	udp->Listen();

	TcpMonitor* tcp = msg.GetTcp();
	tcp->Listen();

	ProtocolService protocol;
	Dispatcher* dispatcher = protocol.GetDispatcher();


	udp->GetSignals()->ConnectReceive(boost::bind(&Dispatcher::ReceiveUdpData, 
		dispatcher,	_1, _2, _3));
	tcp->GetSignals()->ConnectReceive(boost::bind(&Dispatcher::ReceiveTcpData, 
		dispatcher,	_1, _2, _3));

	dispatcher->GetSignals()->ConnectBroadcast(boost::bind(&UdpMonitor::Broadcast, 
		udp, _1, 5123));
	dispatcher->GetSignals()->ConnectSendUdp(boost::bind(&UdpMonitor::SendTo, 
		udp, _1, _2, _3, _4));
	dispatcher->GetSignals()->ConnectSendTcp(boost::bind(&TcpMonitor::SendTo, 
		tcp, _1, _2, _3, _4));

// 	Sleep(5000);
// 
// 	service.GetTcp()->Connect("127.0.0.1");
// 	Sleep(5000);
// 	service.GetTcp()->SendTo(1, sz, strlen(sz)+1, "127.0.0.1");
// //	service.GetUdp()->SendTo(10, sz, strlen(sz)+1, "127.0.0.1");
// 	service.Wait();
	return 0;
}


