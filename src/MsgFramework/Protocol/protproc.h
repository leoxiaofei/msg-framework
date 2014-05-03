#ifndef _PROTPROC_H__
#define _PROTPROC_H__


#include <vector>

class ProtProc
{
	class Impl;
public:
	ProtProc();
	~ProtProc();

	void Prepare(unsigned short uVersion, const std::vector<unsigned short>& vecProtDisp);
	void GetReadyData(std::vector<char>& data);  ///ªÿ”¶«Î«Û
	void SetReadyData(std::vector<char>& data);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};



#endif // _PROTPROC_H__
