#ifndef _PROTMANAGER_H__
#define _PROTMANAGER_H__

#include <memory>


class ProtManager
{
	class Impl;

public:
	static ProtManager& Instance()
	{
		static ProtManager theSingleton;
		return theSingleton;
	}

private:
	ProtManager();
	~ProtManager();
	ProtManager(const ProtManager&);
	ProtManager& operator=(const ProtManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // _PROTMANAGER_H__
