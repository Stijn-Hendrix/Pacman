#pragma once

#include <Renderer/SubTexture.h>
#include <Renderer/AnimationLoop.h>

#include <glm/glm.hpp>

#include "Character.h"


namespace Pacman {

	class Board;

	class Player : public Character
	{
	public:
		Player();

		void OnUpdate(float ts, Board& board) override;

	private:

		void UpdateMovement(float ts, Board& board);

	private:

		uint16_t m_CollectedCoins = 0;
	};

}