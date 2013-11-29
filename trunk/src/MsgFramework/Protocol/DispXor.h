#ifndef DISPXOR_H__
#define DISPXOR_H__

#include "ProtocolBase.h"


class DispXor : public ProtocolBase
{
	class Impl;
	template<typename Archive>
	friend void serialize(Archive& ar, DispXor::Impl& impl, const unsigned int version);
public:
	DispXor();
	~DispXor();
	virtual bool SendData(std::tr1::shared_ptr<std::stringstream>& ptStream);
	virtual bool ReceiveData(std::tr1::shared_ptr<std::stringstream>& ptStream);
	virtual bool NeedReady();
	virtual void GetReadyData(std::stringstream& ptStream);
	virtual void SetReadyData(std::stringstream& ptStream);

protected:
	void ReadyData();

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // DISPXOR_H__
