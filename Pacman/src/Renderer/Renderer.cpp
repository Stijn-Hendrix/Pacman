#include "ppch.h"
#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"

#include <glad/glad.h>

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

		glm::vec3 QuadVertexPositions[4];
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, };

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

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec4& color)
	{
		s_Data.Shader->Bind();
		s_Data.WhiteTexture->Bind();
		FlushQuad(position, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const std::shared_ptr<Texture>& texture, const glm::vec4& color)
	{
		s_Data.Shader->Bind();
		texture->Bind();
		FlushQuad(position, color);
	}


	void Renderer::FlushQuad(const glm::vec3& position, const glm::vec4& color)
	{
		QuadVertex vertices[] = {
			{ position + s_Data.QuadVertexPositions[0], color, {0, 0} },
			{ position + s_Data.QuadVertexPositions[1], color, {1, 0} },
			{ position + s_Data.QuadVertexPositions[2], color, {1, 1} },
			{ position + s_Data.QuadVertexPositions[3], color, {0, 1} }
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