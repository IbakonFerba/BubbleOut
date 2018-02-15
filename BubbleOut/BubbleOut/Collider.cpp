#include "stdafx.h"
#include "Collider.h"

FloatVector2 Collider::getCenter() const
{
	return m_ptr_transform->position + m_offset;
}

FloatVector2 Collider::getScale() const
{
	return m_ptr_transform->scale;
}
