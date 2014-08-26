#include "stdafx.h"
#include "msgver.h"

#include <boost/lexical_cast.hpp>
#include <sstream>
#include "../Tools/vectordevice.h"

int IPMsgVer::GetType() const
{
	return Type;
}

bool IPMsgVer::Parse(const char* pData, unsigned int uSize)
{
	uVersion = boost::lexical_cast<unsigned int>(std::string(pData, uSize));
	return true;
}

bool IPMsgVer::Packet(Msg::MsgStream& ms) const
{
	ms << uVersion;
	return ms.rdstate() == Msg::MsgStream::goodbit;
}

int FeiQVer::GetType() const
{
	return Type;
}

bool FeiQVer::Parse(const char* pData, unsigned int uSize)
{
	bool bRet(false);

	do 
	{
		const char* pSta = pData;
		const char* pCur = pData;
		const char* pEnd = pData + uSize;

		pCur = std::find(pSta, pEnd, '#');

		///版本
		if (pCur == pEnd)
		{
			break;
		}

		ParserVersion(pSta, pCur - pSta);

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///用户等级
		if (pCur == pEnd)
		{
			break;
		}
		uRank = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///Mac地址
		if (pCur == pEnd)
		{
			break;
		}
		strMacAddr = std::string(pSta, pCur - pSta);

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///uUnknow1
		if (pCur == pEnd)
		{
			break;
		}
		uUnknow1 = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///uUnknow2
		if (pCur == pEnd)
		{
			break;
		}
		uUnknow2 = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///uUnknow3
		if (pCur == pEnd)
		{
			break;
		}
		uUnknow3 = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '#');
		///uUnknow4
		if (pCur == pEnd)
		{
			break;
		}
		uUnknow4 = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		///uUnknow5
		uUnknow5 = boost::lexical_cast<unsigned int>(std::string(pSta, pEnd - pSta));

		bRet = true;

	} while (0);

	return bRet;
}

bool FeiQVer::ParserVersion(const char* pData, unsigned int uSize)
{
	bool bRet(false);
	do 
	{
		const char* pSta = pData;
		const char* pCur = pData;
		const char* pEnd = pData + uSize;

		pCur = std::find(pSta, pEnd, '_');

		if (pCur == pEnd)
		{
			break;
		}

		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, '_');
		if (pCur == pEnd)
		{
			break;
		}

		pSta = pSta + strlen("lbt");
		uVersion = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		pSta = pCur + 1;
		uAvatar = boost::lexical_cast<unsigned int>(std::string(pSta, pEnd - pSta));

		bRet = true;

	} while (0);

	return bRet;
}

///1_lbt6_0#128#000C29F4400C#0#0#0#4001#9

bool FeiQVer::Packet(Msg::MsgStream& ms) const
{
	ms << "1_lbt6_";
	ms << uAvatar;
	ms << '#';
	ms << uRank;
	ms << '#';
	std::string ss = strMacAddr;
	std::reverse(ss.begin(), ss.end());
	ms << ss;
	ms << '#';
	ms << uUnknow1;
	ms << '#';
	ms << uUnknow2;
	ms << '#';
	ms << uUnknow3;
	ms << '#';
	ms << uUnknow4;
	ms << '#';
	ms << uUnknow5;

	return ms.rdstate() == Msg::MsgStream::goodbit;
}

