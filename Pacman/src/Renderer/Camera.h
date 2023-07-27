#pragma once

#include <glm/glm.hpp>

namespace Pacman {

	class Camera
	{

	public:

		Camera(uint32_t width, uint32_t height, glm::vec3 position, float zoom = 13.8f);

		const glm::mat4& GetViewProjection() const { return m_ViewProjectionMatrix; }

	private:

		void SetProjection(float left, float right, float bottom, float top);

		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	};

}