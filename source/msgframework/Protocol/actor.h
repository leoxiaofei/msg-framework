#ifndef _ACTOR_H__
#define _ACTOR_H__

#include <boost/asio/io_service.hpp>
#include <boost/scoped_ptr.hpp>

class ActBase;

class Actor
{
	class Impl;
public:
	Actor(boost::asio::io_service& iosWork);
	~Actor();

	template <class T>
	T* RegAct()
	{
		T* p = new T;
		RegActBase(p->GetType(), p);
		return p;
	}

	template <class T>
	T* GetAct()
	{
		return static_cast<T*>(GetActBase(T::Type));
	}

	ActBase* GetActBase(unsigned short uType);

protected:
	void Init();

	void RegActBase(unsigned short uType, ActBase* pBase);

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _ACTOR_H__
