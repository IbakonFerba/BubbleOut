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
