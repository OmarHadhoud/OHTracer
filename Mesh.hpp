#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"
#include <memory>

struct Mesh;

struct Hit
{
	double t;
	Vec3 point;
	Vec3 normal;
	bool frontFace;
	bool doesHit;
	std::shared_ptr<Mesh> mesh;
};

class Material;

class Mesh
{
protected:
	std::shared_ptr<Material> material;

public:
	Mesh(const std::shared_ptr<Material> &material);
	virtual ~Mesh() = 0;
	// get the t value (if exist) for the intersection of the mesh with the ray
	// returns false if no solution exists
	virtual bool IntersectRay(const Ray &ray, Hit &hit) const = 0;
	virtual Vec3 GetBounceDirection(const Ray &ray, const Hit &hit) const = 0;
	std::shared_ptr<const Material> GetMaterial() const { return material; }
};