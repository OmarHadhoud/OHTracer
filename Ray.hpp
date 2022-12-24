#pragma once

#include "Vec3.hpp"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;
	Ray(const Vec3 &origin, const Vec3 &direction)
	{
		this->origin = origin;
		this->direction = direction;
	}
	Vec3 At(double t) const
	{
		return this->origin + this->direction * t;
	}
	Vec3 Reflect(const Vec3 &normal) const;
	Vec3 Refract(const Vec3 &normal, double refractionIndexRatio) const;
};