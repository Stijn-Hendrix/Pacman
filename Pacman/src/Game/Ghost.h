#pragma once

#include "Renderer/AnimationLoop.h"
#include "Character.h"

#include <random>

namespace Pacman {

	enum class GhostState
	{
		Wander = 0,
		Chase,
		Frightened,
	};

	class Ghost :  public Character
	{
	public:

		Ghost(AnimationLoop& animation, Board* board)
			: Character(board, animation), m_CurrentState(GhostState::Wander), rng()
		{
			animation.SetSpeed(4);

			SetCanRotate(false);
			SetRandomDirection();
		}

		void OnUpdate(float ts) override;

	private:

		void OnWander(float ts);
		void OnChase(float ts);

		void OnFrightened(float ts);
		void OnScatter(float ts);

		void FindNewDirection();
		void SetRandomDirection();

	private:

		std::mt19937 rng;

		float m_ChaseDistanceFromPlayer = 6.0f;

		GhostState m_CurrentState;
	};


}