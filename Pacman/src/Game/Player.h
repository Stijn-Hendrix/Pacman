#pragma once

#include <Renderer/Texture.h>
#include <glm/glm.hpp>

namespace Pacman {

	class Player
	{
	public:
		Player();

		void OnUpdate(float ts);
		void OnDraw();

	private:

		glm::vec3 m_Position = { 0,0,0 };

		std::shared_ptr<Texture> m_PacmanTexture;
	};

}