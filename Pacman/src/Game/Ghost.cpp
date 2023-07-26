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
			case Pacman::GhostState::LeavePen:
				OnLeavePen(ts, board);
				return;
		}
		
	}

	void Ghost::OnWander(float ts, Board& board)
	{
		constexpr float movementSpeed = 10.0f;

		if (IsInCenterOfTile(board))
		{
			DoCorrectPosition();

			// higher bias to continue in the current direction
			std::vector<Direction> allDirections = { 
				Utils::Previous(m_CurrentDirection), 
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
			}
		}
		else
		{
			SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
		}
		
	}

	void Ghost::OnLeavePen(float ts, Board& board)
	{
		constexpr float movementSpeed = 1.0f;

		SetDirection(Direction::Up);
		if (board.TileHasFlag(m_Position.x, m_Position.y, WALL) || !IsInCenterOfTile(board))
		{
			SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
		}
		else
		{
			m_CurrentState = GhostState::Wander;
		}
	}
}