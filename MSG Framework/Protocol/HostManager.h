#ifndef HOSTMANAGER_H__
#define HOSTMANAGER_H__

#include <memory>
#include <unordered_map>
#include <string>

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

	HostInfo* FindHost(unsigned int uHostId);
	void DeleteHost(unsigned int uHostId);

	enum TransType{TT_UDP, TT_TCP, TT_TOTAL};
	HostInfo* FindHost(const std::string& strIp, unsigned short uPort, TransType eType);
	unsigned int NewHost(const std::string& strIp, unsigned short uPort, TransType eType);
	void DeleteHost(const std::string& strIp, unsigned short uPort, TransType eType);

	static TransType GetHostType(const HostInfo* pHostInfo);

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
