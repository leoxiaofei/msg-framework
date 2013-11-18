#ifndef HOSTINFO_H__
#define HOSTINFO_H__

#include "ProtSet.h"
#include "UserInfo.h"


class HostInfo
{
public:
	unsigned int   uHostId;
	unsigned short uPort;
	std::string    strIp;
	UserInfo       userInfo;
	ProtSet        protSet;
};

#endif // HOSTINFO_H__
