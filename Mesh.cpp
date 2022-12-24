#include "Mesh.hpp"

Mesh::Mesh(const std::shared_ptr<Material> &material)
{
	this->material = material;
}

Mesh::~Mesh() {}