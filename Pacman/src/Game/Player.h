#pragma once

#include <Renderer/SubTexture.h>
#include <glm/glm.hpp>


namespace Pacman {

	class Board;

	class Player
	{
	public:
		Player();

		void OnUpdate(float ts, Board& board);
		void OnDraw();

		void SetPosition(const glm::vec3& position) { m_Position = position; }

		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetDirection() const { return m_Direction; }

	private:

		void UpdateAnimation(float ts);
		void UpdateMovement(float ts, Board& board);

		bool CanMoveInDirection(Board& board, const glm::vec3& direction, float ts);

	private:

		glm::vec3 m_Direction = { -1, 0, 0 };

		glm::vec3 m_Position = { 0, 0, 0 };

		float m_Angle = 0;
		bool m_Invert = true;

		int8_t m_CurrentAnimation = 0;
		float m_AnimationStep = 0;
		std::vector<std::shared_ptr<SubTexture>> m_PackmanAnimations;
	};

}