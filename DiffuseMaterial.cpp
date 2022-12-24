#include "DiffuseMaterial.hpp"
#include "Sphere.hpp"

DiffuseMaterial::DiffuseMaterial(const Vec3 &albedo, const std::string &name) : Material(name)
{
	this->albedo = albedo;
}

Vec3 DiffuseMaterial::GetBounceDirection(const Ray &ray, const Hit &hit) const
{
	Vec3 normal = hit.frontFace ? hit.normal : -hit.normal;
	auto dir = Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1);
	if (Dot(dir, normal) < 0)
		dir = -dir;
	return dir.Normalize();
}


DiffuseMaterial::~DiffuseMaterial() {}