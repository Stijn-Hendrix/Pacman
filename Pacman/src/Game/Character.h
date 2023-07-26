#pragma once


#include <Renderer/SubTexture.h>
#include <Renderer/AnimationLoop.h>

#include <glm/glm.hpp>

namespace Pacman {

	class Board;

	enum class Direction
	{
		Up = 0,
		Right,
		Down,
		Left
	};


	

	class Character
	{
	public:
		Character()
		{
			SetDirection(Direction::Left);
		}

		Character(const AnimationLoop& animation) : m_Animation(animation)
		{
			SetDirection(Direction::Left);
		}

		void virtual OnUpdate(float ts, Board& board) = 0;
		void OnDraw(float ts);

		void SetPosition(const glm::vec2& position) { m_Position = position; }
		void SetCanRotate(bool value) { m_Rotation = false; m_Angle = 0; m_Invert = false; }

		glm::vec2 GetPosition() const { return m_Position; }
		glm::vec2 GetDirection() const { return m_Direction; }

		void SetDirection(Direction direction)
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

		glm::vec2 GetFromDirection(Direction direction)
		{
			switch (direction)
			{
			case Direction::Up:
				return { 0, 1 };
			case Direction::Down:
				return { 0, -1 };
				break;
			case Direction::Right:
				return { 1, 0 };
			case Direction::Left:
				return { -1, 0 };
			}
		}

	protected:
		
		bool CanMoveInDirection(Board& board, Direction direction, float ts);
		bool CanChangeDirection(Board& board, Direction direction, float ts);
		bool IsInCenterOfTile(Board& board);

		void DoCorrectPosition();

	protected:

		glm::vec2 m_Position = { 0, 0 };
		glm::vec2 m_Direction;
		Direction m_CurrentDirection;

		bool m_Rotation = true;
		float m_Angle = 0;
		bool m_Invert = true;

		AnimationLoop m_Animation;
	};

}