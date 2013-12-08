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
	virtual bool SendData(std::vector<char>*& pData);
	virtual bool ReceiveData(std::vector<char>*& pData);
	virtual int  GetType();
	virtual bool NeedReady();
	virtual void GetReadyData(Msg::MsgStream& stream);
	virtual void SetReadyData(Msg::MsgStream& stream);

protected:
	void ReadyData();


private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // DISPXOR_H__
