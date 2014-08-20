#ifndef ACTOR_H__
#define ACTOR_H__

#include <vector>
#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>


class ActBase;

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

	template <class T>
	T* GetAct()
	{
		return static_cast<T*>GetActBase(T->GetType());
	}

protected:
	void Init();

	ActBase* GetActBase(unsigned short uType);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};


#endif // ACTOR_H__
