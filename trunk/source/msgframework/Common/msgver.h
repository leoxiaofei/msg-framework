#ifndef _MSGVER_H__
#define _MSGVER_H__

#include <vector>

#include "../Tools/vectordevice.h"



class MsgVerBase
{
public:
	virtual bool Parse(const char* pData, unsigned int uSize) = 0;
	virtual bool Packet(Msg::MsgStream& ms) const = 0;

	virtual int GetType() const = 0;
	enum { UserType = 1000 };
};

///1
class IPMsgVer : public MsgVerBase
{
public:
	unsigned int uVersion;

public:
	enum { Type = UserType + 1 };
	virtual int GetType() const;
	virtual bool Parse(const char* pData, unsigned int uSize);
	virtual bool Packet(Msg::MsgStream& ms) const;

};


///1_lbt6_0#128#000C29F4400C#0#0#0#4001#9

class FeiQVer : public MsgVerBase
{
public:
	unsigned int uVersion;	///����汾
	unsigned int uAvatar;   ///�û�ͷ��
	unsigned int uRank;     ///�û��ȼ���̫��������ʲô�ģ�
	std::string strMacAddr; ///Mac��ַ
	unsigned int uUnknow1;
	unsigned int uUnknow2;
	unsigned int uUnknow3;
	unsigned int uUnknow4;
	unsigned int uUnknow5;

public:
	enum { Type = UserType + 1 };
	virtual int GetType() const ;
	virtual bool Parse(const char* pData, unsigned int uSize);
	virtual bool Packet(Msg::MsgStream& ms) const;

protected:
	bool ParserVersion(const char* pData, unsigned int uSize);
};

#endif // _MSGVER_H__
