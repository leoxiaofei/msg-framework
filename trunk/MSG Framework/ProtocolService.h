#ifndef PROTOCOLSERVICE_H__
#define PROTOCOLSERVICE_H__


class ProtocolService
{
	class Impl;
public:
	ProtocolService(void);
	~ProtocolService(void);

	void Exit();

	void ReceiveUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

protected:
	void As_RecUdpData(const std::string& strAddr, unsigned int uPort, 
		std::tr1::shared_ptr<std::stringstream> ptData);

private:
	boost::scoped_ptr<Impl> m_pImpl;
};

#endif // PROTOCOLSERVICE_H__
