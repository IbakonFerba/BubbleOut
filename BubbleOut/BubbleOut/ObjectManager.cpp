#include "stdafx.h"
#include "ObjectManager.h"
#include "ObjectPool.h"

//----------------------------------------------------------------------
//constructor
ObjectManager::ObjectManager()
{
	m_pools = new std::vector<ObjectPool<GameObject>>();
}

//----------------------------------------------------------------------
//destructor
ObjectManager::~ObjectManager()
{
	delete m_pools;
}

//----------------------------------------------------------------------
//object management
template <typename T>
T* ObjectManager::getNewObject()
{
	std::type_info typeInfo = typeid(T);

	for(unsigned i = 0; m_pools->size(); ++i)
	{
		ObjectPool<GameObject>* pool = &m_pools->at(i);
		if(pool->getTypeInfo().hash_code() == typeInfo.hash_code())
		{
			if(!pool->isFull())
			{
				GameObject* go = pool->getNewObject();
				return dynamic_cast<T>(go);
			}
		}
	}
}
