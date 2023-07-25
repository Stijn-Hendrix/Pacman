#pragma once

#include "Core/Base.h"
#include "Renderer/Texture.h"

namespace Pacman {

	class Game
	{
	public:
		void OnResizeViewport(uint32_t width, uint32_t height);

	public:
		void OnStart();
		void OnUpdate(float ts);
		void OnEnd();

	private:
		std::shared_ptr<Texture> m_PacmanTexture;
		std::shared_ptr<Texture> m_GhostTexture;
	};

}