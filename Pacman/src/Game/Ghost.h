#pragma once

#include "Renderer/AnimationLoop.h"
#include "Character.h"
#include <random>

namespace Pacman {

	enum class GhostState
	{
		Wander = 0,
		LeavePen
	};

	class Ghost :  public Character
	{
	public:

		Ghost(Board* board) : Character(board), m_CurrentState(GhostState::LeavePen), rng()
		{
			SetCanRotate(false);
		}

		Ghost(const AnimationLoop& animationLoop, Board* board)
			: Character(animationLoop, board), m_CurrentState(GhostState::LeavePen), rng()
		{
			m_Animation.SetSpeed(4);
			SetCanRotate(false);
		}

		void OnUpdate(float ts) override;

	private:

		void OnWander(float ts);
		void OnLeavePen(float ts);

		void FindNewDirection();

	private:

		std::mt19937 rng;

		GhostState m_CurrentState;
	};


}