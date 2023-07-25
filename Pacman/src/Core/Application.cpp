#include "ppch.h"

#include "Application.h"

namespace Pacman {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Window->Init(name, width, height);

		m_Window->SetResizeEventCallback([this](int width, int height) {
			m_Game->OnResizeViewport(width, height);
		});

		m_Window->SetCloseEventCallback([this]() {
			m_Running = false;
		});
	}

	void Application::Run()
	{
		m_Game->OnStart();

		while (m_Running)
		{
			m_Window->Clear();

			float time = (float)glfwGetTime();
			float timestep = time - m_FrameLastTime;
			m_FrameLastTime = time;

			m_Game->OnUpdate(timestep);

			m_Window->Update();
		}

		m_Game->OnEnd();
	}

}