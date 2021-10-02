#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_object.h"
#include "hittable_list.h"

#include <iostream>
#include <climits>

using namespace spx;

Vec3 getColor(const Ray& ray, HittableList& hittableList);

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

	const Vec3 ORIGIN = Vec3(0.0f);
	const Vec3 LOWER_LEFT = Vec3(-2.0f, -1.0f, -1.0f);
	const Vec3 HORIZONTAL = Vec3(4.0f, 0.0f, 0.0f);
	const Vec3 VERTICAL = Vec3(0.0f, 2.0f, 0.0f);

	// setup scene objects.
	constexpr int OBJECT_COUNT = 1;
	HittableObject *objects[OBJECT_COUNT];
	objects[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);

	HittableList hittableList(objects, OBJECT_COUNT);

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			Ray ray(ORIGIN, LOWER_LEFT + u * HORIZONTAL + v * VERTICAL);
			Vec3 color = getColor(ray, hittableList);
			color *= MAX_COLOR;

			std::cout << color << '\n';
		}
	}

	return 0;
}


Vec3 getColor(const Ray& ray, HittableList& hittableList)
{
	HitDetails hitDetails;

	float minimumTime = 0.0f;
	float maxmiumTime = std::numeric_limits<float>::max();

	if (hittableList.hit(ray, minimumTime, maxmiumTime, hitDetails))
	{
		// change range of each component to [0, 1]. componenets can be -ve if the sufaceNormal points into the screen (-z direction)
		Vec3 surfaceNormal = 0.5f * (hitDetails.normal + Vec3(1.0f));
		return surfaceNormal;
	}

	Vec3 normalizedDirection = ray.getDirection().getNormalized();

	float param = 0.5f * (normalizedDirection.getY() + 1);

	return (1.0f - param) * Vec3(1.0f, 1.0f, 1.0f) + (param) * Vec3(0.3f, 0.0f, 0.70f);
}
