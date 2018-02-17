#pragma once

#ifndef COLLIDER_H
#define COLLIDER_H

#include "stdafx.h"
#include "FloatVector2.h"
#include "Transform.h"

class Collider
{
public:
	Collider(): m_ptr_transform(nullptr) {}
	virtual ~Collider() {}

	void setTransform(const Transform* ptrTrans) { m_ptr_transform = ptrTrans; }
	void setOffset(const FloatVector2& rOffset) { m_offset = rOffset; }

	FloatVector2 getCenter() const;
	FloatVector2 getScale() const;
protected:
	const Transform* m_ptr_transform;

	FloatVector2 m_offset;
};

#endif
