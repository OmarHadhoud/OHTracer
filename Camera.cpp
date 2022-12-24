#include "Camera.hpp"
#include "Utils.hpp"
#include <cmath>
#include <numbers>

static double DegreesToRadians(const double &deg)
{
	constexpr double PI = 3.141592653589793238462643383279502884;
	return (deg * PI / 180);
}

Camera::Camera(const Vec3 &position,
			   const Vec3 &lookAt,
			   const Vec3 &up,
			   const double &aspectRatio,
			   const double &fov,
			   const double &aperture,
			   const double &focusDistance)
{
	this->position = position;
	this->lookAt = lookAt;
	this->up = up;
	this->fov = fov;
	this->aperture = aperture;
	this->focusDistance = focusDistance;

	// Get the viewport size
	auto cameraHeight = 2 * tan(DegreesToRadians(fov) / 2.0);
	this->viewportSize = Vec3{cameraHeight * aspectRatio * focusDistance, cameraHeight * focusDistance, 1};

	// Create the basis for the camera
	auto w = (position - lookAt).Normalize();
	this->u = Cross(up, w).Normalize();
	this->v = Cross(w, u);

	// Calculate the bottom left pixel once and save it to use it later
	this->bottomLeft = this->position - (this->u * this->viewportSize.x / 2) -
					   (this->v * this->viewportSize.y / 2) -
					   w * this->focusDistance;
}

static Vec3 randomPointInDisk(Vec3 center, double radius)
{
	int iters = 0;
	while (iters < 100)
	{
		float x = random(-radius, radius);
		float y = random(-radius, radius);
		if (x * x + y * y <= radius * radius)
			return Vec3{x , y, 0} + center;
	}
	assert(false);
	return Vec3{0, 0, 0};
}

Ray Camera::GetRay(const double &s, const double &t) const
{
	auto target = this->bottomLeft + this->u * s + this->v * t;
	auto pos = this->position;
	if (this->aperture != 0)
	{
		auto randomPoint = randomPointInDisk(Vec3{0, 0, 0}, aperture / 2.0);
		pos += this->u * randomPoint.x + this->v * randomPoint.y;
	}
	auto dir = (target - pos).Normalize();
	return Ray{pos, dir};
}
