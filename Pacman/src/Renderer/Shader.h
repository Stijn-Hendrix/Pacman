#pragma once

#include "Core/Base.h"

#include <glm/glm.hpp>

namespace Pacman {

	class Shader
	{
	public:

		Shader(const char* vertSource, const char* fragSource);
		~Shader();

		static std::shared_ptr<Shader> Create(const std::string& vertPath, const std::string& fragPath);

	public:
		void Bind();

		void SetFloat1(const std::string& name, float value);
		void SetInt1(const std::string& name, int value);
		void SetMat4(const std::string& name, const glm::mat4& value);

	private:
		uint32_t GetUniformLocation(const std::string& name);

	private:

		std::unordered_map<std::string, uint32_t> m_UniformCache;

		uint32_t m_RendererID;
	};


}