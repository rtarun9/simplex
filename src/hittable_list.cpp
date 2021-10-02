#include "hittable_list.h"

namespace spx
{
	HittableList::HittableList(): objectCount(0)
	{
	}

	HittableList::HittableList(HittableObject **objects, size_t objectCount): hittableObjects(objects), objectCount(objectCount)
	{
	}

	bool HittableList::hit(const Ray& ray, float& minimumTime, float& maximumTime, HitDetails& hitDetails)
	{
		bool hasRayHitObject = false;

		for (size_t i  = 0; i < objectCount; i++)
		{
			if (hittableObjects[i]->hit(ray, minimumTime, maximumTime, hitDetails))
			{
				hasRayHitObject = true;
				break;
			}
		}

		return hasRayHitObject;
	}
}