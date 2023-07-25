#pragma once

#include <Renderer/SubTexture.h>
#include <glm/glm.hpp>

namespace Pacman {

	class Player
	{
	public:
		Player();

		void OnUpdate(float ts);
		void OnDraw();

	private:

		void UpdateAnimation(float ts);

	private:

		glm::vec3 m_Position = { 0,0,0 };

		float m_Angle = 0;
		bool m_Invert = false;

		int8_t m_CurrentAnimation = 0;
		float m_AnimationStep = 0;
		std::vector<std::shared_ptr<SubTexture>> m_PackmanAnimations;
	};

}