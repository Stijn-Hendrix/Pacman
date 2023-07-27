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
		m_WallTileSprites.reserve(m_Width * m_Height);

		const float halfWidth = m_Width / 2.0f;
		const float halfHeight = m_Height / 2.0f;

		for (uint32_t x = 0; x < m_Width; x++)
		{
			for (uint32_t y = 0; y < m_Height; y++)
			{
				uint8_t type = m_Tiles[CoordToIndex(x, y)];
				if (type & WALL)
				{

					if (CoordToIndex(x - 1, y) != -1 && m_Tiles[CoordToIndex(x - 1, y)] == _)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.1f, 0.5f };
						m_WallTileSprites.push_back(tile);
					}

					if (CoordToIndex(x + 1, y) != -1 && m_Tiles[CoordToIndex(x + 1, y)] == _)
					{
						WallSprite tile;
						tile.Position = { x, y};
						tile.Size = { 0.1f, 0.5f };
						m_WallTileSprites.push_back(tile);
					}

					if (CoordToIndex(x, y - 1) != -1 && m_Tiles[CoordToIndex(x, y - 1)] == _)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.5f ,  0.1f };
						m_WallTileSprites.push_back(tile);
					}

					if (CoordToIndex(x, y + 1) != -1 && m_Tiles[CoordToIndex(x, y + 1)] == _)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.5f ,  0.1f };
						m_WallTileSprites.push_back(tile);
					}
				

					CoinSprite tile;
					tile.Occupied = false;
					tile.Position = { x, y };
					tile.Size = { 0.8f, 0.8f };
					m_CoinTileSprites[CoordToIndex(x, y)] = tile;
				}
				else if (type & COIN)
				{
					CoinSprite tile;
					tile.Occupied = true;
					tile.Position = { x, y };
					tile.Size = { 0.8f, 0.8f };
					m_CoinTileSprites[CoordToIndex(x, y)] = tile;

					m_RemainingCoins++;
				}
			}
		}


		auto& playerStartPos = glm::vec2( 13, 7 );
		playerStartPos.x += 0.5f;

		m_Player.SetPosition(playerStartPos);

		std::vector<glm::vec2> ghostStartPositions = {
			 glm::vec2(13, 14),
			 glm::vec2(14, 14),
			 glm::vec2(15, 14),
			 glm::vec2(13, 13),
			 glm::vec2(14, 13)
		};

		std::vector<std::string> ghostTextures = {
			"assets/textures/redghost.png",
			"assets/textures/greenghost.png",
			"assets/textures/orangeghost.png",
			"assets/textures/yellowghost.png",
			"assets/textures/blueghost.png"
		};

		for (int i = 0; i < 1; i++)
		{
			auto texture = Texture::Create(ghostTextures[i]);

			Ghost ghost = {
				{
					SubTexture::CreateFromCoords(texture, { 0, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 1, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 2, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 3, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 4, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 5, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 6, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 7, 0 }, { 16,16 })
				}
			};

			ghost.SetPosition(ghostStartPositions[i]);
			m_Ghosts.push_back(ghost);
		}
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
			Renderer::DrawQuad(glm::vec3(sprite.Position, 0), sprite.Size, { 0.337f, 0.341f, 1.0f, 1.0f });
		}

		for (int i = 0; i < m_CoinTileSprites.size(); i++)
		{
			auto& sprite = m_CoinTileSprites[i];
			if (sprite.Occupied)
				Renderer::DrawQuad(glm::vec3(sprite.Position, 0), sprite.Size, m_Coin);
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

		//LOG("Coins remaining: " << m_RemainingCoins);
	}

	bool Board::IsInCenterOfTile(float x, float y)
	{
		constexpr float tolerance = 1e-2;
		auto& [c, d] = PositionToCoord(x, y);
		return std::abs(x - c) < tolerance && std::abs(y - d) < tolerance;
	}

	bool Board::TileHasFlag(float x, float y, TileFlag flag)
	{
		auto& [xx, yy] = PositionToCoord(x, y);
		return m_Tiles[CoordToIndex(xx, yy)] & flag;
	}
}