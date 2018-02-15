#pragma once

#ifndef FLOAT_VECTOR_2_H
#define FLOAT_VECTOR_2_H

#include "stdafx.h"

class FloatVector2 : public sf::Vector2f
{
public:
	FloatVector2() : sf::Vector2f() {}
	FloatVector2(const float x, const float y) : sf::Vector2f(x, y) {}
	FloatVector2(const sf::Vector2f& sfVector) : sf::Vector2f(sfVector) {}
	FloatVector2(const sf::Vector2i& sfVectori) : sf::Vector2f(sfVectori) {}

	//operators
	FloatVector2 operator*(const FloatVector2& other) const;
	FloatVector2 operator*(const sf::Vector2f& other) const;
	void operator*=(const FloatVector2& other);
	void operator*=(const sf::Vector2f& other);

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