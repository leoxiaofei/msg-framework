#ifndef _GENERALSERIALIZE_H__
#define _GENERALSERIALIZE_H__

#include <boost/serialization/vector.hpp>



template<class Archive>
void serialize(Archive &ar, std::vector<unsigned short>& data, const unsigned int version)
{
	ar & data;
}



#endif // _GENERALSERIALIZE_H__
