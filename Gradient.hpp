#pragma once

#include "Vec3.hpp"

class Gradient
{
public:
	Vec3 startColor;
	Vec3 endColor;
	Gradient(const Vec3 &startColor, const Vec3 &endColor)
	{
		this->startColor = startColor;
		this->endColor = endColor;
	}
};