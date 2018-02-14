#pragma once

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "stdafx.h"

/*
 * Base classs for pooling objects in the
 * Object manager
 */
class ObjectPoolBase
{
public:
	ObjectPoolBase() {}
	virtual ~ObjectPoolBase() {}

	virtual void deleteMarkedObjects() {};
};

/*
 * actual object pool class to store
 * objects of give type linearly in memory
 */
template <typename T>
class ObjectPool : public ObjectPoolBase
{
public:
	ObjectPool();
	~ObjectPool();

	/*void markForDelete(T* ptrObj);
	void deleteMarkedObjects() override;
	void deleteObject(T* ptrObj);*/

	T* getObjects() const;
	T* getLastObject() const;
	T* getNewObject();

	T* getDummy();
	const std::type_info& getTypeInfo() const;

	bool isFull() const;
	T* containsObject(T* ptrObj) const;
private:
	static const int SIZE = 128;

	T* m_ptr_objects_start;
	T* m_ptr_objects_end;
	T* m_ptr_last_spot;
	const std::type_info& m_r_typeid;
	T m_dummy;

	std::vector<T*> m_markedForDelete;
};

//----------------------------------------------------------------------
//implementation iside header file because linker throws an error otherwise (or I have to include the cpp file everywhere)


//----------------------------------------------------------------------
//constructor
template <typename T>
ObjectPool<T>::ObjectPool() : m_r_typeid(typeid(T)), m_dummy()
{
	m_ptr_objects_start = new T[SIZE];
	m_ptr_objects_end = m_ptr_objects_start;

	m_ptr_last_spot = m_ptr_objects_start + SIZE;
}

//----------------------------------------------------------------------
//destructor
template <typename T>
ObjectPool<T>::~ObjectPool()
{
	delete[] m_ptr_objects_start;
	delete m_ptr_objects_end;
	delete m_ptr_last_spot;
}

//----------------------------------------------------------------------
//object management

////mark given object for deletion
//template <typename T>
//void ObjectPool<T>::markForDelete(T* ptrObj)
//{
//	m_markedForDelete.push_back(ptrObj);
//}
//
////delete all marked objects
//template <typename T>
//void ObjectPool<T>::deleteMarkedObjects()
//{
//	for(unsigned i = 0; i < m_markedForDelete.size(); ++i)
//	{
//		deleteObject(m_markedForDelete.at(i));
//	}
//
//	m_markedForDelete.clear();
//}
//
////delete given object
//template <typename T>
//void ObjectPool<T>::deleteObject(T* ptrObj)
//{
//	*ptrObj = *(m_ptr_objects_end - 1);
//	--m_ptr_objects_end;
//}


//----------------------------------------------------------------------
//checks

//is the pool full?
template <typename T>
bool ObjectPool<T>::isFull() const
{
	return m_ptr_objects_end == m_ptr_last_spot;
}

/*does the pool contain the given object?
 * (returns the object pointer if true or nullptr if false)
 */
template <typename T>
T* ObjectPool<T>::containsObject(T* ptrObj) const
{
	for(T* object = m_ptr_objects_start; object < m_ptr_objects_end; ++object)
	{
		if(object == ptrObj)
		{
			return object;
		}
	}

	return nullptr;
}

//----------------------------------------------------------------------
//getter

//get a new object
template <typename T>
T* ObjectPool<T>::getNewObject()
{
	if (!isFull())
	{
		++m_ptr_objects_end;
		return m_ptr_objects_end - 1;
	}

	return nullptr;
}

//get the dummy object
template <typename T>
T* ObjectPool<T>::getDummy()
{
	return &m_dummy;
}

//get last object pointer in the Pool
template <typename T>
T* ObjectPool<T>::getLastObject() const
{
	return m_ptr_objects_end - 1;
}

//get first object pointer in the pool
template <typename T>
T* ObjectPool<T>::getObjects() const
{
	return m_ptr_objects_start;
}

//get typeinfo of the object type of the pool
template <typename T>
const std::type_info& ObjectPool<T>::getTypeInfo() const
{
	return m_r_typeid;
}


#endif
