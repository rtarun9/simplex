#pragma once

#include "ray.h"

class Material;

namespace spx
{
	struct HitDetails
	{
		// to locate the point given a ray
		float parameter;

		Vec3 normal;
		Ray ray;

		Material *material;
	};

	class HittableObject
	{
	public:
		// abstract hit function : all inherited classes need to implement this.
		virtual bool hit(const Ray& ray, float& minimumParamter, float& maximumParameter, HitDetails& hitDetails) = 0;
	};
}