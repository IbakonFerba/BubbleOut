#include "stdafx.h"
#include "FloatVector2.h"

//------------------------------------------------------------------------------------------
//functions
// Returns the length of the vector
float FloatVector2::magnitude() const
{
	return sqrt(x * x + y * y);
}

void FloatVector2::normalize()
{
	const float mag = magnitude();

	if (mag != 0) {
		x = x / mag;
		y = y / mag;
	}
}

float FloatVector2::headingAngle()
{
	if (magnitude() != 0.0)
	{
		m_lastHeading = std::atan2f(y, x) * 180 / M_PI;
	}
	return m_lastHeading;
}



//------------------------------------------------------------------------------------------
//getter
sf::Vector2f FloatVector2::getSfVector() const
{
	return sf::Vector2f(x, y);
}

FloatVector2 FloatVector2::getNormalized() const
{
	FloatVector2 normalizedVector(*this);

	normalizedVector.normalize();
	return normalizedVector;
}

