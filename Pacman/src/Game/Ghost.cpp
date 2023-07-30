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

	void Ghost::OnUpdate(float ts)
	{
		switch (m_CurrentState)
		{
			case Pacman::GhostState::Wander:  
				OnWander(ts); 
				return;
			case Pacman::GhostState::LeavePen:
				OnLeavePen(ts);
				return;
		}
		
	}

	void Ghost::FindNewDirection()
	{
		std::vector<Direction> allDirections = {
				Utils::Previous(m_CurrentDirection),
				m_CurrentDirection,
				m_CurrentDirection,
				Utils::Next(m_CurrentDirection)
		};
		std::shuffle(allDirections.begin(), allDirections.end(), rng);

		for (int i = 0; i < allDirections.size(); i++)
		{
			if (CanMoveInDirection(allDirections[i]))
			{
				SetDirection(allDirections[i]);
				return;
			}
		}
		SetDirection(Utils::Opposite(m_CurrentDirection));
	}

	void Ghost::OnWander(float ts)
	{
		constexpr float movementSpeed = 3.0f;

		if (m_Board->IsInCenterOfTile(m_Position))
		{
			FindNewDirection();
			auto& [x, y] = m_Board->PositionToCoord(m_Position);
			m_Position.x = x;
			m_Position.y = y;
		}

		glm::vec2 forward = m_Position + m_Direction * 0.51f;

		bool colision = m_Board->TileHasFlag(forward, WALL);
		if (!colision)
		{
			m_Position += m_Direction * movementSpeed * ts;
		}
		else
		{
			auto& [x, y] = m_Board->PositionToCoord(m_Position);
			m_Position.x = x;
			m_Position.y = y;
		}
	}

	void Ghost::OnLeavePen(float ts)
	{
		constexpr float movementSpeed = 1.0f;

		SetDirection(Direction::Up);
		if (m_Board->TileHasFlag(m_Position, WALL) || !m_Board->IsInCenterOfTile(m_Position))
		{
			SetPosition(m_Position + (m_Direction * ts) * movementSpeed);
		}
		else
		{
			m_CurrentState = GhostState::Wander;
			SetDirection(Direction::Left);
		}
	}

	
}