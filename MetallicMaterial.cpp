#include "MetallicMaterial.hpp"
#include "Sphere.hpp"

MetallicMaterial::MetallicMaterial(const Vec3 &albedo, double fuzziness, const std::string &name) : Material(name)
{
	this->albedo = albedo;
	this->fuzziness = fuzziness;
}

Vec3 MetallicMaterial::GetBounceDirection(const Ray &ray, const Hit &hit) const
{
	return ray.Reflect(hit.normal).Normalize() + Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1) * fuzziness;
}

MetallicMaterial::~MetallicMaterial() {}