#include "stdafx.h"
#include "RectCollider.h"
//----------------------------------------------------------------------
//init

void RectCollider::init(const Transform* ptrTransform, const float& rWidth, const float& rHeight)
{
	setTransform(ptrTransform);

	m_dimensions.x = rWidth;
	m_dimensions.y = rHeight;
}

//----------------------------------------------------------------------
//setter

void RectCollider::setDimensions(const float& rWidth, const float& rHeight)
{
	m_dimensions.x = rWidth;
	m_dimensions.y = rHeight;
}



//----------------------------------------------------------------------
//getter

FloatVector2 RectCollider::getDimensions() const
{
	return m_dimensions * (m_ptr_transform->scale);
}
