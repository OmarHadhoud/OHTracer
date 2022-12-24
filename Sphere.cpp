#include "Sphere.hpp"
#include "Utils.hpp"
#include <cmath>

Sphere::Sphere() : Mesh(nullptr)
{}

Sphere::Sphere(const Vec3 &center, double radius, const std::shared_ptr<Material> &material) : Mesh(material)
{
	this->center = center;
	this->radius = radius;
}

bool Sphere::IntersectRay(const Ray &ray, Hit &hit) const
{
	// expand the equation, P(t) = A + tb
	// t^2 b . b + 2tb . (A-C) + (A-C) . (A-C) - r^2 = 0
	Vec3 coeff{Dot(ray.direction, ray.direction), 2 * Dot(ray.direction, ray.origin - this->center), Dot(ray.origin - this->center, ray.origin - this->center) - this->radius * this->radius};
	double discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	// no solution
	if (discriminant < 0)
		return false;

	double disc_sqrt = sqrt(discriminant);
	auto t0 = (-coeff.y + disc_sqrt) / 2 * coeff.x;
	auto t1 = (-coeff.y - disc_sqrt) / 2 * coeff.x;
	if (t0 > t1 && t1 > 0.001)
		std::swap(t0, t1);

	// get hit point, normal, whether front facing or not
	if (t0 > 0.001 && (t0 < hit.t || hit.doesHit == false))
	{
		hit.doesHit = true;
		hit.t = t0;
		hit.point = ray.origin + ray.direction * hit.t;
		hit.normal = (hit.point - this->center) / this->radius;
		hit.frontFace = Dot(hit.normal, ray.direction) < 0;
		hit.mesh = std::make_shared<Sphere>(*this);
	}

	return hit.doesHit;
}

Vec3 Sphere::GetBounceDirection(const Ray &ray, const Hit &hit) const
{
	return this->material->GetBounceDirection(ray, hit);
}

Vec3 Sphere::randomPointInSphere(Vec3 center, double radius)
{
	int iters = 0;
	while (iters < 100)
	{
		float x = random(-radius, radius);
		float y = random(-radius, radius);
		float z = random(-radius, radius);
		if (x * x + y * y + z * z <= radius * radius)
			return Vec3{x, y, z} + center;
	}
	assert(false);
	return Vec3{0, 0, 0};
}

Sphere::~Sphere() {}