#include "ppch.h"
#include "Ghost.h"

#include "Renderer/Renderer.h"

#include "Board.h"


namespace Pacman {

#define ANIM_REGULAR 0
#define ANIM_FRIGHTENED 1

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

		std::vector<Direction> GetDirections()
		{
			return { 
				Direction::Up,
				Direction::Right,
				Direction::Down,
				Direction::Left 
			};
		}
	}

	void Ghost::OnUpdate(float ts)
	{
		switch (m_CurrentState)
		{
			case Pacman::GhostState::Wander:  
				OnWander(ts); 
				return;
			case Pacman::GhostState::Frightened:
				OnFrightened(ts);
				return;
			case Pacman::GhostState::Chase:
				OnChase(ts);
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

	void Ghost::SetRandomDirection()
	{
		auto directions = Utils::GetDirections();
		std::shuffle(directions.begin(), directions.end(), rng);
		SetDirection(directions[0]);
	}

	void Ghost::OnWander(float ts)
	{
		if (m_Board->IsPowerUpActive())
		{
			m_CurrentState = GhostState::Frightened;
			m_Animation.TransitionTo(ANIM_FRIGHTENED);
			return;
		}

		constexpr float movementSpeed = 3.8f;

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

		const glm::vec2& playerPosition = m_Board->GetPlayer().GetPosition();
		float distance = glm::distance(playerPosition, forward);
		if (distance <= m_ChaseDistanceFromPlayer)
		{
			m_CurrentState = GhostState::Chase;
		}
	}

	void Ghost::OnFrightened(float ts)
	{
		if (m_Board->IsPowerUpActive())
		{
			OnScatter(ts);
		}
		else
		{
			m_CurrentState = GhostState::Wander;
			m_Animation.TransitionTo(ANIM_REGULAR);
		}
	}

	void Ghost::OnScatter(float ts)
	{
		constexpr float movementSpeed = 3.8f;

		const glm::vec2& playerPosition = m_Board->GetPlayer().GetPosition();

		if (m_Board->IsInCenterOfTile(m_Position) || glm::distance(playerPosition, m_Position) <= 3.0f)
		{
			std::vector<Direction> availableDirections;

			for (auto& edir : Utils::GetDirections())
			{
				glm::vec2 dir = GetFromDirection(edir);
				glm::vec2 forward = m_Position + dir * 0.51f;

				bool colision = m_Board->TileHasFlag(forward, WALL);
				if (!colision)
				{
					availableDirections.push_back(edir);
				}
			}

			float maxDistance = -1000000;
			Direction nextDirection = m_CurrentDirection;

			for (auto& edir : availableDirections)
			{
				glm::vec2 dir = GetFromDirection(edir);
				glm::vec2 forward = m_Position + dir * 0.51f;

				if (edir == Utils::Opposite(m_CurrentDirection) && availableDirections.size() > 1)
				{
					continue;
				}

				float distance = glm::distance(playerPosition, forward);
				if (distance > maxDistance)
				{
					nextDirection = edir;
					maxDistance = distance;
				}
			}

			if (m_CurrentDirection != nextDirection)
			{
				SetDirection(nextDirection);
				auto& [x, y] = m_Board->PositionToCoord(m_Position);
				m_Position.x = x;
				m_Position.y = y;
			}
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

	void Ghost::OnChase(float ts)
	{
		if (m_Board->IsPowerUpActive())
		{
			m_CurrentState = GhostState::Frightened;
			m_Animation.TransitionTo(ANIM_FRIGHTENED);
			return;
		}

		constexpr float movementSpeed = 3.8f;

		const glm::vec2& playerPosition = m_Board->GetPlayer().GetPosition();

		float distance = glm::distance(playerPosition, m_Position);
		if (distance > m_ChaseDistanceFromPlayer)
		{
			m_CurrentState = GhostState::Wander;
		}

		Direction nextDirection = m_CurrentDirection;

		if (m_Board->IsInCenterOfTile(m_Position))
		{
			float minDistance = 1000000;

			for (auto& edir : Utils::GetDirections())
			{
				glm::vec2 dir = GetFromDirection(edir);
				glm::vec2 forward = m_Position + dir * 0.51f;

				bool colision = m_Board->TileHasFlag(forward, WALL);
				if (!colision)
				{
					float distance = glm::distance(playerPosition, forward);
					if (distance < minDistance)
					{
						nextDirection = edir;
						minDistance = distance;
					}
				}
			}
		}

		if (m_CurrentDirection != nextDirection)
		{
			SetDirection(nextDirection);
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

	
}