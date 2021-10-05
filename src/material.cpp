#include "material.h"

namespace spx
{
	LambertianDiffuse::LambertianDiffuse(const Vec3& albedo): albedo(albedo)
	{
	}

	bool LambertianDiffuse::scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay)
	{
		Vec3 hitPoint = ray.getPointAtParameter(hitDetails.parameter);

		// target is the random point in unit sphere
		Vec3 target = hitPoint + hitDetails.normal + Utils::getInstance().getRandomPointInUnitSphere();
		scatterdRay = Ray(hitPoint, target - hitPoint);
		attenuation = albedo;
		return true;
	}

	Metal::Metal(const Vec3& albedo, float fuzziness): albedo(albedo), fuzziness(fuzziness)
	{
	}

	bool Metal::scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay)
	{
		// slightly randomise the reflected ray by choosing a new 'end' point for the reflected ray.
		// clamp fuzziness value in the range 0.0f to 1.0f
		fuzziness = fuzziness < 1.0f ? fuzziness : 1.0f;

		Vec3 reflectedRay = Utils::getInstance().reflect(ray.getDirection(), hitDetails.normal);
		scatterdRay = Ray(ray.getPointAtParameter(hitDetails.parameter), reflectedRay + fuzziness * Utils::getInstance().getRandomPointInUnitSphere());
		attenuation = albedo;

		// apparently has something to do with BRDF's and checks
		// checks whether the scattered direction is in the upper hemisphere
		//return dot(scatterdRay.getDirection(), hitDetails.normal) > 0;
		// for now, always assuming that reflection happens
		return true;
	}
}