#ifndef VCPOOL_H__
#define VCPOOL_H__

#include "../Tools/MsgObjectPool.hpp"

class VcPool : public MsgObjectPool<std::vector<char> >
{
public:
	static VcPool& Instance()
	{
		static VcPool theSingleton;
		return theSingleton;
	}

	std::vector<char>* New();

private:
	VcPool();
	~VcPool();
	VcPool(const VcPool&);
	VcPool& operator=(const VcPool&);

};

#endif // VCPOOL_H__
