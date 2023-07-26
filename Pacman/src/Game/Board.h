#pragma once

#include "Renderer/Texture.h"
#include <glm/glm.hpp>

namespace Pacman {

	class Board
	{
	public:
		Board();

		void OnUpdate(float ts);
		void OnDraw();

	private:

		int32_t CoordToIndex(uint32_t x, uint32_t y)
		{
			uint32_t i = (m_Height - 1 - y) * m_Width + x;
			if (i < 0 || i >= m_Tiles.size()) return -1;
			return i;
		}

	private:

		struct TileSprite
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 Size;
		};

		struct CoinSprite
		{
			bool Occupied;
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 Size;
		};

		uint16_t m_Width = 28;
		uint16_t m_Height = 28;

		std::vector<uint8_t> m_Tiles;
		std::vector<TileSprite> m_WallTileSprites;
		std::vector<CoinSprite> m_CoinTileSprites;

		std::shared_ptr<Texture> m_Coin;

	};

}