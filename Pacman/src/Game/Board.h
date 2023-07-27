#pragma once

#include "Renderer/Texture.h"
#include <glm/glm.hpp>

#include "Player.h"
#include "Ghost.h"

namespace Pacman {

	using TileType = uint8_t;

	enum TileFlag
	{
		WALL = 1 << 0,
		COIN = 1 << 1
	};

	class Board
	{
	public:
		Board();

		void OnUpdate(float ts);
		void OnDraw(float ts);

		void RemoveCoin(float x, float y);

		bool IsInCenterOfTile(float x, float y);

		bool TileHasFlag(float x, float y, TileFlag flag);
		

	private:

		int32_t CoordToIndex(uint32_t x, uint32_t y)
		{
			uint32_t i = y * m_Width + x;

			if (i < 0 || i >= m_Tiles.size()) return -1;

			return i;
		}


		std::pair<int, int> PositionToCoord(float x, float y)
		{
			int posX = std::round(x);
			int posY = std::round(y);
			return { posX, posY };
		}

	private:

		struct WallSprite
		{
			glm::vec2 Position;
			glm::vec2 Size;
		};

		struct CoinSprite
		{
			bool Occupied;
			glm::vec2 Position;
			glm::vec2 Size;
		};

		const uint16_t m_Width = 28;
		const uint16_t m_Height = 28;

		std::vector<TileType> m_Tiles;
		std::vector<WallSprite> m_WallTileSprites;
		std::vector<CoinSprite> m_CoinTileSprites;

		std::shared_ptr<Texture> m_Coin;

		uint16_t m_RemainingCoins = 0;

		Player m_Player;
		std::vector<Ghost> m_Ghosts;
	};

}