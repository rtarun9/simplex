#pragma once

#include "vec3.h"
#include "ray.h"
#include "utils.h"

namespace spx
{
	namespace cameraDefaults
	{
		const Vec3 ORIGIN = Vec3(0.0f);
		const Vec3 LOWER_LEFT = Vec3(-2.0f, -1.0f, -1.0f);
		const Vec3 HORIZONTAL = Vec3(4.0f, 0.0f, 0.0f);
		const Vec3 VERTICAL = Vec3(0.0f, 2.0f, 0.0f);
		const float FOV = 45.0f;
		const float ASPECT_RATIO = 2;
	}

	class Camera
	{
	public:
		Camera();
		Camera(const Vec3& position, const Vec3& lookAt, const Vec3& worldUp, float fov = 45.0f, float aspectRatio = 2, float aperture = 0.0f, float focusDistance= 0.0f);

		Ray getRay(float u, float v);

	private:
		Vec3 origin;
		Vec3 lowerLeftCorner;
		Vec3 horizontalRange;
		Vec3 verticalRange;

		float fov;
		float  aspectRatio;

		float aperature;
		float focusDistance;
		float lensRadius;
	};
}