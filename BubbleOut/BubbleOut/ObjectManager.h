#pragma once

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "stdafx.h"
#include "ObjectPool.h"

/*
 * Collection of all objects of the given type
 * (includes derived objects)
 */
template <typename T>
struct ObjectCollection
{
	std::vector<T*> object_list_starts;
	//use <= in for loops
	std::vector<T*> object_list_ends;
};

/*
 * Central object manager of the Engine.
 * All object creation and deletion should happen through
 * this class
 */
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	//returns a new object of the given type
	template <typename T>
	T* getNewObject()
	{
		//get typeid of type
		const std::type_info& typeInfo = typeid(T);

		//iterate through pools to find a pool of the given size that is not full yet
		for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
		{
			ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
			ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);
			if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code())
			{
				if (!ptrPool->isFull())
				{
					//found an existing pool with free space, return new object
					return ptrPool->getNewObject();
				}
			}
		}

		//found no exiting pool with free space, create a new pool and return new object
		ObjectPool<T>* ptrPool = new ObjectPool<T>();
		m_ptr_pools->push_back(ptrPool);

		std::cout << "Created new Pool of type ";
		std::cout << typeInfo.name() << std::endl;

		return ptrPool->getNewObject();
	}

	//get all objects of the given type and derived from the given type
	template <typename T>
	ObjectCollection<T> getObjectsOfType()
	{
		//create the return object
		ObjectCollection<T> objectCollection;

		//get typeinfo of given type
		const std::type_info& typeInfo = typeid(T);

		//iterate through pools to find pools of desired type
		for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
		{
			ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
			ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);

			if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code() /*|| ptrPool->getDummy()->isDerivedFrom(typeInfo.hash_code())*/)
			{
				objectCollection.object_list_starts.push_back(ptrPool->getObjects());
				objectCollection.object_list_ends.push_back(ptrPool->getLastObject());
			}
		}

		//return objects
		return objectCollection;
	}

	//deletion

	////mark the given object for deletion after this frame
	//template <typename T>
	//void destroyObject(T* obj)
	//{
	//	//get typeinfo
	//	const std::type_info& typeInfo = typeid(T);

	//	//iterate trhough pools to fins object
	//	for (unsigned i = 0; i < m_ptr_pools->size(); ++i)
	//	{
	//		ObjectPoolBase* ptrPoolBase = m_ptr_pools->at(i);
	//		ObjectPool<T>* ptrPool = static_cast<ObjectPool<T>*>(ptrPoolBase);

	//		if (ptrPool->getTypeInfo().hash_code() == typeInfo.hash_code() || ptrPool->getDummy()->isDerivedFrom(typeInfo.hash_code()))
	//		{
	//			if(ptrPool->containsObject(obj))
	//			{
	//				ptrPool->markForDelete(obj);
	//				return;
	//			}
	//		}
	//	}
	//}

	//void deleteObjects();
private:
	std::vector<ObjectPoolBase*>* m_ptr_pools;
};
#endif