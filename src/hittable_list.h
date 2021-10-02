#pragma once

#include "hittable_object.h"

#include <vector>

namespace spx
{
	class HittableList : public HittableObject
	{
	public:
		HittableList();
		// note : cannot use a vector  here since the abstract class has no constructor.
		HittableList(HittableObject **objects, size_t objectCount);

		virtual bool hit(const Ray& ray, float& minimumTime, float& maximumTime, HitDetails& hitDetails) override;

	private:
		HittableObject **hittableObjects;
		size_t objectCount;
	};
}