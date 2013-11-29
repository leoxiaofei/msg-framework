#include "stdafx.h"
#include "ProtManager.h"


class ProtManager::Impl
{
public:
	std::vector<int> vecLocalProt;
};

ProtManager::ProtManager()
: m_pImpl(new Impl)
{

}

ProtManager::~ProtManager()
{

}

void ProtManager::SetLocalProtocol(const std::vector<int>& vecProt)
{
	m_pImpl->vecLocalProt = vecProt;
}

void ProtManager::GetLoacalProtocal(int nDesVersion, ProtCont& contProt)
{

}

