#ifndef _DISPATCHER_H__
#define _DISPATCHER_H__

#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>

class TrafficData;
class ActBase;

typedef boost::function<void(const TrafficData& tfcData)> FuncBroadcast;
typedef boost::function<void(const TrafficData& tfcData, unsigned int uNetId)> FuncSend;

class Dispatcher
{
	class Impl;
public:
	Dispatcher(boost::asio::io_service& ios);
	~Dispatcher();

	void SetUdpSendFunc(const FuncBroadcast& funcBroadcast, const FuncSend& funcSend);

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


protected:
	void InitAct();
	void RegActBase(unsigned short uType, ActBase* pBase);
	ActBase* GetActBase(unsigned short uType);

protected:
	void ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId);
	void SendUdpData(const TrafficData& tfcData, unsigned int uNetId);

	boost::asio::io_service& GetIOs();

public: ///Socketµ÷ÓÃ
	void as_ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId);

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _DISPATCHER_H__
