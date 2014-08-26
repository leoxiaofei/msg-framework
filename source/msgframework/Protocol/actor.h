#ifndef _ACTOR_H__
#define _ACTOR_H__

#include <boost/asio/io_service.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>


class Dispatcher;

class Actor
{
	class Impl;
public:
	Actor(boost::asio::io_service& iosWork);
	~Actor();

	void SetDispatcher(Dispatcher* pDispatcher);

protected:

	void Online(unsigned int uNetId) const;
	void Offline(unsigned int uNetId) const;
	void AnsOnline(unsigned int uNetId) const;

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _ACTOR_H__
