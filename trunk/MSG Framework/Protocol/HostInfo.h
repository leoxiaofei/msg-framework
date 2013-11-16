#ifndef HOSTINFO_H__
#define HOSTINFO_H__

class UserInfo
{
public:
	UserInfo():uCpuId(0){}
	unsigned int uCpuId;
	std::string  strComputerName;
	std::string  strUserName;
	unsigned int uLastConfigTime;
	unsigned short uVersion;
	std::vector<unsigned short> vecProtDisp;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & uCpuId;
		ar & strComputerName;
		ar & strUserName;
		ar & uLastConfigTime;
		ar & uVersion;
		ar & vecProtDisp;
	}
};

class HostInfo
{
public:
	unsigned int   uHostId;
	unsigned short uPort;
	std::string    strIp;
	UserInfo       userInfo;
};

#endif // HOSTINFO_H__
