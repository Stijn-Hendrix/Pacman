#pragma once

#include "Renderer/AnimationLoop.h"
#include "Character.h"

#include <random>

namespace Pacman {

	enum class GhostState
	{
		Wander = 0,
		Scatter
	};

	class Ghost :  public Character
	{
	public:

		Ghost(Board* board) : Character(board), m_CurrentState(GhostState::Wander), rng()
		{
			SetCanRotate(false);
			SetRandomDirection();
		}

		Ghost(const AnimationLoop& animationLoop, Board* board)
			: Character(animationLoop, board), m_CurrentState(GhostState::Wander), rng()
		{
			m_Animation.SetSpeed(4);
			SetCanRotate(false);
			SetRandomDirection();
		}

		void OnUpdate(float ts) override;

	private:

		void OnWander(float ts);
		void OnScatter(float ts);
		void FindNewDirection();

		void SetRandomDirection();

	private:

		std::mt19937 rng;

		float m_ScatterDistanceFromPlayer = 5.0f;

		GhostState m_CurrentState;
	};


}