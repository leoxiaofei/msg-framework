#ifndef PROTMANAGER_H__
#define PROTMANAGER_H__

#include <memory>
#include <vector>

class ProtocolBase;

typedef std::vector<std::tr1::shared_ptr<ProtocolBase> > ProtCont;

class ProtManager
{
	class Impl;
public:
	static ProtManager& Instance()
	{
		static ProtManager theSingleton;
		return theSingleton;
	}

	void SetLocalProtocol(const std::vector<int>& vecProt);

	std::tr1::shared_ptr<ProtocolBase> GetProtocol(int nType);
	void GetLoacalProtocal(int nDesVersion, ProtCont& contProt);

private:
	ProtManager();
	~ProtManager();
	ProtManager(const ProtManager&);
	ProtManager& operator=(const ProtManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // PROTMANAGER_H__
