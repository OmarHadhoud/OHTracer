#include "Vec3.hpp"
#include "Gradient.hpp"
#include "PPM.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include <iostream>
#include <memory>

int main()
{
	// Constants
	constexpr int samplesPerPixel = 100;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = 225;
	constexpr double aspectRatio = (double)imageWidth / (double)imageHeight;
	constexpr double fov = 20;
	constexpr double aperture = 0.1;
	constexpr double focusDistance = 10;

	auto image = std::make_unique<PPM>(imageWidth, imageHeight, 255, true);
	auto backgroundGradient = Gradient(Vec3{1, 1, 1}, Vec3{128.0 / 255.0, 180.0 / 255.0, 1});

	auto spheres = GenerateRandomScene();

	auto camera = Camera(Vec3{13, 3, 3},
						 Vec3{0, 0, 0},
						 Vec3{0, 1, 0},
						 aspectRatio,
						 fov,
						 aperture,
						 focusDistance);

	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			auto pixelColor = Vec3{0, 0, 0};
			for (int k = 0; k < samplesPerPixel; k++)
			{
				auto s = ((j + random()) * camera.viewportSize.x) / imageWidth;
				auto t = ((i + random()) * camera.viewportSize.y) / imageHeight;
				auto cameraRay = camera.GetRay(s, t);
				pixelColor += getRayHitColor(cameraRay, spheres, backgroundGradient, 0);
			}
			image->pixels[i][j] = GammaCorrect(pixelColor / samplesPerPixel);
		}
	}
	image->Save("output");

	return 1;
}