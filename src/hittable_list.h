#pragma once

#include "hittable_object.h"

#include <vector>

namespace spx
{
	class HittableList : public HittableObject
	{
	public:
		HittableList();
		// note : cannot use a vector  here since the abstract class has no constructor. To use vector you need a vector of pointers, but leaving that for simplicity.
		HittableList(HittableObject **objects, size_t objectCount);

		virtual bool hit(const Ray& ray, float& minimumParameter, float& maximumParameter, HitDetails& hitDetails) override;

	private:
		HittableObject **hittableObjects;
		size_t objectCount;
	};
}