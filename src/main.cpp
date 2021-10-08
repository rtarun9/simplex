#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "hittable_object.h"
#include "hittable_list.h"

#include <iostream>
#include <climits>
#include <random>

using namespace spx;

Vec3 getColor(const Ray& ray, HittableList& hittableList, int maximumDepth);

int main()
{
	// note : general setup
	// using Right handed orientation. Rays are shot from the bottom left with two offsets. First ray short to top left.

	constexpr int MAX_COLOR = 255;

	int nx = 500;
	int ny = 250;

	// setup camera
	Vec3 lookFrom = Vec3(0.0, 10.0, 10.0);
	Vec3 lookAt = Vec3(0, 0.0f, 0.0f);
	float distanceToFocus = 10.5f;
	float aperture = 0.6f;

	float aspectRatio = static_cast<float>(nx) / ny;

	Camera camera(lookFrom, lookAt, Vec3(0, 1, 0), 20.0f, aspectRatio, aperture, distanceToFocus);

	// setup scene objects.
	// used code from RTOW to get a bunch of random sphere's and test out the efficiency of  the code.

	const int OBJECT_COUNT = 484;
	HittableObject *objects[OBJECT_COUNT + 1];

	objects[0] = new Sphere(Vec3(0, -1000, 0), 1000, new LambertianDiffuse(Vec3(0.5f)));
	int i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMaterial = Utils::getInstance().getRandomFloatInRange();
			Vec3 center = Vec3(a + 0.9 * Utils::getInstance().getRandomFloatInRange(), 0.2f, b + 0.9 * Utils::getInstance().getRandomFloatInRange());
			if ((center - Vec3(4, 0.2, 0)).getLength() > 0.9)
			{
				if (chooseMaterial < 0.8)
				{
					objects[i++] = new Sphere(center, 0.2f, new LambertianDiffuse(Vec3(Utils::getInstance().getRandomFloatInRange() * Utils::getInstance().getRandomFloatInRange(), Utils::getInstance().getRandomFloatInRange() * Utils::getInstance().getRandomFloatInRange(),  Utils::getInstance().getRandomFloatInRange() * Utils::getInstance().getRandomFloatInRange())));
				}
				else if (chooseMaterial < 0.95)
				{
					objects[i++] = new Sphere(center, 0.2f, new Metal(Vec3(0.5f * (1 + Utils::getInstance().getRandomFloatInRange()), 0.5f * (1 + Utils::getInstance().getRandomFloatInRange()), 0.5f * (1 + Utils::getInstance().getRandomFloatInRange()))));
				}
				else
				{
					objects[i++] = new Sphere(center, 0.2f, new Dielectric(1.33f));
				}
			}
		}
	}

	objects[i++] = new Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f));
	objects[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, new LambertianDiffuse(Vec3(0.4f, 0.f, 0.1f)));
	objects[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.1f));

	HittableList hittableList(objects, OBJECT_COUNT);

	Utils::getInstance().initializeRNG(0.0f, 0.999999f);

	// send multiple rays and average out the color value to get rid of some of the hard edges.
	const int SAMPLES = 10;
	int maximumDepth = 10;

	const float GAMMA_CORRECTION = 1.0 / 2.2f;

	std::cout << "P3\n" << nx << " " << ny << "\n" << MAX_COLOR << '\n';

	// main 'render loop'
	for (int j = ny - 1; j >= 0; j--)
	{
		std::cerr << "\rLines Remaining : " << j << ' ' << std::flush;
		for (int i = 0; i < nx; i++)
		{
			Vec3 color(0.0f);
			for (int k = 0; k < SAMPLES; k++)
			{
				float u = (float(i) + Utils::getInstance().getRandomFloatInRange())/ float(nx);
				float v = (float(j) + Utils::getInstance().getRandomFloatInRange()) / float(ny);

				Ray ray = camera.getRay(u, v);
				color += getColor(ray, hittableList, maximumDepth);
			}

			color /= SAMPLES;
			color = Vec3(pow(color.getX(), GAMMA_CORRECTION), pow(color.getY(), GAMMA_CORRECTION), pow(color.getZ(), GAMMA_CORRECTION));

			displayColor(color, std::cout);
		}
	}

	std::cerr << "\nCompleted." << std::flush;

	for (auto object : objects)
	{
		delete object;
	}

	return 0;
}

Vec3 getColor(const Ray& ray, HittableList& hittableList, int maximumDepth)
{
	HitDetails hitDetails;

	float minimumParameter = 0.001f;
	float maxmiumParamter = std::numeric_limits<float>::max();

	if (hittableList.hit(ray, minimumParameter, maxmiumParamter, hitDetails))
	{
		if (maximumDepth <= 0)
		{
			return Vec3(0.0f);
		}

		Vec3 attenuation;
		Ray scattered;

		if (hitDetails.material->scatter(ray, hitDetails, attenuation, scattered))
		{
			return attenuation * getColor(scattered, hittableList, maximumDepth - 1);
		}
	}

	// setup for background color
	Vec3 normalizedDirection = ray.getDirection().getNormalized();

	float param = 0.5f * (normalizedDirection.getY() + 1);
	return (1.0f - param) * Vec3(1.0f) + (param) * Vec3(0.5f, 0.7f, 1.0f);
}

