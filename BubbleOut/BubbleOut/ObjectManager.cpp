#include "stdafx.h"
#include "ObjectManager.h"

//----------------------------------------------------------------------
//constructor
ObjectManager::ObjectManager()
{
	m_ptr_pools = new std::vector<ObjectPoolBase*>();
}

//----------------------------------------------------------------------
//destructor
ObjectManager::~ObjectManager()
{
	delete m_ptr_pools;
}

//----------------------------------------------------------------------
//object managment
//void ObjectManager::deleteObjects()
//{
//	for(unsigned i = 0; i < m_ptr_pools->size(); ++i)
//	{
//		m_ptr_pools->at(i)->deleteMarkedObjects();
//	}
//}
