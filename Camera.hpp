#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera
{
public:
	Vec3 position;
	Vec3 direction;
	Vec3 lookAt;
	Vec3 viewportSize;
	Vec3 up;
	Vec3 u;
	Vec3 v;
	Vec3 bottomLeft;
	double fov;
	double aperture;
	double focusDistance;

	Camera(const Vec3 &position,
		   const Vec3 &lookAt,
		   const Vec3 &up,
		   const double &aspectRatio,
		   const double &fov,
		   const double &aperture,
		   const double &focusDistance);
	Ray GetRay(const double &s, const double &t) const;
};
