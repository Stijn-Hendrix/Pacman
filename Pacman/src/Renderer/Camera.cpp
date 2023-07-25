#include "ppch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pacman {

	Camera::Camera(uint32_t width, uint32_t height, float zoom)
	{
		float aspectRatio = (float)width / (float)height;
		SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

}