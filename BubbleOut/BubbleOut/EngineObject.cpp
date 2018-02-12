#include "stdafx.h"
#include "EngineObject.h"

bool EngineObject::isDerivedFrom(const std::size_t& rTypeHash)
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

void EngineObject::setObjectManager(ObjectManager* rObjManager)
{
	m_ptr_objManager = rObjManager;
}

