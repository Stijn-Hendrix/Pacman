#pragma once

#include "Texture.h"
#include <glm/glm.hpp>

namespace Pacman {

	class SubTexture
	{
	public:
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

		const std::shared_ptr<Texture>& GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		// Shrink ensure there is no bleed over between tiles, by "shrinking" the tile by a given amount
		static std::shared_ptr<SubTexture> CreateFromCoords(const std::shared_ptr<Texture>& texture, const glm::vec2& coords, const glm::vec2& spriteSize, float shrink = 0.0f);

	private:
		std::shared_ptr<Texture> m_Texture;

		glm::vec2 m_TexCoords[4];
	};

}