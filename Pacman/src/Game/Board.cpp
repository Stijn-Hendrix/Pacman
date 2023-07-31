#include "ppch.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	Board::Board() 
		: m_Player(this)
	{
		m_Coin = Texture::Create("assets/textures/coin.png");

		const unsigned char _ = static_cast<uint8_t>(TileFlag::COIN);
		const unsigned char W = static_cast<uint8_t>(TileFlag::WALL);
		const unsigned char E = 0;
		const unsigned char P = static_cast<uint8_t>(TileFlag::POWERUP);

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
			W, P, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, P, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W,
			E, E, E, E, E, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, _, _, _, _, _, _, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, W, W, W, _, _, W, W, W, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, E, E, E, E, E,
			E, E, E, E, E, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, E, E, E, E, E,
			W, W, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, W, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, P, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, P, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		};


		// TEMP, Prepare grid for drawing
		m_WallTileSprites.reserve(m_Width * m_Height);

		const float halfWidth = m_Width / 2.0f;
		const float halfHeight = m_Height / 2.0f;


		for (uint32_t x = 0; x < m_Width; x++)
		{
			for (uint32_t y = 0; y < m_Height; y++)
			{
				uint8_t type = GetTile(x, y);
				if (type & WALL)
				{

					if (
						CoordToIndex(x - 1, y) != -1 && 
						(m_Tiles[CoordToIndex(x - 1, y)] == _ ||
						m_Tiles[CoordToIndex(x - 1, y)] == P)
					)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.1f, 0.5f };
						m_WallTileSprites.push_back(tile);
					}

					if (
						CoordToIndex(x + 1, y) != -1 && 
						(m_Tiles[CoordToIndex(x + 1, y)] == _ ||
						m_Tiles[CoordToIndex(x + 1, y)] == P)
					)
					{
						WallSprite tile;
						tile.Position = { x, y};
						tile.Size = { 0.1f, 0.5f };
						m_WallTileSprites.push_back(tile);
					}

					if (
						CoordToIndex(x, y - 1) != -1 && 
						(m_Tiles[CoordToIndex(x, y - 1)] == _ ||
						m_Tiles[CoordToIndex(x, y - 1)] == P)
					)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.5f ,  0.1f };
						m_WallTileSprites.push_back(tile);
					}

					if (
						CoordToIndex(x, y + 1) != -1 && 
						(m_Tiles[CoordToIndex(x, y + 1)] == _ ||
						m_Tiles[CoordToIndex(x, y + 1)] == P)
					)
					{
						WallSprite tile;
						tile.Position = { x, y };
						tile.Size = { 0.5f ,  0.1f };
						m_WallTileSprites.push_back(tile);
					}
				}
			}
		}


		auto& playerStartPos = glm::vec2( 13, 7 );

		m_Player.SetPosition(playerStartPos);

		std::vector<glm::vec2> ghostStartPositions = {
			 glm::vec2(13, 14),
			 glm::vec2(14, 14),
			 glm::vec2(15, 14),
			 glm::vec2(14, 15),
		};

		std::vector<std::string> ghostTextures = {
			"assets/textures/redghost.png",
			"assets/textures/greenghost.png",
			"assets/textures/orangeghost.png",
			"assets/textures/blueghost.png"
		};

		auto frightened = Texture::Create("assets/textures/scaredghost.png");

		for (int i = 0; i < 4; i++)
		{
			auto texture = Texture::Create(ghostTextures[i]);

			AnimationLoop loop = {
				SubTexture::CreateFromCoords(texture, { 0, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 1, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 2, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 3, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 4, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 5, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 6, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(texture, { 7, 0 }, { 16,16 })
			};
			loop.AddAnimation({
				SubTexture::CreateFromCoords(frightened, { 0, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 1, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 2, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 3, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 4, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 5, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 6, 0 }, { 16,16 }),
					SubTexture::CreateFromCoords(frightened, { 7, 0 }, { 16,16 })
				});

			Ghost ghost = {
				loop,
				this
			};

			ghost.SetPosition(ghostStartPositions[i]);
			m_Ghosts.push_back(ghost);
		}
	}

	void Board::OnUpdate(float ts)
	{
		if (IsPowerUpActive())
		{
			m_PowerUpActive -= ts;
		}

		m_Player.OnUpdate(ts);

		for (uint8_t i = 0; i < m_Ghosts.size(); i++)
		{
			m_Ghosts[i].OnUpdate(ts);
		}

		for (auto& it = m_Ghosts.begin(); it != m_Ghosts.end();)
		{
			if (glm::distance(m_Player.GetPosition(), it->GetPosition()) < 0.5f)
			{
				if (IsPowerUpActive())
				{
					it = m_Ghosts.erase(it);
				}
				else
				{
					m_GameOver = true;
					return;
				}
			}
			else
			{
				++it;
			}
		}
	}

	void Board::OnDraw(float ts)
	{
		for (int i = 0; i < m_WallTileSprites.size(); i++)
		{
			auto& sprite = m_WallTileSprites[i];
			Renderer::DrawQuad(glm::vec3(sprite.Position, 0), sprite.Size, { 0.337f, 0.341f, 1.0f, 1.0f });
		}
		for (uint32_t i = 0; i < m_Width * m_Height; i++)
		{
			int x = i % m_Width;
			int y = i / m_Height;
			uint8_t tile = GetTile(x, y);

			if (tile & COIN)
			{
				Renderer::DrawQuad({x, y, 0}, { 0.7f, 0.7f }, m_Coin);
			}
			else if (tile & POWERUP)
			{
				Renderer::DrawQuad({x, y, 0}, { 0.85f, 0.85f }, m_Coin, glm::vec4(1,0,0,1));
			}
			
		}

		m_Player.OnDraw(ts);

		for (uint8_t i = 0; i < m_Ghosts.size(); i++)
		{
			m_Ghosts[i].OnDraw(ts);
		}
	}

	void Board::RemoveCoin(const glm::vec2& position)
	{
		RemoveFlag(position, COIN);
		m_RemainingCoins--;
	}

	void Board::RemovePowerUp(const glm::vec2& position)
	{
		RemoveFlag(position, POWERUP);
	}

	void Board::RemoveFlag(const glm::vec2& position, TileFlag flag)
	{
		auto& [xx, yy] = PositionToCoord(position);
		uint32_t index = CoordToIndex(xx, yy);

		TileType tile = m_Tiles[index];

		m_Tiles[index] = m_Tiles[index] & ~flag;
	}

	bool Board::GhostOnTile(const glm::vec2& position)
	{
		auto coord = PositionToCoord(position);

		for (Ghost& ghost : m_Ghosts)
		{
			auto ghostCoord = PositionToCoord(ghost.GetPosition());
			if (ghostCoord == coord)
			{
				return true;
			}
		}
		return false;
	}

	bool Board::IsInCenterOfTile(const glm::vec2& position)
	{
		constexpr float tolerance = 1e-2;
		auto& [c, d] = PositionToCoord(position);
		return std::abs(position.x - c) < tolerance && std::abs(position.y - d) < tolerance;
	}

	bool Board::TileHasFlag(const glm::vec2& position, TileFlag flag)
	{
		auto& [xx, yy] = PositionToCoord(position);
		return m_Tiles[CoordToIndex(xx, yy)] & flag;
	}

	std::pair<int, int> Board::PositionToCoord(const glm::vec2& position)
	{
		// (x,y) is the center of a tile. This means that we must offset by 0.5f
		// ex. (0,0) -> (-0.5f, _) is still tile 0.
		int posX = std::floor(position.x + 0.5f);
		int posY = std::floor(position.y + 0.5f);
		return { posX, posY };
	}

	uint8_t Board::GetTile(uint32_t x, uint32_t y)
	{
		return m_Tiles[CoordToIndex(x, y)];
	}

	int32_t Board::CoordToIndex(uint32_t x, uint32_t y)
	{
		uint32_t i = y * m_Width + x;

		if (i < 0 || i >= m_Tiles.size()) return -1;

		return i;
	}
}