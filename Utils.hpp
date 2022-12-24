#pragma once

#include "Sphere.hpp"
#include "DiffuseMaterial.hpp"
#include "DielectricMaterial.hpp"
#include "MetallicMaterial.hpp"
#include "Gradient.hpp"
#include <cmath>
#include <vector>
#include <cassert>
#include <memory>

// returns random in range [0, 1[
double random();
// returns random in range passed [min, max[
double random(double min, double max);
Vec3 GammaCorrect(const Vec3 &color, double gamma = 2.2);
Vec3 backgroundColor(Vec3 direction, Gradient gradient);
std::vector<Sphere> GenerateRandomScene();
Vec3 getRayHitColor(Ray ray, const std::vector<Sphere> &spheres, Gradient backgroundGradient, int rayHitCount);