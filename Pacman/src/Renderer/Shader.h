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

		void SetFloat(const std::string& name, float value);

	private:
		uint32_t GetUniformLocation(const std::string& name);

	private:

		std::unordered_map<std::string, uint32_t> m_UniformCache;

		uint32_t m_RendererID;
	};


}