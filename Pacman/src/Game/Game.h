#pragma once

#include "Core/Base.h"

#include "Renderer/Camera.h"
#include "Player.h"
#include "Ghost.h"
#include "Board.h"

namespace Pacman {

	class Game
	{
	public:
		Game(uint32_t width, uint32_t height);
		void OnResizeViewport(uint32_t width, uint32_t height);

	public:
		void OnStart();
		void OnUpdate(float ts);
		void OnDraw(float ts);
		void OnEnd();

	private:
		Board m_Board;
		Camera m_Camera;
	};

}