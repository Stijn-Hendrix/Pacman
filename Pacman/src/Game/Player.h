#pragma once

#include <Renderer/SubTexture.h>
#include <Renderer/AnimationLoop.h>

#include <glm/glm.hpp>

#include "Character.h"
#include <random>


namespace Pacman {

	class Board;

	class Player : public Character
	{
	public:
		Player(Board* board);

		void OnUpdate(float ts) override;
	private:

		void UpdateMovement(float ts);

	private:

		AnimationLoop m_MoveAnimation;

		uint16_t m_CollectedCoins = 0;
	};

}