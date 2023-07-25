#pragma once

#include "Core/Base.h"

#include "Renderer/Camera.h"
#include "Player.h"

namespace Pacman {

	class Game
	{
	public:
		Game(uint32_t width, uint32_t height);
		void OnResizeViewport(uint32_t width, uint32_t height);

	public:
		void OnStart();
		void OnUpdate(float ts);
		void OnEnd();

	private:
		Player m_Player;
		Camera m_Camera;
	};

}