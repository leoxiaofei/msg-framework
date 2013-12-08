// MSG Framework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MsgFramework.h"
#include "MsgService.h"

#include "../Socket/tcpmonitor.h"
#include "../Socket/udpmonitor.h"
#include "../Protocol/Dispatcher.h"
#include "../Socket/msgsignals.h"
#include "../Protocol/socketsignals.h"
#include "ProtocolService.h"

#include <windows.h>
#include "../Socket/constant.h"
#include "../Protocol/DispZlib.h"
#include <boost/iostreams/stream.hpp> 

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
	"Boost welcomes and thrives on participation from a variety of individuals and organizations. Many avenues for participation are available in the Boost Community.1\n"
	;

int MsgFrameMain( int argc, _TCHAR* argv[] )
{

// 
// 	stream << str;
// 	stream.clear();
// 	stream.seekg(0);
// 	stream.seekp(0);
// 	char szXor = 111;
// 	char sz;
// 	while (stream >> sz)
// 	{
// 		stream << (char)(sz ^ szXor);
// 	}
// 	str = stream.str();
// 	stream.clear();
// 	stream.seekg(0);
// 	stream.seekp(0);
// 	while (stream >> sz)
// 	{
// 		stream << (char)(sz ^ szXor);
// 	}
// 	str = stream.str();

// 	int first, second;
// 	while(1)
// 	{   
// 		//clear()，这个名字让很多人想当然地认为它会清除流的内容。
// 		//实际上，它并不清空任何内容，它只是重置了流的状态标志而已！
// 		stream.seekg(0);
// 		stream.seekp(0);
// 		stream.clear();
// 		// 去掉下面这行注释，清空stringstream的缓冲，每次循环内存消耗将不再增加!
// 		//stream.str("");      
// 		stream<< 123; //插入字符串
// 		stream<<"abc";
// 
// 		stream.seekg(0);
// 		stream.seekp(0);
// 		stream.clear(); //在进行多次转换前，必须清除stream
// 		stream << "789"; //插入bool值
// 		// 去掉下面两行注释，看看每次循环，你的内存消耗增加了多少！
// 		std::cout<<"Size of stream = "<<stream.str()<<std::endl;
//  		system("PAUSE");
//  	}
// 
//  	return EXIT_SUCCESS;
	
	std::srand(static_cast<unsigned int>(time(0)));

	MsgService msg;

	UdpMonitor* udp = msg.GetUdp();
	udp->Listen(MSG_SOCKET_PORT);

	TcpMonitor* tcp = msg.GetTcp();
	tcp->Listen(MSG_SOCKET_PORT);

	ProtocolService protocol;
	Dispatcher* dispatcher = protocol.GetDispatcher();

	udp->GetSignals()->ConnectReceive(boost::bind(&Dispatcher::as_ReceiveUdpData, 
		dispatcher,	_1, _2, _3));
	tcp->GetSignals()->ConnectReceive(boost::bind(&Dispatcher::as_ReceiveTcpData, 
		dispatcher,	_1, _2, _3));
	tcp->GetSignals()->ConnectConResult(boost::bind(&Dispatcher::as_TcpConResult,
		dispatcher, _1, _2, _3));

	dispatcher->GetSocketSignals()->ConnectBroadcast(boost::bind(&UdpMonitor::as_Broadcast, 
		udp, _1, MSG_SOCKET_PORT));
	dispatcher->GetSocketSignals()->ConnectSendUdp(boost::bind(&UdpMonitor::as_SendTo, 
		udp, _1, _2, _3, _4));
	dispatcher->GetSocketSignals()->ConnectSendTcp(boost::bind(&TcpMonitor::as_SendTo, 
		tcp, _1, _2, _3, _4));
	dispatcher->GetSocketSignals()->ConnectTcpConnect(boost::bind(&TcpMonitor::Connect, 
		tcp, _1, _2));

	Sleep(5000);

// 	unsigned int uHostId = dispatcher->TcpConnect("127.0.0.1", 5123);
//  	Sleep(5000);
// 	std::vector<char>* ptData(new std::stringstream);
// 	(*ptData)<<sz;
// 	dispatcher->SendData(uHostId, ptData);
// 	Sleep(5000);

	//uHostId = dispatcher->UdpConnect("127.0.0.1", 5123);
	//dispatcher->SendData(uHostId, ptData);
	//Sleep(5000);
	system("PAUSE");
// 
// 	service.GetTcp()->Connect("127.0.0.1");
// 	Sleep(5000);
// 	service.GetTcp()->SendTo(1, sz, strlen(sz)+1, "127.0.0.1");
// //	service.GetUdp()->SendTo(10, sz, strlen(sz)+1, "127.0.0.1");
// 	service.Wait();
	return 0;
}


