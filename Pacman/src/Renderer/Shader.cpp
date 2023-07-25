#include "ppch.h"
#include "Shader.h"

#include "Core/Base.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Pacman {

	std::shared_ptr<Shader> Shader::Create(const std::string& vertPath, const std::string& fragPath)
	{
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertPath);
            fShaderFile.open(fragPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        return std::make_unique<Shader>(vertexCode.c_str(), fragmentCode.c_str());
	}

	Shader::Shader(const char* vertSource, const char* fragSource)
	{
		int  success;
		char infoLog[512];

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			ASSERT(false, "Failed to compile vertex shader: " << infoLog);
		}

		uint32_t fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			ASSERT(false, "Failed to compile fragment shader: " << infoLog);
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);

		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}

		glUseProgram(m_RendererID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_RendererID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}



	uint32_t Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformCache.find(name) == m_UniformCache.end())
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			m_UniformCache.emplace(name, location);
		}

		return m_UniformCache[name];
	}

	void Shader::SetFloat1(const std::string& name, float value)
	{
		GLint location = GetUniformLocation(name);
		glUniform1f(location, value);
	}
	
	void Shader::SetInt1(const std::string& name, int value)
	{
		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}