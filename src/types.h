#pragma once

#include "ray.h"

namespace spx
{
	struct HitDetails
	{
		// to locate the point given a ray
		float parameter;

		Vec3 normal;
		Ray ray;
	};
}