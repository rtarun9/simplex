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
	constexpr int MAX_COLOR = 255;

	int nx = 500;
	int ny = 250;

	// note : general setup
	// camera (from where we shoot rays to the 'screen') is at 0, 0, 0.
	// window aspect ratio : 2 : 1.
	// The Window dimesions are : w(4), h(2)
	// using Right handed orientation. Rays are shot from the bottom left with two offsets. First ray short to top left.

	Vec3 lookFrom = Vec3(0.0, 2, 5);
	Vec3 lookAt = Vec3(0.0, -1.0f, -0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.1;

	Camera camera(lookFrom, lookAt, Vec3(0, 1, 0), 50.0f, 2.0f, aperture, distanceToFocus);

	// setup scene objects.
	constexpr int OBJECT_COUNT = 30;
	HittableObject *objects[OBJECT_COUNT];
	Vec3 offset = Vec3(0.0f, 0.0f, -1.5f);

	for (int i = 0; i < OBJECT_COUNT - 1; i++)
	{
		Vec3 color = Vec3(Utils::getInstance().getRandomFloatInRange(), Utils::getInstance().getRandomFloatInRange(), Utils::getInstance().getRandomFloatInRange());

		offset += Vec3(1.0f, 0, -1.0);

		if(i > 10)
			offset += Vec3(0.0f, 0, 2.0);

		if (i % 2 == 0)
		{
			objects[i] = new Sphere(offset, 0.5f, new LambertianDiffuse(color));
		}
		else
		{
			objects[i] = new Sphere(offset, 0.5f, new Metal(color));

			if (i % 3 == 0)
			{
				objects[i] = new Sphere(offset, 0.5f, new Dielectric(0.5f));
			}

			if (i % 5 == 0)
			{
				objects[i] = new Sphere(offset, 0.5f, new Dielectric(0.333f));
			}
		}
	}

	objects[OBJECT_COUNT - 1] = new Sphere(Vec3(0.0f, -1000.5f, -1.0f), 1000.0f, new LambertianDiffuse(Vec3(0.3f, 0.1f, 0.1f)));

	HittableList hittableList(objects, OBJECT_COUNT);

	Utils::getInstance().initializeRNG(0.0f, 0.999999f);

	// send multiple rays and average out the color value to get rid of some of the hard edges.
	const int SAMPLES = 10;
	int maximumDepth = 10;

	const float GAMMA_CORRECTION = 1.0 / 2.2f;

	std::cout << "P3\n" << nx << " " << ny << "\n" << MAX_COLOR << '\n';

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

		// change range of each component to [0, 1]. componenets can be -ve if the sufaceNormal points into the screen (-z direction)
		//Vec3 surfaceNormal = 0.5f * (hitDetails.normal.getNormalized() + Vec3(1.0f));
		//return surfaceNormal;

		// for diffuse materials

		Vec3 attenuation;
		Ray scattered;

		if (hitDetails.material->scatter(ray, hitDetails, attenuation, scattered))
		{
			return attenuation * getColor(scattered, hittableList, maximumDepth - 1);
		}
	}

	Vec3 normalizedDirection = ray.getDirection().getNormalized();

	float param = 0.5f * (normalizedDirection.getY() + 1);

	// purple background hue
	return (1.0f - param) * Vec3(1.0f, 1.0f, 1.0f) + (param) * Vec3(0.7001f, 0.0f, 0.601f);

	// dark grayish background hue
	//return (1.0f - param) * Vec3(1.0f, 1.0f, 1.0f) * 0.3f + (param) * Vec3(0.01001f, 0.0f, 0.0101f);
}

