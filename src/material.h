#include "ray.h"
#include "hittable_object.h"

namespace spx
{
	class Material
	{
	public:
		virtual bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay) = 0;
	};

	class LambertianDiffuse : public Material
	{
	public:
		inline LambertianDiffuse(const Vec3& albedo);
		inline virtual bool scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay);

	private:
		// proportion of light absorbed to that of light  reflected/ refracted.
		Vec3 albedo;
	};

	inline LambertianDiffuse::LambertianDiffuse(const Vec3& albedo): albedo(albedo)
	{
	}

	bool LambertianDiffuse::scatter(const Ray& ray, const HitDetails& hitDetails, Vec3& attenuation, Ray& scatterdRay)
	{

	}
}