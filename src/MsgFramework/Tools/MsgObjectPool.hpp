#ifndef MSGOBJECTPOOL_H__
#define MSGOBJECTPOOL_H__

#include <stack>
#include <boost/thread.hpp>

template<typename T>
class MsgObjectPool
{
public:
	virtual ~MsgObjectPool()
	{
		Release();
	}

	T* New()
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		T* pRet(NULL);
		if (!m_staData.empty())
		{
			pRet = m_staData.top();
			m_staData.pop();
		}
		return pRet;
	}

	void Recycle(T* data)
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		m_staData.push(data);
	}
	
	void Release()
	{
		boost::mutex::scoped_lock lock(m_mxSingle);
		while(!m_staData.empty())
		{
			delete m_staData.top();
			m_staData.pop();
		}
	}

private:
	std::stack<T*> m_staData;
	boost::mutex   m_mxSingle;
};


#endif // MSGOBJECTPOOL_H__
