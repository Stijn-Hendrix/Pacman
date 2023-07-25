#pragma once

#include "Core/Base.h"

namespace Pacman {

	class Shader
	{
	public:

		Shader(const char* vertSource, const char* fragSource);
		~Shader();

		static std::shared_ptr<Shader> Create(const std::string& vertPath, const std::string& fragPath);

	public:
		void Bind();

		void SetUnifromFloat1(const std::string& name, float value);
		void SetUniform1i(const std::string& name, int value);

	private:
		uint32_t GetUniformLocation(const std::string& name);

	private:

		std::unordered_map<std::string, uint32_t> m_UniformCache;

		uint32_t m_RendererID;
	};


}