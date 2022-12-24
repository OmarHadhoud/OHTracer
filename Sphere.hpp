#pragma once

#include "Vec3.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include <memory>

class Sphere : public Mesh
{
private:
	Vec3 center;
	double radius;
public:
	Sphere();
	Sphere(const Vec3 &center, double radius, const std::shared_ptr<Material> &material);
	~Sphere();
	// get the t value (if exist) for the intersection of the sphere with the ray
	// solves the equation: (P(t) - C) . (P(t) - C) = r^2
	// returns -false if no solution exists
	bool IntersectRay(const Ray &ray, Hit &hit) const;
	Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const;
	static Vec3 randomPointInSphere(Vec3 center, double radius);
};