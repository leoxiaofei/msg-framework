#include "stdafx.h"
#include "dispxor.h"
#include "../agreement.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using boost::archive::binary_oarchive; // saving
using boost::archive::binary_iarchive; // loading

class DispXor::Impl
{
public:
	char chXor;
};

template<typename Archive>
void serialize(Archive& ar, DispXor::Impl& impl, const unsigned int version)
{
	ar & impl.chXor;
}


DispXor::DispXor()
: m_pImpl(new Impl)
{

}

DispXor::~DispXor()
{

}

class XorOp
{
public:
	XorOp(char chXor) : m_chXor(chXor) {}

	char operator()(char ch)
	{
		return (char)(ch ^ m_chXor);
	}

private:
	char m_chXor;
};

bool DispXor::SendData(std::vector<char>*& pData)
{
	for_each(pData->begin(), pData->end(), XorOp(m_pImpl->chXor));
	return true;
}

bool DispXor::ReceiveData(std::vector<char>*& pData)
{
	for_each(pData->begin(), pData->end(), XorOp(m_pImpl->chXor));
	return true;
}

bool DispXor::NeedReady()
{
	return true;
}

void DispXor::GetReadyData(Msg::MsgStream& stream)
{
	ReadyData();
	binary_oarchive oa(stream);
	oa << *m_pImpl;
}

void DispXor::SetReadyData(Msg::MsgStream& stream)
{
	binary_iarchive ia(stream);
	ia >> *m_pImpl;
}

void DispXor::ReadyData()
{
	m_pImpl->chXor = std::rand() % 200 + 50;
}

int DispXor::GetType()
{
	return Agreement::PD_XOR;
}


