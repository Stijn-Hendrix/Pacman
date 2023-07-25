#include "ppch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Pacman {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;

		QuadVertex(glm::vec3 position, glm::vec4 color) : Position(position), Color(color) {}
	};

	struct RendererData
	{
		uint32_t VBO;
		uint32_t VAO;
		uint32_t IBO;
		uint32_t Shader;

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
		InitShader();
	}

	void Renderer::InitShader()
	{
		int  success;
		char infoLog[512];

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec4 aColor;\n"
			"out vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"   ourColor = aColor; \n"
			"}\0";

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor; \n"
			"in vec4 ourColor; \n"
			"void main()\n"
			"{\n"
			"FragColor = ourColor;\n"
			"}\n";

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		s_Data.Shader = glCreateProgram();
		glAttachShader(s_Data.Shader, vertexShader);
		glAttachShader(s_Data.Shader, fragmentShader);
		glLinkProgram(s_Data.Shader);

		glGetProgramiv(s_Data.Shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar* infoLog;
			glGetProgramInfoLog(s_Data.Shader, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}

		glUseProgram(s_Data.Shader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
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
		QuadVertex vertices[] = {
			{position + s_Data.QuadVertexPositions[0], color},
			{position + s_Data.QuadVertexPositions[1], color},
			{position + s_Data.QuadVertexPositions[2], color},
			{position + s_Data.QuadVertexPositions[3], color},
		};


		glUseProgram(s_Data.Shader);
		glBindVertexArray(s_Data.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(QuadVertex) * 4, vertices);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::ShutDown()
	{
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteShader(s_Data.Shader);
	}
	
}