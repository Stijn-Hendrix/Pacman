#include "ppch.h"
#include "Ghost.h"

#include "Renderer/Renderer.h"

#include "Board.h"

#include <random>

namespace Pacman {

	namespace Utils {

		Direction Next(Direction direction)
		{
			if (direction == Direction::Left)
			{
				return Direction::Up;
			}
			return (Direction)((int)(direction)+1);
		}

		Direction Previous(Direction direction)
		{
			if (direction == Direction::Up)
			{
				return Direction::Left;
			}
			return (Direction)((int)(direction)-1);
		}

		Direction Opposite(Direction direction)
		{
			if (direction == Direction::Left)
			{
				return Direction::Right;
			}
			else if (direction == Direction::Down)
			{
				return Direction::Up;
			}
			return (Direction)((int)(direction)+2);
		}
	}

	void Ghost::OnUpdate(float ts, Board& board)
	{
		switch (m_CurrentState)
		{
			case Pacman::GhostState::Wander:  
				OnWander(ts, board); 
				return;
		}
		
	}

	void Ghost::OnWander(float ts, Board& board)
	{
		constexpr float movementSpeed = 3.0f;

		if (IsInCenterOfTile(board, m_CurrentDirection))
		{
			// 66% percent bias to continue in the current direction
			std::vector<Direction> allDirections = { 
				Utils::Previous(m_CurrentDirection), 
				m_CurrentDirection,
				m_CurrentDirection,
				m_CurrentDirection,
				m_CurrentDirection, 
				Utils::Next(m_CurrentDirection)
			};
			std::shuffle(allDirections.begin(), allDirections.end(), rng);

			for (int i = 0; i < allDirections.size(); i++)
			{
				if (CanMoveInDirection(board, allDirections[i], ts))
				{
					SetDirection(allDirections[i]);
					SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
					return;
				}
			}

			if (CanMoveInDirection(board, Utils::Opposite(m_CurrentDirection), ts))
			{
				SetDirection(Utils::Opposite(m_CurrentDirection));
				SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
				return;
			}
		}
		else
		{
			SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
		}
		
	}
}