#include "ppch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pacman {

	Camera::Camera(uint32_t width, uint32_t height, glm::vec3 position, float zoom)
		: m_Position(position)
	{
		float aspectRatio = (float)width / (float)height;
		SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);

		RecalculateViewMatrix();
	}

	void Camera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}