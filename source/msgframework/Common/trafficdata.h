#ifndef _TRAFFICDATA_H__
#define _TRAFFICDATA_H__

#include <boost/shared_ptr.hpp>
#include <vector>

class TrafficData
{
	class Impl;
public:
	TrafficData();
	~TrafficData();

	std::vector<char>* GetData() const;

protected:

private:
	boost::shared_ptr <Impl> m_pImpl;
};


#endif // _TRAFFICDATA_H__
