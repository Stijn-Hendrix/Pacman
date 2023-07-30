#include "ppch.h"
#include "Character.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	void Character::OnDraw(float ts)
	{
		m_Animation.Update(ts);

		Renderer::DrawQuadRotated(glm::vec3(m_Position, 0), { m_Invert ? -1 : 1, 1 }, 
			m_Angle, m_Animation.GetCurrentAnimation());
	}

	void Character::SetPosition(const glm::vec2& position)
	{
		m_Position = position;
	}

	void Character::SetDirection(Direction direction)
	{
		m_CurrentDirection = direction;
		switch (direction)
		{
		case Direction::Up:
			m_Direction = { 0, 1 };
			if (m_Rotation)
			{
				m_Angle = 90;
				m_Invert = false;
			}
			break;
		case Direction::Down:
			m_Direction = { 0, -1 };
			if (m_Rotation)
			{
				m_Angle = -90;
				m_Invert = false;
			}
			break;
		case Direction::Right:
			m_Direction = { 1, 0 };
			if (m_Rotation)
			{
				m_Angle = 0;
				m_Invert = false;
			}
			break;
		case Direction::Left:
			m_Direction = { -1, 0 };
			if (m_Rotation)
			{
				m_Angle = 0;
				m_Invert = true;;
			}
			break;
		}
	}

	bool Character::CanMoveInDirection(Direction direction)
	{
		auto& dir = GetFromDirection(direction);
		glm::vec2 newPosOffset = m_Position + dir * 0.6f;
		return !m_Board->TileHasFlag(newPosOffset, WALL);
	}

	bool Character::CanChangeDirection(Direction direction)
	{
		auto& dir = GetFromDirection(direction);
		bool isInCenterOfTile = m_Board->IsInCenterOfTile(m_Position);
		glm::vec2 newPosOffset = m_Position + dir * 0.6f;
		return !m_Board->TileHasFlag(newPosOffset, WALL) && (isInCenterOfTile || dir == -m_Direction);
	}
}