#ifndef _MSGFMT_H__
#define _MSGFMT_H__

#include <vector>
#include <boost/shared_ptr.hpp>

class MsgVerBase;

/// 版本号:包编号:发送者姓名:发送者主机名:命令字:附加信息
class MsgFmt
{
public:
	bool Parse(const std::vector<char>& vecData);
	void Clear();

	boost::shared_ptr<MsgVerBase> ptMsgVer;
	unsigned int uBagNum;
	std::string strUser;
	std::string strIdentification;
	std::string strComputer;
	unsigned short uMode;
	unsigned int uOpt;
	std::string strAddition;

};



#endif // _MSGFMT_H__
