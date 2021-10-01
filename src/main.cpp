#include "vec3.h"

#include <iostream>

int main()
{
	constexpr int MAX_COLOR = 255;

	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			spx::Vec3 color(float(i) / nx, float(j) / ny, 0.6f);
			color *= (float)MAX_COLOR;

			std::cout << color << '\n';
		}
	}

	return 0;
}
