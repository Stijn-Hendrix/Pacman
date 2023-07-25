#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Pacman {

	class Renderer
	{
	public:

		static void Init();
		static void DrawQuad(const glm::vec3& position, const glm::vec4& color = glm::vec4(1,1,1,1));
		static void DrawQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		static void ShutDown();

	private:
		static void FlushQuad(const glm::vec3& position, const glm::vec4& color);

	private:
		static void InitVertexArray();
		static void InitVertexBuffer();
		static void InitIndexBuffer();
	};


}