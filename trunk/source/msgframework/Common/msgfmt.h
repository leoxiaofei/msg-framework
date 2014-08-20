#ifndef _MSGFMT_H__
#define _MSGFMT_H__

#include <vector>
#include <boost/shared_ptr.hpp>

class MsgVerBase;

/// �汾��:�����:����������:������������:������:������Ϣ
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
