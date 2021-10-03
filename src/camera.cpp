#include "camera.h"

namespace spx
{
	Camera::Camera(): origin(cameraDefaults::ORIGIN), lowerLeftCorner(cameraDefaults::LOWER_LEFT),
					  horizontalRange(cameraDefaults::HORIZONTAL), verticalRange(cameraDefaults::VERTICAL)
	{
	}

	Camera::Camera(const Vec3& origin): origin(origin), lowerLeftCorner(cameraDefaults::LOWER_LEFT),
					                    horizontalRange(cameraDefaults::HORIZONTAL), verticalRange(cameraDefaults::VERTICAL)
	{

	}

	Ray Camera::getRay(float u, float v)
	{
		return Ray(origin, lowerLeftCorner + u * horizontalRange + v * verticalRange);
	}
}