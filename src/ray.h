#pragma once

#include "vec3.h"

namespace spx
{
	class Ray
	{
	public:
		Ray();
		Ray(const Vec3& origin, const Vec3& direction);

		Vec3 getOrigin() const;
		Vec3 getDirection() const;

		Vec3 getPointAtParameter(float t) const;

		void setOrigin(const Vec3& newOrigin);
		void setDirection(const Vec3& newDirection);

	private:
		Vec3 origin;
		Vec3 direction;
	};

	inline Ray::Ray(): origin(Vec3(0.0f)), direction(Vec3(0.0f))
	{
	}

	inline Ray::Ray(const Vec3& origin, const Vec3& direction): origin(origin), direction(direction)
	{
	}

	inline Vec3 Ray::getOrigin() const
	{
		return origin;
	}

	inline Vec3 Ray::getDirection() const
	{
		return direction;
	}

	inline Vec3 Ray::getPointAtParameter(float t) const
	{
		return origin + t * direction;
	}

	inline void Ray::setOrigin(const Vec3& newOrigin)
	{
		origin = newOrigin;
	}

	inline void Ray::setDirection(const Vec3& newDirection)
	{
		direction = newDirection;
	}
}
