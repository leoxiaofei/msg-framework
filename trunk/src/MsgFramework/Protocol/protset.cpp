#include "stdafx.h"
#include "protset.h"
#include "agreement.h"
#include "Dis/dispxor.h"
#include "Dis/dispzlib.h"

#include <map>
#include <iterator>
#include <algorithm>


typedef ProtocolBase* (*CreateProtFunc)();

template <class T>
ProtocolBase* CreateProtocol()
{
	return new T;
}


class ProtSet::Impl
{
public:
	std::vector<unsigned short> vecLocalProt;

	std::map<unsigned short, CreateProtFunc>  mapFunc;

};

ProtSet::ProtSet()
: m_pImpl(new Impl)
{
	m_pImpl->mapFunc[Agreement::PD_XOR] = &CreateProtocol<DispXor>;
	m_pImpl->mapFunc[Agreement::PD_ZLIB] = &CreateProtocol<DispZlib>;
}

ProtSet::~ProtSet()
{

}

void ProtSet::GetLocalProtocal(unsigned short nDesVersion, ProtCont& contProt)
{
	contProt.clear();
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

void ProtSet::GetRemoteProtocal(const std::vector<unsigned short>& vecProt, ProtCont& contProt)
{
	contProt.clear();
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

void ProtSet::SetUseProtocol(const std::vector<unsigned short>& vecProt)
{
	m_pImpl->vecLocalProt = vecProt;
}

const std::vector<unsigned short>& ProtSet::GetUseProtocol() const
{
	return m_pImpl->vecLocalProt;
}

unsigned short ProtSet::GetLocalVersion() const
{
	return Agreement::PD_VERSION;
}

