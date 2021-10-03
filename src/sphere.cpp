#include "sphere.h"

namespace spx
{
	Sphere::Sphere(): radius(0.5f)
	{
		center = (Vec3(0.0f, 0.0f, -1.0f));
	}

	Sphere::Sphere(const Vec3& circleCenter, float radius): radius(radius)
	{
		center = circleCenter;
	}

	bool Sphere::hit(const Ray& ray, float& minimumParameter, float& maximumParameter, HitDetails& hitDetails)
	{
		// note : related math
		// for a point to lie on the sphere, it must satisfy circle equation : (x - cx)^2 * (y - cy)^2 * (z - cz)^ = R^2.
		// in ray form, dot(r(t) - center) * dot(r(t) - center) = R^2.
		// simplifying,
		// dot(a + bt - c) * dot(a + bt - c) = R^2
		// a^2 + abt - ac + abt + (bt)^2 - cbt - ac - btc + c^ = R^2.
		// t^2(b * b) + t(2ab - 2cb) + (a^2 - 2ac + c^2 - R^2) = 0
		// t^2(b * b) + 2 * t * b(a - c) + (a - c)(a - c) - R^2 = 0;

		float quadratic = dot(ray.getDirection(), ray.getDirection());
		float linear = 2 * dot(ray.getDirection(), (ray.getOrigin() - center));
		float constant = dot(ray.getOrigin() - center, ray.getOrigin() - center) - radius * radius;

		// consider quadratic equation of form ax^2 + bx + c = 0;
		float determinant = (linear * linear - 4 * quadratic * constant);
		if (determinant > 0.0f)
		{
			// first check for the smallest root.
			float t = (-linear - sqrtf(determinant)) / (2.0f * quadratic);

			if (t > minimumParameter && t < maximumParameter)
			{
				hitDetails.parameter = t;
				hitDetails.ray = ray;
				hitDetails.normal = (ray.getPointAtParameter(t) - center).getNormalized();

				return true;

			}
			else
			{
				float t = (-linear + sqrtf(determinant)) / (2.0f * quadratic);
				if (t > minimumParameter && t < maximumParameter)
				{
					hitDetails.parameter = t;
					hitDetails.ray = ray;
					hitDetails.normal = (ray.getPointAtParameter(t) - center).getNormalized();
					return true;
				}
			}
		}

		return false;
	}
}