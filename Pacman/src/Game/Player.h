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
		Player(Board* board);

		void OnUpdate(float ts) override;

	private:

		void UpdateMovement(float ts);

	private:

		uint16_t m_CollectedCoins = 0;
	};

}