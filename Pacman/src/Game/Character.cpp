#include "ppch.h"
#include "Character.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	void Character::OnDraw(float ts)
	{
		m_Animation.Update(ts);

		Renderer::DrawQuadRotated(glm::vec3(m_Position, 0), { m_Invert ? -1 : 1, 1 }, m_Angle, m_Animation.GetCurrentAnimation());
	}

	bool Character::CanMoveInDirection(Board& board, Direction direction, float ts)
	{

		auto& dir = GetFromDirection(direction);
		glm::vec2 newPosOffset = m_Position + (dir * ts) + dir;
		return !board.TileHasFlag(newPosOffset.x, newPosOffset.y, WALL);
	}

	bool Character::CanChangeDirection(Board& board, Direction direction, float ts)
	{
		auto& dir = GetFromDirection(direction);
		bool isInCenterOfTile = board.IsInCenterOfTile(m_Position.x, m_Position.y);
		glm::vec2 newPosOffset = m_Position + (dir * ts) + dir;
		return !board.TileHasFlag(newPosOffset.x, newPosOffset.y, WALL) && (isInCenterOfTile || dir == -m_Direction);
	}

	// Shifts the character position to stick to the closest tile, throws away
	// small floating points
	void Character::DoCorrectPosition()
	{
		float x = m_Position.x * 10.0f;
		float y = m_Position.y * 10.0f;

		m_Position.x = glm::round(x) / 10.0f;
		m_Position.y = glm::round(y) / 10.0f;
	}

	bool Character::IsInCenterOfTile(Board& board)
	{
		return board.IsInCenterOfTile(m_Position.x, m_Position.y);
	}
}