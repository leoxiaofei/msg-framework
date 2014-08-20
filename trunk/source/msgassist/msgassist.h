#include "msgassistglobal.h"

// This class is exported from the msgassist.dll
class MSGASSIST_API MsgAssist 
{
public:
	MsgAssist();
	~MsgAssist();
	// TODO: add your methods here.
	
	bool SetHook();
	bool UnHook();
	

};

