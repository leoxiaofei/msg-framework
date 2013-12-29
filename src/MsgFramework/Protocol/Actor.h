#ifndef ACTOR_H__
#define ACTOR_H__

#include <vector>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>

namespace boost
{
	class mutex;
}

class Actor
{
	class Impl;
public:
	Actor(boost::asio::io_service& iosWork);
	~Actor();
	
	typedef boost::function<void(unsigned int, unsigned int,
		unsigned short,std::vector<char>*) > FuncSend;
	typedef boost::function<void(unsigned short, std::vector<char>* )> FuncBroadcast;

	void SetSender(const FuncSend& sendFunc);
	void SetBroadcastor(const FuncBroadcast& broadcastFunc);

	void ReceiveData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData);

	unsigned int SendData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData);
	unsigned int as_SendData(unsigned int uHostId, unsigned short eActType, std::vector<char>* ptData);


protected:
	void Init();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};


#endif // ACTOR_H__
