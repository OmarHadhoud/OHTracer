#include "Utils.hpp"


// returns random in range [0, 1[
double random()
{
	double num = rand();
	num /= (RAND_MAX + 1);
	return num;
}

// returns random in range passed [min, max[
double random(double min, double max)
{
	double num = random();
	// map [0, 1] -> [min, max]
	num = min + num * (max - min);
	return num;
}

Vec3 GammaCorrect(const Vec3 &color, double gamma)
{
	Vec3 gammaCorrectedColor;
	gammaCorrectedColor.x = pow(color.x, 1.0 / 2.2);
	gammaCorrectedColor.y = pow(color.y, 1.0 / 2.2);
	gammaCorrectedColor.z = pow(color.z, 1.0 / 2.2);
	return gammaCorrectedColor;
}

Vec3 backgroundColor(Vec3 direction, Gradient gradient)
{
	auto t = direction.Normalize().y * 0.5 + 0.5;
	return Lerp(gradient.startColor, gradient.endColor, t);
}

std::vector<Sphere> GenerateRandomScene()
{
	constexpr double sphereRadius = 0.2;

	std::vector<Sphere> spheres;
	int sphereIndex = 0;
	//Create the ground sphere
	auto groundMaterial = std::make_shared<DiffuseMaterial>(Vec3{0.5, 0.5, 0.5}, "ground_material");
	auto groundSphere = Sphere(Vec3{0, -1000, 0}, 1000, groundMaterial);
	spheres.push_back(groundSphere);

	for (int i = -11; i < 11; i++)
	{
		for (int j = -11; j < 11; j++)
		{
			std::shared_ptr<Material> mat;
			auto chooseMaterial = random();
			if (chooseMaterial < 0.8)
			{
				// auto color
				auto diffMat = std::make_shared<DiffuseMaterial>(Vec3{0, 0, 0,}, "");
				diffMat->albedo = Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1) * Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1);
				mat = diffMat;
			}
			else if (chooseMaterial < 0.95)
			{
				auto fuzziness = random(0, 0.5);
				auto metMat = std::make_shared<MetallicMaterial>(Vec3{0, 0, 0,}, fuzziness, "");
				metMat->albedo = Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1) * Sphere::randomPointInSphere(Vec3{0, 0, 0}, 1);
				mat = metMat;
			}
			else
			{
				auto refIndex = random(1, 2);
				auto diMat = std::make_shared<DielectricMaterial>(refIndex, "");
				mat = diMat;
			}

			auto sphereCenter = Vec3{i + random(), sphereRadius, j + random()};
			auto sphere = Sphere(sphereCenter, sphereRadius, mat);
			spheres.push_back(sphere);
		}
	}

	//Add 3 large spheres
	auto mat1 = std::make_shared<DielectricMaterial>(1.5, "");
	auto sphere1 = Sphere(Vec3{0, 1, 0}, 1.0, mat1);
	spheres.push_back(sphere1);

	auto mat2 = std::make_shared<DiffuseMaterial>(Vec3{0.4, 0.2, 0.1}, "");
	auto sphere2 = Sphere(Vec3{-4, 1, 0}, 1.0, mat2);
	spheres.push_back(sphere2);
	
	auto mat3 = std::make_shared<MetallicMaterial>(Vec3{0.7, 0.6, 0.5}, 0.0, "");
	auto sphere3 = Sphere(Vec3{4, 1, 0}, 1.0, mat3);
	spheres.push_back(sphere3);

	return spheres;
}

Vec3 getRayHitColor(Ray ray, const std::vector<Sphere> &spheres, Gradient backgroundGradient, int rayHitCount)
{
	if (rayHitCount == 50)
		return Vec3{0, 0, 0};

	// check for any ray hit
	Hit hit{};
	for (auto &sphere: spheres)
		sphere.IntersectRay(ray, hit);

	if (hit.doesHit)
	{
		Vec3 lightReflection = hit.mesh->GetBounceDirection(ray, hit);
		Ray bouncedRay {hit.point, lightReflection};
		auto sphereMat = hit.mesh->GetMaterial();
		// auto final_color = sphereMat->GetColor();
		auto final_color = sphereMat->GetColor() *
						   getRayHitColor(bouncedRay , spheres, backgroundGradient, rayHitCount + 1);

		return final_color;
	}
	else
	{
		return backgroundColor(ray.direction, backgroundGradient);
	}
}