#include "stdafx.h"
#include "RectCollider.h"
//----------------------------------------------------------------------
//init
void RectCollider::init(const Transform* ptrTransform, const float width, const float height)
{
	setTransform(ptrTransform);

	m_dimensions.x = width;
	m_dimensions.y = height;
}

//----------------------------------------------------------------------
//setter
void RectCollider::setDimensions(const float width, const float height)
{
	m_dimensions.x = width;
	m_dimensions.y = height;
}



//----------------------------------------------------------------------
//getter
FloatVector2 RectCollider::getDimensions() const
{
	return m_dimensions * (m_ptr_transform->scale);
}
