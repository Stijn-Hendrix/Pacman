#pragma once

#include "ppch.h"

#include "Window.h"
#include "Game/Game.h"

namespace Pacman {

	class Application
	{
	public:
		Application(const std::string& name = "Pacman", uint32_t width = 800, uint32_t height = 800);
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Game> m_Game;

		bool m_Running = true;
		float m_FrameLastTime = 0;

	private:
		static Application* s_Instance;
	};

}