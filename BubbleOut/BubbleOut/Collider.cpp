#include "stdafx.h"
#include "Collider.h"

FloatVector2 Collider::getCenter() const
{
	return FloatVector2(m_ptr_transform->position);
}
