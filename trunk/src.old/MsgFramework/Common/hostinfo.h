#ifndef HOSTINFO_H__
#define HOSTINFO_H__

#include <string>

class HostInfo
{
public:
	unsigned int   uHostId;
	unsigned short uPort;
	std::string    strIp;
};

#endif // HOSTINFO_H__
