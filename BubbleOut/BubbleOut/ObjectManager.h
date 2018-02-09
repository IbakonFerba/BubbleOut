#pragma once

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "stdafx.h"
#include "ObjectPool.h"
#include "GameObject.h"


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	template <typename T>
	T* getNewObject();

	//get all objects of type
	//delete object
private:
	std::vector<ObjectPool<GameObject>>* m_pools;
};

#endif
