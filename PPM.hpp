#pragma once

#include "Image.hpp"

class PPM : public Image
{
private:
	int maxColor;

public:
	PPM(int width, int height, int maxColor, bool printProgressBar = false);
	void Save(const std::string &imageName) const;
	~PPM();
};
