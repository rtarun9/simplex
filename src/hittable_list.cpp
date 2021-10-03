#include "hittable_list.h"

namespace spx
{
	HittableList::HittableList(): objectCount(0)
	{
	}

	HittableList::HittableList(HittableObject **objects, size_t objectCount): hittableObjects(objects), objectCount(objectCount)
	{
	}

	bool HittableList::hit(const Ray& ray, float& minimumParameter, float& maximumParameter, HitDetails& hitDetails)
	{
		bool hasRayHitObject = false;
		float closestHitSoFar = maximumParameter;

		for (size_t i  = 0; i < objectCount; i++)
		{
			if (hittableObjects[i]->hit(ray, minimumParameter, closestHitSoFar, hitDetails))
			{
				closestHitSoFar = hitDetails.parameter;
				hasRayHitObject = true;
			}
		}

		return hasRayHitObject;
	}
}