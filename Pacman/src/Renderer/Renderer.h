#pragma once

#include <glm/glm.hpp>

#include "Texture.h"
#include "SubTexture.h"
#include "Shader.h"
#include "Camera.h"

namespace Pacman {

	class Renderer
	{
	public:

		static void BeginScene(const Camera& camera);

		static void Init();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1,1,1,1));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture>& subTexture, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture>& subTexture, const glm::vec4& color = glm::vec4(1, 1, 1, 1));
		static void ShutDown();

	private:
		static void FlushQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2 textureCoords[4]);
		static void FlushQuad(const glm::mat4& transform, const glm::vec4& color, const glm::vec2 textureCoords[4]);

	private:
		static void InitVertexArray();
		static void InitVertexBuffer();
		static void InitIndexBuffer();
	};


}