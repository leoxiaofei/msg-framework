#include "stdafx.h"
#include "ProtManager.h"
#include "Agreement.h"
#include "DispXor.h"
#include "DispZlib.h"

#include <map>
#include <iterator>
#include <algorithm>

typedef ProtocolBase* (*CreateProtFunc)();

template <class T>
ProtocolBase* CreateProtocol()
{
	return new T;
}


class ProtManager::Impl
{
public:
	std::vector<unsigned short> vecLocalProt;

	std::map<unsigned short, CreateProtFunc>  mapFunc;

};

ProtManager::ProtManager()
: m_pImpl(new Impl)
{
	m_pImpl->mapFunc[Agreement::PD_XOR] = &CreateProtocol<DispXor>;
	m_pImpl->mapFunc[Agreement::PD_ZLIB] = &CreateProtocol<DispZlib>;
}

ProtManager::~ProtManager()
{

}

void ProtManager::SetLocalProtocol(const std::vector<unsigned short>& vecProt)
{
	m_pImpl->vecLocalProt = vecProt;
}

void ProtManager::GetLoacalProtocal(unsigned short nDesVersion, ProtCont& contProt)
{
	for (std::vector<unsigned short>::const_iterator citor = m_pImpl->vecLocalProt.begin();
		citor != m_pImpl->vecLocalProt.end(); ++citor)
	{
		if (*citor < nDesVersion)
		{
			std::map<unsigned short, CreateProtFunc>::const_iterator ciFind =
				m_pImpl->mapFunc.find(*citor);
			if (ciFind != m_pImpl->mapFunc.end())
			{
				contProt.push_back(std::tr1::shared_ptr<ProtocolBase>(
					ciFind->second()));
			}
		}
	}
}

void ProtManager::GetRemoteProtocal(const std::vector<unsigned short>& vecProt, ProtCont& contProt)
{
	for (std::vector<unsigned short>::const_iterator citor = vecProt.begin();
		citor != vecProt.end(); ++citor)
	{
		if (*citor < Agreement::PD_VERSION)
		{
			std::map<unsigned short, CreateProtFunc>::const_iterator ciFind =
				m_pImpl->mapFunc.find(*citor);
			if (ciFind != m_pImpl->mapFunc.end())
			{
				contProt.push_back(std::tr1::shared_ptr<ProtocolBase>(
					ciFind->second()));
			}
		}
	}
}

void ProtManager::GetSendProtocol(std::vector<unsigned short>& vecProt) const
{
	vecProt.clear();
	vecProt.resize(m_pImpl->vecLocalProt.size());
	std::reverse_copy(m_pImpl->vecLocalProt.begin(), 
		m_pImpl->vecLocalProt.end(), vecProt.begin());
}

