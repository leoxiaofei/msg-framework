#include "stdafx.h"
#include "msgfmt.h"
#include "msgver.h"
#include <boost/lexical_cast.hpp>
#include "../Protocol/ipmsg.h"

bool MsgFmt::Parse(const std::vector<char>& vecData)
{
	bool bRet(false);

	do 
	{
		/// 版本号:包编号:发送者姓名:发送者主机名:命令字:附加信息
		const char* pSta = vecData.data();
		const char* pCur = pSta;
		const char* pEnd = pSta + vecData.size();

		/// 版本号
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}

		if (memcmp(pSta, "1_lbt", strlen("1_lbt")) == 0)
		{
			ptMsgVer = boost::shared_ptr<MsgVerBase>(new FeiQVer);
		}
		else
		{
			ptMsgVer = boost::shared_ptr<MsgVerBase>(new IPMsgVer);
		}
		ptMsgVer->Parse(pSta, pCur - pSta);

		/// 包编号
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		uBagNum = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		/// 发送者姓名
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		strUser = std::string(pSta, pCur - pSta);
		//std::string strIdentification;

		/// 发送者主机名
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		strComputer = std::string(pSta, pCur - pSta);

		/// 命令字
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		unsigned int uTemp = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));
		uMode = GET_MODE(uTemp);
		uOpt = GET_OPT(uTemp);
		
		/// 附加信息
		pSta = pCur + 1;
		strAddition = std::string(pSta, pEnd - pSta);

		bRet = true;

	} while (0);

	return bRet;
}

void MsgFmt::Clear()
{
	uBagNum = 0;
	strUser.resize(0);
	strIdentification.resize(0);
	strComputer.resize(0);
	uMode = 0;
	uOpt = 0;
	strAddition.resize(0);
}
