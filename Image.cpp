#include "Image.hpp"
#include <string>

Image::Image(int width, int height, bool printProgressBar)
{
	this->width = width;
	this->height = height;
	this->printProgressBar = printProgressBar;
	std::vector<Vec3> rowValues(width, Vec3{});
	this->pixels = std::move(std::vector<std::vector<Vec3>>(width, rowValues));
}

Image::~Image(){}

void Image::PrintProgressBar(int currentWidth, int currentHeight) const
{
	if (this->printProgressBar == false)
		return;

	constexpr int bar_width = 40;
	auto pixels_drawn = currentHeight * this->width + currentWidth;
	auto percentage = ((long double)pixels_drawn / (long double)(this->width * (this->height + 1))) * 100;

	std::cout << std::setprecision(3) << std::fixed << percentage << "/100% (" << pixels_drawn << " pixels)" << std::endl;

	auto current_bar_width = percentage / 2.5;
	for (auto i = 0; i < current_bar_width; i++)
		std::cout << "#";

	std::cout << std::endl;
}