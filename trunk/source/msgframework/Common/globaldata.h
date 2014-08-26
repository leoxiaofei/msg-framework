#ifndef _GLOBALDATA_H__
#define _GLOBALDATA_H__

#include <string>
#include <boost/shared_ptr.hpp>

class MsgVerBase;

namespace GD
{
	extern std::string strUserName;
	extern std::string strComputer;

	extern unsigned int uLastBagNum;
	extern boost::shared_ptr<MsgVerBase> ptMsgVar;
};


#endif // _GLOBALDATA_H__
