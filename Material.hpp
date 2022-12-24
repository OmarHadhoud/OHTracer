#pragma once

#include "Mesh.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include <string>

class Material
{
private:
	std::string name;

public:
	Material(const std::string &name);
	std::string GetName() const { return name; }
	virtual Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const = 0;
	virtual Vec3 GetColor() const = 0;
	virtual ~Material() = 0;
};