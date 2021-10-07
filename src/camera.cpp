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
		fov = fov * 3.14159 / 180.0f;

		float heightHalf = tanf(fov / 2);
		float widthHalf = aspectRatio * heightHalf;
		lowerLeftCorner = Vec3(-widthHalf, -heightHalf, -1.0f);
		horizontalRange = Vec3(2 * widthHalf, 0.0f, 0.0f);
		verticalRange = Vec3(0.0f, 2 * heightHalf, 0.0f);

		origin = position;

		// opposite to what is expected, since z is facing in the screen.
		Vec3 w = (position - lookAt).normalize();
		Vec3 u = (cross(worldUp, w)).normalize();
		Vec3 v = cross(w, u);

		lowerLeftCorner = origin - widthHalf *  u - heightHalf * v - w * focusDistance;
		horizontalRange = 2 * widthHalf * u * focusDistance;
		verticalRange = 2 * heightHalf * v * focusDistance;
	}

	Ray Camera::getRay(float u, float v)
	{
		Vec3 random = lensRadius * Utils::getInstance().getRandomPointInUnitSphere();
		Vec3 offset = u * random.getX() + v *random.getY();
		return Ray(origin + offset, lowerLeftCorner + u * horizontalRange + v * verticalRange - origin - offset);
	}
}