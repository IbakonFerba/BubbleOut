#pragma once

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "stdafx.h"
#include "ObjectPool.h"
template <typename T>
struct ObjectCollection
{
	std::vector<T*> object_list_starts;
	//use <= in for loops
	std::vector<T*> object_list_ends;
};

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	template <typename T>
	T* getNewObject()
	{
		const std::type_info& typeInfo = typeid(T);

		for (unsigned i = 0; i < m_pools->size(); ++i)
		{
			ObjectPoolBase* poolBase = m_pools->at(i);
			ObjectPool<T>* pool = static_cast<ObjectPool<T>*>(poolBase);
			if (pool->getTypeInfo().hash_code() == typeInfo.hash_code())
			{
				if (!pool->isFull())
				{
					return pool->getNewObject();
				}
			}
		}

		ObjectPool<T>* pool = new ObjectPool<T>();
		m_pools->push_back(pool);

		std::cout << "Created new Pool of type ";
		std::cout << typeInfo.name() << std::endl;

		return pool->getNewObject();
	}

	template <typename T>
	ObjectCollection<T> getObjectsOfType()
	{
		ObjectCollection<T> objectCollection;

		const std::type_info& typeInfo = typeid(T);

		for (unsigned i = 0; i < m_pools->size(); ++i)
		{
			ObjectPoolBase* poolBase = m_pools->at(i);
			ObjectPool<T>* pool = static_cast<ObjectPool<T>*>(poolBase);
			std::cout << pool->getTypeInfo().name() << std::endl;

			if (pool->getTypeInfo().hash_code() == typeInfo.hash_code() || pool->getDummy()->isInheritedFrom(typeInfo.hash_code()))
			{
				objectCollection.object_list_starts.push_back(pool->getObjects());
				objectCollection.object_list_ends.push_back(pool->getLastObject());
			}
		}

		return objectCollection;
	}

	//delete object
private:
	std::vector<ObjectPoolBase*>* m_pools;
};
#endif