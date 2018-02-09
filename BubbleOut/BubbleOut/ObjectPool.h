#pragma once

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "stdafx.h"

template <typename T>
class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();

	void deleteObject(T* object);

	T* getObjects() const;
	T* getLastObject() const;
	T* getNewObject();

	const T& getDummy() const;
	const std::type_info& getTypeInfo() const;

	bool isFull() const;
private:
	static const int SIZE = 128;

	T* m_objects_start;
	T* m_objects_end;
	T* m_last_spot;
	const std::type_info& m_typeid;
	const T m_dummy;
};

//----------------------------------------------------------------------
//implementation iside header file because linker throws an error otherwise (or I have to include the cpp file everywhere)


//----------------------------------------------------------------------
//constructor
template <typename T>
ObjectPool<T>::ObjectPool() : m_typeid(typeid(T)), m_dummy()
{
	m_objects_start = new T[SIZE];
	m_objects_end = m_objects_start;

	m_last_spot = m_objects_start + SIZE;
}

//----------------------------------------------------------------------
//destructor
template <typename T>
ObjectPool<T>::~ObjectPool()
{
	delete[] m_objects_start;
}

//----------------------------------------------------------------------
//object management
template <typename T>
void ObjectPool<T>::deleteObject(T* object)
{
	*object = *(m_objects_end - 1);
	--m_objects_end;
}


//----------------------------------------------------------------------
//checks
template <typename T>
bool ObjectPool<T>::isFull() const
{
	return m_objects_end == m_last_spot;
}

//----------------------------------------------------------------------
//getter
template <typename T>
T* ObjectPool<T>::getNewObject()
{
	if (!isFull())
	{
		++m_objects_end;
		return m_objects_end - 1;
	}

	return nullptr;
}

template <typename T>
const T& ObjectPool<T>::getDummy() const
{
	return m_dummy;
}

template <typename T>
T* ObjectPool<T>::getLastObject() const
{
	return m_objects_end - 1;
}

template <typename T>
T* ObjectPool<T>::getObjects() const
{
	return m_objects_start;
}

template <typename T>
const std::type_info& ObjectPool<T>::getTypeInfo() const
{
	return m_typeid;
}


#endif
