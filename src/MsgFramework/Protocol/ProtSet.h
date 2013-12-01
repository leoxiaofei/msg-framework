#ifndef _PROTSET_H__
#define _PROTSET_H__

#include <vector>

class ProtSet
{
	class Impl;
public:
	ProtSet();
	~ProtSet();

	void Prepare(unsigned short uVersion, const std::vector<unsigned short>& vecProtDisp);
	bool NeedReady();
	void GetReadyData();  ///ªÿ”¶«Î«Û
	void SetReadyData();  

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // ProtSet_h__
