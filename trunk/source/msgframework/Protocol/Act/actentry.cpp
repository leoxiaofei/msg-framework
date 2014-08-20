#include "stdafx.h"
#include "actentry.h"
#include "..\..\Common\msgfmt.h"

#include <iostream>
#include <string>

bool ActEntry::ReceiveMsg(MsgFmt* pMsgFmt)
{
	std::cout << pMsgFmt->uBagNum << std::endl;
	std::cout << pMsgFmt->strUser << std::endl;
	std::cout << pMsgFmt->strComputer << std::endl;
	std::cout << pMsgFmt->uMode << std::endl;
	std::cout << pMsgFmt->uOpt << std::endl;
	std::cout << pMsgFmt->strAddition << std::endl;
	return false;
}
