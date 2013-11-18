#include "stdafx.h"
#include "ProtSet.h"
#include "ProtocolBase.h"

#include <vector>


typedef std::vector<std::tr1::shared_ptr<ProtocolBase> > ProtCont;

class ProtSet::Impl
{
public:
	ProtCont contSender;
	ProtCont contReceiver;


};


ProtSet::ProtSet()
: m_pImpl(new Impl)
{

}

ProtSet::~ProtSet()
{

}

