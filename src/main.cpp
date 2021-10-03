#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
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

	int nx = 200;
	int ny = 100;

	// note : general setup
	// camera (from where we shoot rays to the 'screen') is at 0, 0, 0.
	// window aspect ratio : 2 : 1.
	// The Window dimesions are : w(4), h(2)
	// using Right handed orientation. Rays are shot from the bottom left with two offsets. First ray short to top left.

	Camera camera(Vec3(0.0f));

	// setup scene objects.
	constexpr int OBJECT_COUNT = 2;
	HittableObject *objects[OBJECT_COUNT];
	objects[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
	objects[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);

	HittableList hittableList(objects, OBJECT_COUNT);

	Utils::getInstance().initializeRNG(0.0f, 0.9999f);

	// send multiple rays and average out the color value to get rid of some of the hard edges.
	const int SAMPLES = 100;
	int maximumDepth = 50;

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

			color *= Vec3(255.99, 255.99, 255.99);

			std::cout << color << '\n';
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
		Vec3 objectHitPoint = ray.getPointAtParameter(hitDetails.parameter);

		// target is a random point inside of a unit sphere on the surface of the hittable object.
		Vec3 target = objectHitPoint + hitDetails.normal + Utils::getInstance().getRandomPointInUnitSphere();
		return 0.5f * getColor(Ray(objectHitPoint, target - objectHitPoint), hittableList, maximumDepth - 1);
	}

	Vec3 normalizedDirection = ray.getDirection().getNormalized();

	float param = 0.5f * (normalizedDirection.getY() + 1);

	return (1.0f - param) * Vec3(1.0f, 1.0f, 1.0f) + (param) * Vec3(0.7001f, 0.0f, 0.601f);
}

