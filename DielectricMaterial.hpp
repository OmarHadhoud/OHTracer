#pragma once

#include "Material.hpp"
#include <string>

class DielectricMaterial: public Material
{
public:
	double refIndex;
	DielectricMaterial(double refIndex, const std::string &name);
	Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const;
	Vec3 GetColor() const { return Vec3{1, 1, 1}; }
	~DielectricMaterial();
};
