#ifndef MSGOBJECTPOOL_H__
#define MSGOBJECTPOOL_H__

#include <stack>

template<typename T>
class MsgObjectPool
{
public:
	~MsgObjectPool()
	{
		Release();
	}

	T* New()
	{
		T* pRet(NULL);
		if (!m_staData.empty())
		{
			pRet = m_staData.top();
		}
		return pRet;
	}

	void Recycle(T* data)
	{
		m_staData.push(data);
	}
	
	void Release()
	{
		while(!m_staData.empty())
		{
			delete m_staData.top();
			m_staData.pop();
		}
	}

private:
	std::stack<T*> m_staData;
};


#endif // MSGOBJECTPOOL_H__
