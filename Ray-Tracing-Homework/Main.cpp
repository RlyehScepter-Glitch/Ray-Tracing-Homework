#include <fstream>

/// Output image resolution
static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;

void GenerateGrid()
{
	std::ofstream ppmFileStream("GridImage.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	std::string colors[6] = {"red", "green", "blue", "yellow", "purple", "cyan"};

	int i = 0;

	for (int y = 0; y < imageHeight; y++)
	{
		
		for (int x = 0; x < imageWidth; x++)
		{
			if (x == 480 || x == 960 || x == 1440)
				i++;

			if (i > 5)
				i = 0;

			int r = 0;
			int g = 0;
			int b = 0;

			if(colors[i] == "red")
			{
				r = std::rand() % 255;
			}
			else if (colors[i] == "green")
			{
				g = std::rand() % 255;
			}
			else if (colors[i] == "blue")
			{
				b = std::rand() % 255;
			}
			else if (colors[i] == "yellow")
			{
				r = std::rand() % 255;
				g = std::rand() % 255;
			}
			else if (colors[i] == "purple")
			{
				r = std::rand() % 255;
				b = std::rand() % 255;
			}
			else if (colors[i] == "cyan")
			{
				b = std::rand() % 255;
				g = std::rand() % 255;
			}

			ppmFileStream << r << " " << g << " " << b << "\t";
		}
		
		if (y < 270)
			i = 0;
		if (y >= 270 && y < 540)
			i = 4;
		if (y >= 540 && y < 810)
			i = 2;
		if (y >= 810)
			i = 0;

		ppmFileStream << "\n";
	}

	ppmFileStream.close();
}

int main()
{
	GenerateGrid();
}