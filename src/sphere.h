#pragma once

#include "hittable_object.h"

namespace spx
{
	class Sphere : public HittableObject
	{
	public:
		Sphere();
		Sphere(const Vec3& center, float radius, Material *material);

		~Sphere();

		virtual bool hit(const Ray& ray, float& minimumParameter, float& maximumParamter, HitDetails& hitDetails) override;

	private:
		Vec3 center;
		float radius;
		Material *material;
	};
}