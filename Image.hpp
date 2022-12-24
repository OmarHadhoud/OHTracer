#pragma once

#include "Vec3.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

class Image
{
protected:
	int width;
	int height;
	bool printProgressBar;
public:
	std::vector<std::vector<Vec3>> pixels;
	Image(int width, int height, bool printProgressBar = false);
	void PrintProgressBar(int currentWidth, int currentHeight) const;
	virtual void Save(const std::string &imageName) const = 0;
	virtual ~Image() = 0;
};