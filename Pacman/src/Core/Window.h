#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace Pacman {

	class Window
	{
	public:
		Window() = default;

		using ResizeEventCallbackFn = std::function<void(uint32_t, uint32_t)>;
		using CloseEventCallbackFn = std::function<void()>;
		using ScrollEventCallbackFn = std::function<void(double, double)>;

		void SetResizeEventCallback(const ResizeEventCallbackFn& callback) { m_ResizeCallback = callback; }
		void SetCloseEventCallback(const CloseEventCallbackFn& callback) { m_CloseCallback = callback; }
		void SetScrollEventCallback(const ScrollEventCallbackFn& callback) { m_ScrollCallback = callback; }

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		void Init(const std::string& name, uint32_t width, uint32_t heigth);
		void Update();
		void Shutdown();

		void SetVsync(bool value);

		GLFWwindow* GetNativeWindow() const { return m_Window; }

	private:
		GLFWwindow* m_Window;

		uint32_t m_Width;
		uint32_t m_Height;

		ResizeEventCallbackFn m_ResizeCallback;
		CloseEventCallbackFn m_CloseCallback;
		ScrollEventCallbackFn m_ScrollCallback;

	};

}