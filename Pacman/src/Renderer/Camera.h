#pragma once

#include <glm/glm.hpp>

namespace Pacman {

	class Camera
	{

	public:

		Camera(uint32_t width, uint32_t height, float zoom = 13.8f);

		const glm::mat4& GetViewProjection() const { return m_ProjectionMatrix; }

	private:

		void SetProjection(float left, float right, float bottom, float top);

	private:
		glm::mat4 m_ProjectionMatrix;
	};

}