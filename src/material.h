#include "ray.h"
#include "utils.h"

namespace spx
{
	class HitDetails;

	class Material
	{
	public:
		// abstract class that returns if the ray has been scattered. If scatterd, returns how much should the
		// scattered ray be atteunated by. Also returns the scattered ray
		virtual bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay) = 0;
	};

	class LambertianDiffuse : public Material
	{
	public:
		LambertianDiffuse(const Vec3& albedo);
		bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay);

	private:
		// lambertian diffuse doesnt not have any color : merely just directs ray in random direction.
		// the color vislble is just the color of  re direction ray * its attenutation.
		Vec3 albedo;
	};

	class Metal : public Material
	{
	public:
		Metal(const Vec3& albedo, float fuzziness = 0.0f);
		bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay);

	private:
		// perfect reflection happens in the metal.
		Vec3 albedo;
		float fuzziness;
	};

	class Dielectric : public Material
	{
	public:
		Dielectric(float refractiveIndex);
		bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay);

	private:
		float refractiveIndex;
	};
}