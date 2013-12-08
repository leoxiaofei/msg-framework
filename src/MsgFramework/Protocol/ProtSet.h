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
	void GetReadyData(std::vector<char>& data);  ///ªÿ”¶«Î«Û
	void SetReadyData(std::vector<char>& data);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // ProtSet_h__
