#pragma once

#include "Renderer/AnimationLoop.h"
#include "Character.h"
#include <random>

namespace Pacman {

	enum class GhostState
	{
		Wander = 0,
	};

	class Ghost :  public Character
	{
	public:

		Ghost() : Character(), rng()
		{
			SetCanRotate(false);
		}

		Ghost(const AnimationLoop& animationLoop) 
			: Character(animationLoop), m_CurrentState(GhostState::Wander), rng()
		{
			m_Animation.SetSpeed(4);
			SetCanRotate(false);
		}

		void OnUpdate(float ts, Board& board) override;

	private:

		void OnWander(float ts, Board& board);

	private:

		std::mt19937 rng;

		GhostState m_CurrentState;
	};


}