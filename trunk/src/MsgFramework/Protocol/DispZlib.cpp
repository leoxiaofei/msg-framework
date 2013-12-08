#include "stdafx.h"
#include "DispZlib.h"
#include "Agreement.h"
#include "../Common/vcpool.h"

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <sstream>

using namespace boost::iostreams;


bool DispZlib::SendData(std::vector<char>*& pData)
{
	std::vector<char>* ptNew = VcPool::Instance().New();
	Msg::MsgStream stmNew(*ptNew);

	filtering_ostream out;
	out.push(zlib_compressor());
	out.push(stmNew);

	boost::iostreams::copy(Msg::MsgStream(*pData), out);
	VcPool::Instance().Recycle(pData);
	pData = ptNew;

	return true;
}


bool DispZlib::ReceiveData(std::vector<char>*& pData)
{
	std::vector<char>* ptNew = VcPool::Instance().New();
	Msg::MsgStream stmNew(*ptNew);

	filtering_istream in;
	in.push(zlib_decompressor());
	in.push(Msg::MsgStream(*pData));
	boost::iostreams::copy(in, stmNew);
	VcPool::Instance().Recycle(pData);
	pData = ptNew;

	return true;
}

int DispZlib::GetType()
{
	return Agreement::PD_ZLIB;
}

