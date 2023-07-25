#pragma once

namespace Pacman {

	class Game
	{
	public:
		void OnResizeViewport(uint32_t width, uint32_t height);

	public:
		void OnUpdate(float ts);

	};

}