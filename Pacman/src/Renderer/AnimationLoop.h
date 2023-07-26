#pragma once

#include "SubTexture.h"

namespace Pacman {

	class AnimationLoop
	{
	public:

		AnimationLoop() = default;

		AnimationLoop(std::initializer_list<std::shared_ptr<SubTexture>> animations) 
			: m_AnimationSpeed(1), m_Animations(animations)
		{

		}

		void Update(float ts)
		{
			m_AnimationStep += ts * m_AnimationSpeed;

			float progress = (std::abs(glm::sin(m_AnimationStep)) / 2.0f) - (std::abs(glm::cos(m_AnimationStep)) / 2.0f) + 0.5f;

			m_CurrentAnimation = progress * (m_Animations.size() - 1);
		}

		void SetSpeed(float speed) { m_AnimationSpeed = speed; }

		const std::shared_ptr<SubTexture>& GetCurrentAnimation() { return m_Animations[m_CurrentAnimation]; }

	private:

		float m_AnimationSpeed;
		int8_t m_CurrentAnimation = 0;
		float m_AnimationStep = 0;
		std::vector<std::shared_ptr<SubTexture>> m_Animations;
	};

}