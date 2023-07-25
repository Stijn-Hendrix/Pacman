#include "ppch.h"
#include "Input.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Pacman {

	bool Input::IsKeyPressed(KeyCode keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

}