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

	FloatVector2 getCenter() const;
protected:
	const Transform* m_ptr_transform;
};

#endif
