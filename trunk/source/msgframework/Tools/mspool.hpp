#ifndef _MSPOOL_H__
#define _MSPOOL_H__

#include <stack>
#include <boost/thread.hpp>


template <class Tag, class Type>
class MsPool
{
public:
	static Type* Malloc()
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		Type* pRet(NULL);
		if (!m_staData.empty())
		{
			pRet = m_staData.top();
			m_staData.pop();
		}
		return pRet;
	}

	static void Free(Type*& data)
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		if (data)
		{
			m_staData.push(data);
			data = NULL;
		}
	}

	static Type* New()
	{
		Type* pRet = Malloc();
		if (!pRet)
		{
			pRet = new Type();
		}
		return pRet;
	}

	static void Release()
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		while (!m_staData.empty())
		{
			delete m_staData.top();
			m_staData.pop();
		}
	}

private:
	static std::stack<Type*>	m_staData;
	static boost::mutex			m_mxSingle;
};

template <class Tag, class Type>
std::stack<Type*> MsPool<Tag, Type>::m_staData;

template <class Tag, class Type>
boost::mutex MsPool<Tag, Type>::m_mxSingle;

#endif // _MSPOOL_H__
