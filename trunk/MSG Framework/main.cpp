#include "StdAfx.h"

#include "MsgFramework.h"

#include <windows.h>


#define SERVICE_NAME TEXT("MSG Framework") 
#define SVC_ERROR ((DWORD)0xC0020001L)

SERVICE_STATUS          gSvcStatus;            //服务状态
SERVICE_STATUS_HANDLE   gSvcStatusHandle;      //服务状态句柄  
HANDLE                  ghSvcStopEvent = NULL; //服务停止句柄  

void ServerReportEvent(LPTSTR szName, LPTSTR szFunction)
{
	HANDLE hEventSource = RegisterEventSource(NULL, szName);  

	if( NULL != hEventSource )  
	{
		LPCTSTR lpszStrings[2];  
		unsigned int len = _tcsnlen(szFunction, 1024) + 1;
		TCHAR *Buffer = new TCHAR[len]; 

		_tcscpy_s(Buffer, len, szFunction);  
		lpszStrings[0] = szName;  
		lpszStrings[1] = Buffer;  

		ReportEvent(hEventSource,        // event log handle  
			EVENTLOG_ERROR_TYPE,         // event type  
			0,                           // event category  
			SVC_ERROR,                   // event identifier  
			NULL,                        // no security identifier  
			2,                           // size of lpszStrings array  
			0,                           // no binary data  
			lpszStrings,                 // array of strings  
			NULL);                       // no binary data      
		DeregisterEventSource(hEventSource);  
	}  
}

VOID ReportSvcStatus( 
	DWORD dwCurrentState,  
	DWORD dwWin32ExitCode,  
	DWORD dwWaitHint)  
{  
	static DWORD dwCheckPoint = 1;  

	// Fill in the SERVICE_STATUS structure.  

	gSvcStatus.dwCurrentState = dwCurrentState;  
	gSvcStatus.dwWin32ExitCode = dwWin32ExitCode;  
	gSvcStatus.dwWaitHint = dwWaitHint;  

	if (dwCurrentState == SERVICE_START_PENDING)  
		gSvcStatus.dwControlsAccepted = 0;  
	else gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;  

	if ( (dwCurrentState == SERVICE_RUNNING) ||  
		(dwCurrentState == SERVICE_STOPPED) )  
		gSvcStatus.dwCheckPoint = 0;  
	else gSvcStatus.dwCheckPoint = dwCheckPoint++;  

	// Report the status of the service to the SCM.  
	SetServiceStatus( gSvcStatusHandle, &gSvcStatus );  
}  

void WINAPI SvcCtrlHandler( DWORD dwCtrl )  
{  
	// Handle the requested control code.   
	switch(dwCtrl)   
	{    
	case SERVICE_CONTROL_STOP:   
		ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);  

		// Signal the service to stop.  

		SetEvent(ghSvcStopEvent);

		return;  

	case SERVICE_CONTROL_INTERROGATE:   
		// Fall through to send current status.  
		break;   

	default:   
		break;  
	}   
	ReportSvcStatus(gSvcStatus.dwCurrentState, NO_ERROR, 0);  
}  

void WINAPI ServiceMain(
	DWORD   dwNumServicesArgs,
	LPWSTR  *lpServiceArgVectors
	)
{
	// Register the handler function for the service  
	gSvcStatusHandle = RegisterServiceCtrlHandler(   
		SERVICE_NAME,   
		SvcCtrlHandler);  

	if( !gSvcStatusHandle )  
	{   
		ServerReportEvent(SERVICE_NAME, TEXT("RegisterServiceCtrlHandler"));   
		return;   
	}   

	// These SERVICE_STATUS members remain as set here  
	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; //只有一个单独的服务  
	gSvcStatus.dwServiceSpecificExitCode = 0;      

	// Report initial status to the SCM  
	ReportSvcStatus( SERVICE_START_PENDING, NO_ERROR, 3000 );  

	// Perform service-specific initialization and work.  
	ghSvcStopEvent = CreateEvent(  
		NULL,    // default security attributes  
		TRUE,    // manual reset event  
		FALSE,   // not signaled  
		NULL);   // no name  

	if ( ghSvcStopEvent == NULL)  
	{  
		ReportSvcStatus( SERVICE_STOPPED, NO_ERROR, 0 );
		return;  
	}  

	// Report running status when initialization is complete.  
	ReportSvcStatus( SERVICE_RUNNING, NO_ERROR, 0 );  

	// TO_DO: Perform work until service stops.   
	//你需要的操作在此添加代码  
	MsgFrameMain(dwNumServicesArgs, lpServiceArgVectors);
	SetEvent(ghSvcStopEvent);

	// Check whether to stop the service.  
	WaitForSingleObject(ghSvcStopEvent, INFINITE);  
	ReportSvcStatus( SERVICE_STOPPED, NO_ERROR, 0 );  

}


int _tmain(int argc, _TCHAR* argv[])
{
	SERVICE_TABLE_ENTRY DispatchTable[] =  
	{  
		{ SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },  
		{ NULL, NULL }
	};  

	// 启动服务的控制分派机线程  
	if (!StartServiceCtrlDispatcher(DispatchTable))  
	{
		ServerReportEvent(SERVICE_NAME, TEXT("StartServiceCtrlDispatcher"));  
		MsgFrameMain(argc, argv);
	}

	return 0;  
}

