#ifndef VectorDevice_h__
#define VectorDevice_h__

#include "container_device.hpp"
#include <vector>
#include <string>
#include <boost/iostreams/stream.hpp>

namespace Msg
{
	typedef container_device< std::vector<char> > VectorDevice;
	typedef container_device< std::string >       StringDevice;

	typedef boost::iostreams::stream<VectorDevice> MsgStream;
}


#endif // VectorDevice_h__
