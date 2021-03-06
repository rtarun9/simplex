#include "material.h"

namespace spx
{
	LambertianDiffuse::LambertianDiffuse(const Vec3& albedo): albedo(albedo)
	{
	}

	bool LambertianDiffuse::scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay)
	{
		Vec3 hitPoint = ray.getPointAtParameter(hitDetails.parameter);

		// target is the random point in unit sphere, centered at randomPoint - Hitpoint
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

	Dielectric::Dielectric(float refractiveIndex): refractiveIndex(refractiveIndex)
	{
	}

	bool Dielectric::scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay)
	{
		// bit complicated math, need to read it up
		// good explanation is given here : https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
		// the dielectric materiail will randomly either reflect or refract.

		Vec3 outwardNormal;
		Vec3  reflected = Utils::getInstance().reflect(ray.getDirection(), hitDetails.normal);
		float niOverNt;
		attenuation = Vec3(1.0f);

		Vec3 refracted;

		float reflectProbability;
		float  cos;

		// if the dot product  is greater than 0, the ray's direction and normal is in the same directions.
		// think of it as the case when  light  is entering a new medium : by default from lower medium to higher (air to glass, etc).
		if (dot(ray.getDirection(), hitDetails.normal) > 0)
		{
			outwardNormal = -1 * hitDetails.normal;
			niOverNt = refractiveIndex;
			cos = refractiveIndex * dot(ray.getDirection(), hitDetails.normal) / ray.getDirection().getLength();
		}

		// else, the ray is going from a higher refractive index to a  medium of lower  refractive index. (the ray is going from inside of dieletric objectt to the outside environment.)
		else
		{
			outwardNormal = hitDetails.normal;
			niOverNt = 1.0f / refractiveIndex;
			cos = -1 * dot(ray.getDirection(), hitDetails.normal) / ray.getDirection().getLength();
		}

		if (Utils::getInstance().refract(ray.getDirection(), outwardNormal, niOverNt, refracted))
		{
			reflectProbability = Utils::getInstance().schlick(cos, refractiveIndex);
		}
		else
		{
			scatterdRay = Ray(ray.getPointAtParameter(hitDetails.parameter), reflected);
			reflectProbability = 1.0f;
		}

		if (Utils::getInstance().getRandomFloatInRange() < reflectProbability)
		{
			scatterdRay = Ray(ray.getPointAtParameter(hitDetails.parameter), reflected);
		}
		else
		{
			scatterdRay = Ray(ray.getPointAtParameter(hitDetails.parameter), refracted);
		}

		return true;
	}
}