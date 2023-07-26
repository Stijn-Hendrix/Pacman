#include "ppch.h"
#include "Character.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	void Character::OnDraw(float ts)
	{
		m_Animation.Update(ts);

		Renderer::DrawQuadRotated(m_Position, { m_Invert ? -1 : 1, 1 }, m_Angle, m_Animation.GetCurrentAnimation());
	}

	bool Character::CanMoveInDirection(Board& board, Direction direction, float ts)
	{

		auto& dir = GetFromDirection(direction);
		//bool isInCenterOfTile = board.IsInCenterOfTile(m_Position.x, m_Position.y);
		glm::vec3 newPosOffset = m_Position + (dir * ts) + dir;
		return !board.IsWall(newPosOffset.x, newPosOffset.y);
	}

	bool Character::CanChangeDirection(Board& board, Direction direction, float ts)
	{
		auto& dir = GetFromDirection(direction);
		bool isInCenterOfTile = board.IsInCenterOfTile(m_Position.x, m_Position.y);
		glm::vec3 newPosOffset = m_Position + (dir * ts) + dir;
		return !board.IsWall(newPosOffset.x, newPosOffset.y) && (isInCenterOfTile || dir == -m_Direction);
	}

	bool Character::IsInCenterOfTile(Board& board, Direction direction)
	{
		auto& dir = GetFromDirection(direction);
		return board.IsInCenterOfTile(m_Position.x, m_Position.y);
	}

}