#include "stdafx.h"
#include "DispXor.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <sstream>

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

bool DispXor::SendData(std::tr1::shared_ptr<std::stringstream>& ptStream)
{
	std::stringstream& stream = *ptStream.get();
	stream.clear();
	stream.seekg(0);
	stream.seekp(0);
	char chXor = m_pImpl->chXor;
	char chTemp;
	while (stream >> chTemp)
	{
		stream << (char)(chTemp ^ chXor);
	}
	return true;
}

bool DispXor::ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream)
{
	std::stringstream& stream = *ptStream.get();
	stream.clear();
	stream.seekg(0);
	stream.seekp(0);
	char chXor = m_pImpl->chXor;
	char chTemp;
	while (stream >> chTemp)
	{
		stream << (char)(chTemp ^ chXor);
	}
	return true;
}

bool DispXor::NeedReady()
{
	return true;
}

void DispXor::GetReadyData(std::stringstream& ptStream)
{
	ReadyData();
	binary_oarchive oa(ptStream);
	oa << *m_pImpl.get();
}

void DispXor::SetReadyData(std::stringstream& ptStream)
{
	binary_iarchive ia(ptStream);
	ia >> *m_pImpl.get();
}

void DispXor::ReadyData()
{
	m_pImpl->chXor = std::rand() % 200 + 50;
}
