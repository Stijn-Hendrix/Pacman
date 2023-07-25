#pragma once

#include "Core/Base.h"

namespace Pacman {

	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& path);
		~Texture();

		static std::shared_ptr<Texture> Create(const std::string& path)
		{
			return std::make_shared<Texture>(path);
		}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot = 0);

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
	};

}