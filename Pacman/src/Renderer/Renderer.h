#pragma once

#include <glm/glm.hpp>

namespace Pacman {

	class Renderer
	{
	public:

		static void Init();
		static void DrawQuad(const glm::vec3& position);
		static void ShutDown();

	private:
		static void InitVertexArray();
		static void InitVertexBuffer();
		static void InitIndexBuffer();
		static void InitShader();
	};


}