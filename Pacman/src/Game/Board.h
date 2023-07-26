#pragma once

#include "Renderer/Texture.h"
#include <glm/glm.hpp>

#include "Player.h"

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
		Board(Player* player);

		void OnUpdate(float ts);
		void OnDraw();

		bool IsWall(float x, float y)
		{
			auto& [xx, yy] = PositionToCoord(x, y);
			int index = CoordToIndex(xx, yy);
			return m_Tiles[index] & WALL;
		}

		bool IsInCenterOfTile(float x, float y)
		{
			constexpr float tolerance = 1e-2;
			auto& [a, b] = PositionToRelativeCoord(x, y);
			auto& [c, d] = PositionToCoord(x, y);
			return std::abs(a - c) < tolerance && std::abs(b - d) < tolerance;
		}

		TileType GetTile(uint32_t index)
		{
			return m_Tiles[index];
		}

		TileType GetTile(uint32_t x, uint32_t y)
		{
			return m_Tiles[CoordToIndex(x, y)];
		}


		TileType GetTileFromPos(float x, float y)
		{
			auto& [xx, yy] = PositionToCoord(x, y);
			return m_Tiles[CoordToIndex(xx, yy)];
		}

		void RemoveCoin(float x, float y)
		{
			auto& [xx, yy] = PositionToCoord(x, y);
			uint8_t index = CoordToIndex(xx, yy);
			m_Tiles[index] = m_Tiles[index] & ~COIN;
			m_CoinTileSprites[index].Occupied = false;
		}

	private:

		int32_t CoordToIndex(uint32_t x, uint32_t y)
		{
			uint32_t i = y * m_Width + x;
			if (i < 0 || i >= m_Tiles.size()) return -1;
			return i;
		}

		glm::vec3 CoordToPosition(uint32_t x, uint32_t y)
		{
			float posX = x - (m_Width / 2.0f) + 0.5f;
			float posY = y - (m_Height / 2.0f) + 0.5f;
			return { posX, posY, 0 };
		}

		std::pair<int, int> PositionToCoord(float x, float y)
		{
			int posX = std::round(x + (m_Width / 2.0f) - 0.5f);
			int posY = std::round(y + (m_Height / 2.0f) - 0.5f);
			return { posX, posY };
		}

		std::pair<float, float> PositionToRelativeCoord(float x, float y)
		{
			float posX = x + (m_Width / 2.0f) - 0.5f;
			float posY = y + (m_Height / 2.0f) - 0.5f;
			return { posX, posY };
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

		const uint16_t m_Width = 28;
		const uint16_t m_Height = 28;

		std::vector<TileType> m_Tiles;
		std::vector<TileSprite> m_WallTileSprites;
		std::vector<CoinSprite> m_CoinTileSprites;

		std::shared_ptr<Texture> m_Coin;

		Player* m_Player;

	};

}