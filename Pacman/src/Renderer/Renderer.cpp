#include "ppch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

namespace Pacman {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

		QuadVertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord)
			: Position(position), Color(color), TexCoord(texCoord){}
	};

	struct RendererData
	{
		uint32_t VBO;
		uint32_t VAO;
		uint32_t IBO;
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture> WhiteTexture;

		glm::vec4 QuadVertexPositions[4];
	};

	static RendererData s_Data;

	void Renderer::BeginScene(const Camera& camera)
	{
		glm::mat4 viewProj = camera.GetViewProjection();

		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", viewProj);
	}

	void Renderer::Init()
	{
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		InitVertexArray();
		InitVertexBuffer();
		InitIndexBuffer();

		s_Data.Shader = Shader::Create("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

		s_Data.WhiteTexture = Texture::Create("assets/textures/white.png");
	}

	void Renderer::InitVertexBuffer()
	{
		glGenBuffers(1, &s_Data.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertex) * 4, nullptr, GL_DYNAMIC_DRAW);


		int stride = sizeof(QuadVertex);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void Renderer::InitIndexBuffer()
	{
		unsigned int indices[] = { 
			0, 1, 2,   // first triangle
			2, 3, 0    // second triangle
		};

		glGenBuffers(1, &s_Data.IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void Renderer::InitVertexArray()
	{
		glGenVertexArrays(1, &s_Data.VAO);
		glBindVertexArray(s_Data.VAO);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data.Shader->Bind();
		s_Data.WhiteTexture->Bind();

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		FlushQuad(position, size, color, textureCoords);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, const glm::vec4& color)
	{
		s_Data.Shader->Bind();
		texture->Bind();

		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		FlushQuad(position, size, color, textureCoords);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<SubTexture>& subTexture, const glm::vec4& color)
	{
		s_Data.Shader->Bind();

		auto& texture = subTexture->GetTexture();
		const glm::vec2* textureCoords = subTexture->GetTexCoords();

		texture->Bind();
		FlushQuad(position, size, color, textureCoords);
	}

	void Renderer::DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<SubTexture>& subTexture, const glm::vec4& color)
	{
		s_Data.Shader->Bind();

		auto& texture = subTexture->GetTexture();
		const glm::vec2* textureCoords = subTexture->GetTexCoords();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		texture->Bind();
		FlushQuad(transform, color, textureCoords);
	}



	void Renderer::FlushQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2 textureCoords[4])
	{
		const float halfSizeX = size.x / 2.0f;
		const float halfSizeY = size.y / 2.0f;

		QuadVertex vertices[] = {
			{ glm::vec3(position.x - halfSizeX, position.y - halfSizeY, 0), color, textureCoords[0] },
			{ glm::vec3(position.x + halfSizeX, position.y - halfSizeY, 0), color, textureCoords[1] },
			{ glm::vec3(position.x + halfSizeX, position.y + halfSizeY, 0), color, textureCoords[2] },
			{ glm::vec3(position.x - halfSizeX, position.y + halfSizeY, 0), color, textureCoords[3] }
		};

		glBindVertexArray(s_Data.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(QuadVertex) * 4, vertices);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::FlushQuad(const glm::mat4& transform, const glm::vec4& color, const glm::vec2 textureCoords[4])
	{
		QuadVertex vertices[] = {
			{ transform * s_Data.QuadVertexPositions[0], color, textureCoords[0] },
			{ transform * s_Data.QuadVertexPositions[1], color, textureCoords[1] },
			{ transform * s_Data.QuadVertexPositions[2], color, textureCoords[2] },
			{ transform * s_Data.QuadVertexPositions[3], color, textureCoords[3] }
		};

		glBindVertexArray(s_Data.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(QuadVertex) * 4, vertices);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::ShutDown()
	{
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteVertexArrays(1, &s_Data.VAO);
	}

}