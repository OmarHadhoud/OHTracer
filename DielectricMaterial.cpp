#include "DielectricMaterial.hpp"

DielectricMaterial::DielectricMaterial(double refIndex, const std::string &name) : Material(name)
{
	this->refIndex = refIndex;
}

Vec3 DielectricMaterial::GetBounceDirection(const Ray &ray, const Hit &hit) const
{
	Vec3 normal = hit.frontFace ? hit.normal : -hit.normal;
	auto refIndexVal = this->refIndex;
	if (hit.frontFace == true)
		refIndexVal = 1.0 / refIndex;
	auto dir = ray.Refract(normal, refIndexVal);
	return dir.Normalize();
}

DielectricMaterial::~DielectricMaterial() {}
