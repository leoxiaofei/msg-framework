#ifndef HOSTMANAGER_H__
#define HOSTMANAGER_H__

#include <memory>

class HostInfo;

class HostManager
{
	class Impl;
public:
	static HostManager& Instance()
	{
		static HostManager theSingleton;
		return theSingleton;
	}

	unsigned int NewHost(const std::string& strIp, unsigned short uPort);
	HostInfo* FindHost(const std::string& strIp, unsigned short uPort);
	HostInfo* FindHost(unsigned int uHostId);

	void DeleteHost(unsigned int uHostId);
	void DeleteHost(const std::string& strIp, unsigned short uPort);

protected:
	void AddHost(HostInfo* pHostInfo);
	void RemoveHost(const HostInfo* pHostInfo);

private:
	HostManager();
	~HostManager();
	HostManager(const HostManager&);
	HostManager& operator=(const HostManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // HOSTMANAGER_H__
