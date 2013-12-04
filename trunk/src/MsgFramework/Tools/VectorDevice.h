#ifndef VectorDevice_h__
#define VectorDevice_h__

#include "container_device.hpp"
#include <vector>
#include <string>

namespace Msg
{
	typedef container_device< std::vector<char> > VectorDevice;
	typedef container_device< std::string >       StringDevice;
}


#endif // VectorDevice_h__
