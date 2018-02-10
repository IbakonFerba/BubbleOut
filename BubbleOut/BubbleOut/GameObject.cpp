#include "stdafx.h"
#include "GameObject.h"

bool GameObject::isInheritedFrom(const std::size_t& rTypeHash)
{
	for (unsigned i = 0; i < m_inheritanceChain.size(); ++i)
	{
		if (rTypeHash == m_inheritanceChain.at(i))
		{
			return true;
		}
	}

	return false;
}

void GameObject::setObjectManager(ObjectManager* rObjManager)
{
	m_ptr_objManager = rObjManager;
}

