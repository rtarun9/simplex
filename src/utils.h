#pragma once

#include "vec3.h"
#include "hittable_object.h"

#include <random>

namespace spx
{
	class Utils
	{
	public:
		inline Utils();

		inline void initializeRNG(float min, float max);
		inline Vec3 getRandomPointInUnitSphere();
		inline float getRandomFloatInRange();

		inline Vec3 reflect(const Vec3& v, const Vec3& normal);
		inline bool refract(const Vec3& v, const Vec3& normal, float thetaM1OverThetaM2, Vec3& refractedVector);

		inline float schlick(float cos, float refractiveIndex);

		static inline Utils& getInstance();

	private:
		std::default_random_engine randomEngine;
		std::uniform_real_distribution<float> distribution;
	};

	inline Utils::Utils()
	{
	}

	inline void Utils::initializeRNG(float min, float max)
	{
		std::random_device randomDevice;
		std::default_random_engine eng(randomDevice());
		std::uniform_real_distribution<float> distr(min, max);

		distribution = distr;
		randomEngine = eng;
	}

	inline Vec3 Utils::getRandomPointInUnitSphere()
	{
		// initialize random number generator
		std::random_device randomDevice;
		std::default_random_engine eng(randomDevice());
		std::uniform_real_distribution<float> distribution(0, 1);

		Vec3 point;
		do
		{
			// use rejection method to find point that lies inside the unit sphere.
			// this picks a point in the range [-1, -1, -1] to [1, 1, 1].
			point = 2.0f * Vec3(distribution(eng), distribution(eng), distribution(eng)) - Vec3(1.0f);
		}while(point.getLengthSquare() >= 1.0f);

		return point;
	}

	inline float Utils::getRandomFloatInRange()
	{
		return distribution(randomEngine);
	}

	inline Vec3 Utils::reflect(const Vec3& v, const Vec3& normal)
	{
		// note : dot(v, normal) gives the length of projection of v on normal : so,
		// dot(v, normal) gives length of B (keep in mind B || normal, but normal is unit vector, B must be length of dot(v, normal).
		// we do v - 2 * .. because v and n points in opposite directions.

		return v - 2 * dot(v, normal) * normal;
	}

	inline bool Utils::refract(const Vec3& v, const Vec3& normal, float thetaM1OverThetaM2, Vec3& refractedVector)
	{
		// no idea about the calculations, putting  understanding of concept or math here
		Vec3 uv = v;
		uv.normalize();

		float dt = dot(uv, normal);
		float discriminant = 1.0f - thetaM1OverThetaM2 * thetaM1OverThetaM2 * (1 - dt * dt);

		if (discriminant > 0)
		{
			refractedVector = thetaM1OverThetaM2 * (uv - normal * dt) - normal * sqrtf(discriminant);
			return true;
		}
		else
		{
			return false;
		}
	}

	float Utils::schlick(float cos, float refractiveIndex)
	{
		float ro = (1 - refractiveIndex) / (1 + refractiveIndex);
		ro = ro * ro;

		return ro + (1 - ro) * powf((1 - cos), 5);
	}

	inline Utils& Utils::getInstance()
	{
		static Utils instance;
		return instance;
	}
}