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

		for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
		{
			ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
			ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);
			if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code())
			{
				if (!ptrPool->isFull())
				{
					return ptrPool->getNewObject();
				}
			}
		}

		ObjectPool<T>* ptrPool = new ObjectPool<T>();
		m_ptr_pools->push_back(ptrPool);

		std::cout << "Created new Pool of type ";
		std::cout << typeInfo.name() << std::endl;

		return ptrPool->getNewObject();
	}

	template <typename T>
	ObjectCollection<T> getObjectsOfType()
	{
		ObjectCollection<T> objectCollection;

		const std::type_info& typeInfo = typeid(T);

		for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
		{
			ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
			ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);

			if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code() || ptrPool->getDummy()->isInheritedFrom(typeInfo.hash_code()))
			{
				objectCollection.object_list_starts.push_back(ptrPool->getObjects());
				objectCollection.object_list_ends.push_back(ptrPool->getLastObject());
			}
		}

		return objectCollection;
	}

	//deletion
	template <typename T>
	void destroyObject(T* obj)
	{
		const std::type_info& typeInfo = typeid(T);

		for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
		{
			ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
			ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);

			if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code() || ptrPool->getDummy()->isInheritedFrom(typeInfo.hash_code()))
			{
				if(ptrPool->containsObject(obj))
				{
					ptrPool->markForDelete(obj);
				}
			}
		}
	}

	void deleteObjects();
private:
	std::vector<ObjectPoolBase*>* m_ptr_pools;
};
#endif