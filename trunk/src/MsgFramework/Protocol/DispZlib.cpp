#include "stdafx.h"
#include "DispZlib.h"
#include "Agreement.h"

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <sstream>

using namespace boost::iostreams;

bool DispZlib::SendData(std::tr1::shared_ptr<std::stringstream>& ptStream)
{
// 	ptStream->clear();
// 	ptStream->seekg(0);
// 	ptStream->seekp(0);

	std::tr1::shared_ptr<std::stringstream> ptNew(new std::stringstream());
	filtering_ostream out;
	out.push(zlib_compressor());
	out.push(*ptNew);

	boost::iostreams::copy(*ptStream, out);
	ptStream = ptNew;

	return true;
}

bool DispZlib::ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream)
{
// 	ptStream->clear();
// 	ptStream->seekg(0);
// 	ptStream->seekp(0);

	std::tr1::shared_ptr<std::stringstream> ptNew(new std::stringstream());
	filtering_istream in;
	in.push(zlib_decompressor());
	in.push(*ptStream);
	boost::iostreams::copy(in, *ptNew);
	ptStream = ptNew;

	return true;
}

int DispZlib::GetType()
{
	return Agreement::PD_ZLIB;
}

