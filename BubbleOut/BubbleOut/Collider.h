#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include "stdafx.h"
#include "EngineObject.h"
#include "FloatVector2.h"
#include "Transform.h"

class Collider : public EngineObject
{
public:
	Collider()
	{
		pushInheritanceChain<Collider>();
	}
	virtual ~Collider() {}

	void setTransform(const Transform* t) { m_ptr_transform = t; }
	void setOffset(const FloatVector2& offset) { m_offset = offset; }

	FloatVector2 getCenter() const;
	FloatVector2 getScale() const;
protected:
	const Transform* m_ptr_transform;
	FloatVector2 m_offset;
};

#endif
