#ifndef USERINFO_H__
#define USERINFO_H__

#include <string>
#include <vector>

class UserInfo
{
public:
	UserInfo() :uCpuId(0){}
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

#endif // USERINFO_H__
