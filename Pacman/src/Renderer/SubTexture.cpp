#include "ppch.h"
#include "SubTexture.h"

namespace Pacman {



	SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	std::shared_ptr<SubTexture> SubTexture::CreateFromCoords(const std::shared_ptr<Texture>& texture, const glm::vec2& coords, const glm::vec2& spriteSize, float shrink)
	{
		glm::vec2 min = { (coords.x * spriteSize.x + shrink) / texture->GetWidth(), (coords.y * spriteSize.y + shrink) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + 1) * spriteSize.x - shrink) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y - shrink) / texture->GetHeight() };
		return std::make_shared<SubTexture>(texture, min, max);
	}

}