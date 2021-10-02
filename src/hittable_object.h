#pragma once

#include "ray.h"
#include "types.h"

namespace spx
{
	class HittableObject
	{
	public:
		// abstract hit function : all inherited classes need to implement this.
		virtual bool hit(const Ray& ray, float& minimumTime, float& maximumTime, HitDetails& hitDetails) = 0;
	};
}