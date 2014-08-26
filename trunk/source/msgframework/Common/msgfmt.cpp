#include "stdafx.h"
#include "msgfmt.h"
#include "msgver.h"
#include <boost/lexical_cast.hpp>
#include "../Protocol/ipmsg.h"
#include "../Tools/mspool.hpp"

typedef MsPool<struct pool_tag, MsgFmtData > MFP;

bool MsgFmt::Parse(const std::vector<char>& vecData)
{
	bool bRet(false);

	do 
	{
		/// �汾��:�����:����������:������������:������:������Ϣ
		const char* pSta = vecData.data();
		const char* pCur = pSta;
		const char* pEnd = pSta + vecData.size();

		/// �汾��
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}

		if (memcmp(pSta, "1_lbt", strlen("1_lbt")) == 0)
		{
			d->ptMsgVer = boost::shared_ptr<MsgVerBase>(new FeiQVer);
		}
		else
		{
			d->ptMsgVer = boost::shared_ptr<MsgVerBase>(new IPMsgVer);
		}
		d->ptMsgVer->Parse(pSta, pCur - pSta);

		/// �����
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		d->uBagNum = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));

		/// ����������
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		d->strUser = std::string(pSta, pCur - pSta);
		//std::string strIdentification;

		/// ������������
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		d->strComputer = std::string(pSta, pCur - pSta);

		/// ������
		pSta = pCur + 1;
		pCur = std::find(pSta, pEnd, ':');
		if (pCur == pEnd)
		{
			break;
		}
		unsigned int uTemp = boost::lexical_cast<unsigned int>(std::string(pSta, pCur - pSta));
		d->uMode = GET_MODE(uTemp);
		d->uOpt = GET_OPT(uTemp);
		
		/// ������Ϣ
		pSta = pCur + 1;
		d->strAddition = std::string(pSta, pEnd - pSta);

		bRet = true;

	} while (0);

	return bRet;
}

void MsgFmt::Clear()
{
	d->uBagNum = 0;
	d->strUser.resize(0);
	d->strIdentification.resize(0);
	d->strComputer.resize(0);
	d->uMode = 0;
	d->uOpt = 0;
	d->strAddition.resize(0);
}

/// �汾��:�����:����������:������������:������:������Ϣ

bool MsgFmt::Packet(std::vector<char>& vecData) const
{
	Msg::MsgStream ms(vecData);
	d->ptMsgVer->Packet(ms);

	ms << ':';
	ms << d->uBagNum;
	ms << ':';
	ms << d->strUser;
	ms << ':';
	ms << d->strComputer;
	ms << ':';
	ms << (d->uOpt + d->uMode);
	ms << ':';
	ms << d->strAddition;

	return ms.rdstate() == Msg::MsgStream::goodbit;
}

MsgFmt::MsgFmt()
: d(MFP::New())
{
	Clear();
}

MsgFmt::~MsgFmt()
{
	MFP::Free(d);
}

