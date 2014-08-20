#ifndef _MSGTRACE_H__
#define _MSGTRACE_H__

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include <string>

#include <iostream>
#include <vector>
#include <boost/scoped_ptr.hpp>

namespace bip = boost::interprocess;


class MsgTrace
{
	class Impl;
public:
	MsgTrace();
	~MsgTrace();

	void InitData(unsigned int uPID, const std::wstring& strTitle);
	void Input(const std::wstring& strText);
	void Input(const wchar_t& chChar);
	void Emit();

private:
	boost::scoped_ptr<Impl> m_pImpl;
};


#endif // _MSGTRACE_H__
