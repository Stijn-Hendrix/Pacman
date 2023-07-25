#include "ppch.h"

#include "Window.h"

#include "Base.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pacman {

	void Window::Init(const std::string& name, uint32_t width, uint32_t heigth)
	{
		glfwInit();

		m_Window = glfwCreateWindow(width, heigth, name.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			ASSERT(false, "Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwSetWindowSizeLimits(m_Window, width, heigth, width, heigth);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(status, "Failed to initialize Glad!");

		m_Width = width;
		m_Height = heigth;

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

			instance->m_Width = width;
			instance->m_Height = height;

			glViewport(0, 0, width, height);
			if (instance->m_ResizeCallback)
			{
				instance->m_ResizeCallback(width, height);
			}
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (instance->m_CloseCallback)
			{
				instance->m_CloseCallback();
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (instance->m_ScrollCallback)
			{
				instance->m_ScrollCallback(xoffset, yoffset);
			}
		});

		SetVsync(true);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SetVsync(bool value)
	{
		glfwSwapInterval(value ? 1 : 0);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Shutdown()
	{
		glfwTerminate();
	}

}