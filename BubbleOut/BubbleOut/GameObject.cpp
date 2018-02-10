#include "stdafx.h"
#include "GameObject.h"

bool GameObject::isInheritedFrom(const std::size_t& typeHash)
{
	for (unsigned i = 0; i < m_inheritanceChain.size(); ++i)
	{
		if (typeHash == m_inheritanceChain.at(i))
		{
			return true;
		}
	}

	return false;
}

void GameObject::setObjectManager(ObjectManager* objManager)
{
	m_objManager = objManager;
}

