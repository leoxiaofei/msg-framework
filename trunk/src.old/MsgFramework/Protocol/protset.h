#ifndef PROTMANAGER_H__
#define PROTMANAGER_H__

#include <memory>
#include <vector>

class ProtocolBase;

typedef std::vector<std::tr1::shared_ptr<ProtocolBase> > ProtCont;

class ProtSet
{
	class Impl;
public:
	static ProtSet& Instance()
	{
		static ProtSet theSingleton;
		return theSingleton;
	}

	void SetUseProtocol(const std::vector<unsigned short>& vecProt);
	const std::vector<unsigned short>& GetUseProtocol() const;
	unsigned short GetLocalVersion() const;

	void GetLocalProtocal(unsigned short nDesVersion, ProtCont& contProt);
	void GetRemoteProtocal(const std::vector<unsigned short>& vecProt, ProtCont& contProt);

private:
	ProtSet();
	~ProtSet();
	ProtSet(const ProtSet&);
	ProtSet& operator=(const ProtSet&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // PROTMANAGER_H__
