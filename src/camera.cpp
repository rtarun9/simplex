#include "camera.h"

namespace spx
{
	Camera::Camera(): origin(cameraDefaults::ORIGIN), lowerLeftCorner(cameraDefaults::LOWER_LEFT),
					  horizontalRange(cameraDefaults::HORIZONTAL), verticalRange(cameraDefaults::VERTICAL)
	{
	}

	Camera::Camera(const Vec3& position, const Vec3& lookAt, const Vec3& worldUp, float fov, float aspect, float aperture, float focusDistance)
										: aspectRatio(aspect), focusDistance(focusDistance), aperature(aperture)
	{
		lensRadius = aperature / 2;

		// convert degeree to radians
		float theta = fov * 3.14159 / 180.0f;
		float heightHalf = tanf(theta / 2);
		float viewportHeight = 2.0f * heightHalf;
		float viewportWidth = aspectRatio * viewportHeight;

		origin = position;

		//z is opposite to what is expected, since z is facing in the screen.
		Vec3 w = (position - lookAt).normalize();
		Vec3 u = (cross(worldUp, w)).normalize();
		Vec3 v = cross(w, u);

		horizontalRange = (viewportWidth) * u * focusDistance;
		verticalRange = (viewportHeight) * v * focusDistance;

		lowerLeftCorner = origin - viewportWidth / 2  - viewportHeight / 2 - w * focusDistance;
	}

	Ray Camera::getRay(float u, float v)
	{
		Vec3 random = lensRadius * Utils::getInstance().getRandomPointInUnitSphere();
		Vec3 offset = u * random.getX() + v *random.getY();
		return Ray(origin + offset, lowerLeftCorner + u * horizontalRange + v * verticalRange - origin - offset);
	}
}