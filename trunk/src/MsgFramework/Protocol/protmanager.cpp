#include "stdafx.h"
#include "ProtManager.h"
#include "..\Tools\msgobjectpool.hpp"
#include "protproc.h"



class ProtManager::Impl
{
public:
	MsgObjectPool<ProtProc> mopProtSet;

};


ProtManager::ProtManager()
: m_pImpl(new Impl)
{

}

ProtManager::~ProtManager()
{

}

