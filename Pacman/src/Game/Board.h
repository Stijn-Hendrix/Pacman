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
		COIN = 1 << 1,
		POWERUP = 1 << 2
	};

	class Board
	{
	public:
		Board();

		void OnUpdate(float ts);
		void OnDraw(float ts);

		void RemoveCoin(const glm::vec2& position);
		void RemovePowerUp(const glm::vec2& position);

		bool GhostOnTile(const glm::vec2& position);

		bool IsInCenterOfTile(const glm::vec2& position);

		bool TileHasFlag(const glm::vec2& position, TileFlag flag);
		
		std::pair<int, int> PositionToCoord(const glm::vec2& position);

		uint8_t GetTile(uint32_t x, uint32_t y);

		const Player& GetPlayer() const { return m_Player; }
		
		bool IsPowerUpActive() { return m_PowerUpActive > 0.0f; }

		void ActivatePowerUp(float seconds) { m_PowerUpActive = seconds; }

	private:

		int32_t CoordToIndex(uint32_t x, uint32_t y);

		void RemoveFlag(const glm::vec2& position, TileFlag flag);

	private:



		struct WallSprite
		{
			glm::vec2 Position;
			glm::vec2 Size;
		};

		const uint16_t m_Width = 28;
		const uint16_t m_Height = 28;

		std::vector<TileType> m_Tiles;
		std::vector<WallSprite> m_WallTileSprites;

		std::shared_ptr<Texture> m_Coin;

		uint16_t m_RemainingCoins = 0;

		float m_PowerUpActive = 0.0f;

		Player m_Player;
		std::vector<Ghost> m_Ghosts;
	};

}