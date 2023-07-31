#pragma once


#include <Renderer/SubTexture.h>
#include <Renderer/AnimationLoop.h>

#include <glm/glm.hpp>


namespace Pacman {

	enum class Direction
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	class Board;
	
	class Character
	{
	public:

		Character(Board* board) : m_Board(board)
		{
			SetDirection(Direction::Left);
		}

		Character(Board* board, AnimationLoop animation) : m_Board(board), m_Animation(animation)
		{
			SetDirection(Direction::Left);
		}

		void virtual OnUpdate(float ts) = 0;
		void OnDraw(float ts);

		void SetPosition(const glm::vec2& position);

		void SetCanRotate(bool value) { m_Rotation = false; m_Angle = 0; m_Invert = false; }

		glm::vec2 GetPosition() const { return m_Position; }
		glm::vec2 GetDirection() const { return m_Direction; }

		void SetDirection(Direction direction);

	protected:

		glm::vec2 GetFromDirection(Direction direction)
		{
			switch (direction)
			{
			case Direction::Up:		return { 0.0f, 1.0f };
			case Direction::Down:	return { 0.0f, -1.0f };
			case Direction::Right:	return { 1.0f, 0.0f };
			case Direction::Left:	return { -1.0f, 0.0f };
			}
		}
		
		bool CanMoveInDirection(Direction direction);
		bool CanChangeDirection(Direction direction);

	protected:

		glm::vec2 m_Position = { 0, 0 };
		glm::vec2 m_Direction;
		Direction m_CurrentDirection;

		bool m_Rotation = true;
		float m_Angle = 0;
		bool m_Invert = true;

		Board* m_Board;

		AnimationLoop m_Animation;
	};

}