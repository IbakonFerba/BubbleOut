#include "stdafx.h"
#include "Barrier.h"

void Barrier::init(ObjectManager* ptrObjectManager, const FloatVector2& rPosition, const float& rWidth, const float& rHeight, const Tag& rTag)
{
	//get components
	m_ptr_trans = ptrObjectManager->getNewObject<Transform>();
	m_ptr_col = ptrObjectManager->getNewObject<RectCollider>();
	m_ptr_rigidbody = ptrObjectManager->getNewObject<Rigidbody>();

	//init values
	tag = rTag;

	//init components
	m_ptr_trans->position = rPosition;
	m_ptr_col->init(m_ptr_trans, rWidth, rHeight);
	m_ptr_rigidbody->init(this, m_ptr_col, m_ptr_trans, 0, 1);
	m_ptr_rigidbody->kinematic = true;
}
