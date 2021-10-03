#pragma once

#include "vec3.h"

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

	inline Utils& Utils::getInstance()
	{
		static Utils instance;
		return instance;
	}
}