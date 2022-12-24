#pragma once

#include "Material.hpp"
#include <string>

class MetallicMaterial: public Material
{
public:
	Vec3 albedo;
	double fuzziness;
	MetallicMaterial(const Vec3 &albedo, double fuzziness, const std::string &name);
	Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const;
	Vec3 GetColor() const { return albedo; }
	~MetallicMaterial();
};
