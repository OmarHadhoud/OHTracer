#pragma once

#include "Material.hpp"
#include <string>

class DiffuseMaterial: public Material
{
public:
	Vec3 albedo;
	DiffuseMaterial(const Vec3 &albedo, const std::string &name);
	Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const;
	Vec3 GetColor() const { return albedo; }
	~DiffuseMaterial();
};
