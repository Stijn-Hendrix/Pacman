#include "ppch.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	Board::Board(Player* player) : m_Player(player)
	{
		m_Coin = Texture::Create("assets/textures/coin.png");

		//m_Tiles.resize(m_Width * m_Height);

		const unsigned char _ = static_cast<uint8_t>(~TileFlag::WALL) | static_cast<uint8_t>(TileFlag::COIN);
		const unsigned char W = static_cast<uint8_t>(TileFlag::WALL) | static_cast<uint8_t>(~TileFlag::COIN);
		const unsigned char E = static_cast<uint8_t>(~TileFlag::WALL) | static_cast<uint8_t>(~TileFlag::COIN);

		m_Tiles = {
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, W, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, W, W,
			E, E, E, E, E, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		};

		// TEMP, Prepare grid for drawing

		m_CoinTileSprites.resize(m_Width * m_Height);

		const float halfWidth = m_Width / 2.0f;
		const float halfHeight = m_Height / 2.0f;

		for (uint32_t x = 0; x < m_Width; x++)
		{
			for (uint32_t y = 0; y < m_Height; y++)
			{
				uint8_t type = m_Tiles[CoordToIndex(x, y)];
				if (type & WALL)
				{
					bool allNeighboursWall = true;

					if (CoordToIndex(x - 1, y) != -1 && m_Tiles[CoordToIndex(x - 1, y)] == _)
					{
						TileSprite tile;
						tile.Position = { x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 };
						tile.Size = { 0.1f, 0.5f };
						tile.Color = { 0.337f, 0.341f, 1.0f, 1.0f };
						m_WallTileSprites.push_back(tile);

						allNeighboursWall = false;
					}

					if (CoordToIndex(x + 1, y) != -1 && m_Tiles[CoordToIndex(x + 1, y)] == _)
					{
						TileSprite tile;
						tile.Position = { x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 };
						tile.Size = { 0.1f, 0.5f };
						tile.Color = { 0.337f, 0.341f, 1.0f, 1.0f };
						m_WallTileSprites.push_back(tile);

						allNeighboursWall = false;
					}

					if (CoordToIndex(x, y - 1) != -1 && m_Tiles[CoordToIndex(x, y - 1)] == _)
					{
						TileSprite tile;
						tile.Position = { x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 };
						tile.Size = { 0.5f ,  0.1f };
						tile.Color = { 0.337f, 0.341f, 1.0f, 1.0f };
						m_WallTileSprites.push_back(tile);

						allNeighboursWall = false;
					}

					if (CoordToIndex(x, y + 1) != -1 && m_Tiles[CoordToIndex(x, y + 1)] == _)
					{
						TileSprite tile;
						tile.Position = { x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 };
						tile.Size = { 0.5f ,  0.1f };
						tile.Color = { 0.337f, 0.341f, 1.0f, 1.0f };
						m_WallTileSprites.push_back(tile);

						allNeighboursWall = false;
					}

					if (allNeighboursWall)
					{
						TileSprite tile;
						tile.Position = { x - halfWidth + .5f, y - halfHeight + 0.5f, 0 };
						tile.Size = { 0.5f , 0.5f };
						tile.Color = { 0.337f, 0.341f, 1.0f, 1.0f };
						m_WallTileSprites.push_back(tile);
					}

					CoinSprite tile;
					tile.Occupied = false;
					tile.Position = { x - halfWidth + .5f, y - halfHeight + 0.5f, 0 };
					tile.Size = { 0.8f, 0.8f };
					tile.Color = glm::vec4(1, 1, 1, 1);
					m_CoinTileSprites[CoordToIndex(x, y)] = tile;
				}
				else if (type & COIN)
				{
					CoinSprite tile;
					tile.Occupied = true;
					tile.Position = { x - halfWidth + .5f, y - halfHeight + 0.5f, 0 };
					tile.Size = { 0.8f, 0.8f };
					tile.Color = glm::vec4(1, 1, 1, 1);
					m_CoinTileSprites[CoordToIndex(x, y)] = tile;
				}
			}
		}

		auto& startPos = PositionFromCoord(13, 7);
		startPos.x += 0.5f;

		m_Player->SetPosition(startPos);
	}

	void Board::OnUpdate(float ts)
	{

	}

	void Board::OnDraw()
	{
		for (int i = 0; i < m_WallTileSprites.size(); i++)
		{
			auto& sprite = m_WallTileSprites[i];
			Renderer::DrawQuad(sprite.Position, sprite.Size, sprite.Color);
		}

		for (int i = 0; i < m_CoinTileSprites.size(); i++)
		{
			auto& sprite = m_CoinTileSprites[i];
			if (sprite.Occupied)
				Renderer::DrawQuad(sprite.Position, sprite.Size, m_Coin, sprite.Color);
		}
	}
}