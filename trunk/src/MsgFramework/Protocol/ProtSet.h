#ifndef _PROTSET_H__
#define _PROTSET_H__

class ProtSet
{
	class Impl;
public:
	ProtSet();
	~ProtSet();



private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // ProtSet_h__
