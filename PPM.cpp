#include "PPM.hpp"
#include <fstream>

PPM::PPM(int width, int height, int maxColor, bool printProgressBar) : Image(width, height, printProgressBar)
{
	this->maxColor = maxColor;
}

void PPM::Save(const std::string &imageName) const
{
	std::ofstream outputFile;
	outputFile.open(imageName + ".ppm");
	if (!outputFile)
	{
		std::cerr << "Could not open file " << imageName << " to write to!" << std::endl;
		exit(1);
	}

	outputFile << "P3 " << this->width << " " << this->height << " " << this->maxColor << std::endl;
	for (auto i = this->height - 1; i >= 0; i--)
	{
		for (auto j = 0; j < this->width; j++)
		{
			auto pixel = this->pixels[i][j];
			pixel = pixel * this->maxColor;
			outputFile << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b << std::endl;
			PrintProgressBar(j, this->height - i);
		}
	}

	outputFile.close();
}

PPM::~PPM()
{

}