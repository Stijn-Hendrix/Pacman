#include "ppch.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	Board::Board() 
	{
		m_Coin = Texture::Create("assets/textures/coin.png");

		const unsigned char _ = static_cast<uint8_t>(~TileFlag::WALL) | static_cast<uint8_t>(TileFlag::COIN);
		const unsigned char W = static_cast<uint8_t>(TileFlag::WALL) | static_cast<uint8_t>(~TileFlag::COIN);
		const unsigned char E = static_cast<uint8_t>(~TileFlag::WALL) | static_cast<uint8_t>(~TileFlag::COIN);

		// Inverted along Y-Axis
		m_Tiles = {
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W,
			E, E, E, E, E, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, E, E, E, E, E,
			W, W, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, W, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
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

					m_RemainingCoins++;
				}
			}
		}


		auto& playerStartPos = CoordToPosition(13, 7);
		playerStartPos.x += 0.5f;

		m_Player.SetPosition(playerStartPos);


		auto redghostTexture = Texture::Create("assets/textures/redghost.png");

		Ghost redGhost = { 
			{
				SubTexture::CreateFromCoords(redghostTexture, { 0, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 1, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 2, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 3, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 4, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 5, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 6, 0 }, { 16,16 }),
				SubTexture::CreateFromCoords(redghostTexture, { 7, 0 }, { 16,16 }) 
			}
		};
		redGhost.SetPosition(CoordToPosition(13, 16) + glm::vec3(0.5f, 0, 0));

		auto greenghostTexture = Texture::Create("assets/textures/greenghost.png");

		Ghost greenGhost = {
		{
			SubTexture::CreateFromCoords(greenghostTexture, { 0, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 1, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 2, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 3, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 4, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 5, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 6, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(greenghostTexture, { 7, 0 }, { 16,16 })
		}
		};
		greenGhost.SetPosition(CoordToPosition(14, 16) + glm::vec3(0.5f, 0, 0));

		m_Ghosts = {
			redGhost,
			greenGhost
		};
	}

	void Board::OnUpdate(float ts)
	{
		m_Player.OnUpdate(ts, *this);

		for (uint8_t i = 0; i < m_Ghosts.size(); i++)
		{
			m_Ghosts[i].OnUpdate(ts, *this);
		}
	}

	void Board::OnDraw(float ts)
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

		m_Player.OnDraw(ts);

		for (uint8_t i = 0; i < m_Ghosts.size(); i++)
		{
			m_Ghosts[i].OnDraw(ts);
		}
	}

	void Board::RemoveCoin(float x, float y)
	{
		auto& [xx, yy] = PositionToCoord(x, y);
		uint32_t index = CoordToIndex(xx, yy);

		TileType tile = m_Tiles[index];

		m_Tiles[index] = m_Tiles[index] & ~COIN;
		m_CoinTileSprites[index].Occupied = false;
		m_RemainingCoins--;

		LOG("Coins remaining: " << m_RemainingCoins);
	}
}