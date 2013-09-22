#ifndef UDPSESSION_H__
#define UDPSESSION_H__



class UdpSession
{
	class Impl;
public:
	UdpSession();
	~UdpSession();


private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};


#endif // UDPSESSION_H__
