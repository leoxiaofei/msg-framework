#ifndef _MSGTRACERECORD_H__
#define _MSGTRACERECORD_H__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <string>

struct TraceRecord
{
	unsigned int uPID;
	std::wstring strTitle;
	std::wstring strText;

	//use this function to serialize and deserialize object
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & uPID & strTitle & strText;
	}

};


#endif // _MSGTRACERECORD_H__