#pragma once

#ifndef FLOAT_VECTOR_2_H
#define FLOAT_VECTOR_2_H

#include "stdafx.h"

/*
 * A improved 2D Float Vector with
 * some vector functions and more operators
 * that the sf::Vector2f
 */
class FloatVector2 : public sf::Vector2f
{
public:
	FloatVector2() : sf::Vector2f(), m_lastHeading(0) {}

	FloatVector2(const float& x, const float& y) : sf::Vector2f(x, y), m_lastHeading(0) {}
	FloatVector2(const sf::Vector2f& rSfVector) : sf::Vector2f(rSfVector), m_lastHeading(0) {}
	FloatVector2(const sf::Vector2i& rSfVectori) : sf::Vector2f(rSfVectori), m_lastHeading(0) {}

	//operators
	FloatVector2 operator*(const FloatVector2& rOther) const;
	FloatVector2 operator*(const sf::Vector2f& rOther) const;

	void operator*=(const FloatVector2& rOther);
	void operator*=(const sf::Vector2f& rOther);
	void operator-=(const float& rVal);
	void operator+=(const float& rVal);

	//Functions
	float magnitude() const;
	void normalize();
	float headingAngle();

	//getter
	sf::Vector2f getSfVector() const;
	FloatVector2 getNormalized() const;
private:
	float m_lastHeading;
};

#endif