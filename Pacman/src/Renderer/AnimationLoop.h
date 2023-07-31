#pragma once

#include "SubTexture.h"

namespace Pacman {

	class AnimationLoop
	{
	public:

		AnimationLoop() = default;

		AnimationLoop(std::initializer_list<std::shared_ptr<SubTexture>> animations) 
			: m_CurrentAnimation(0)
		{
			m_Animations.push_back(animations);
		}

		void AddAnimation(std::initializer_list<std::shared_ptr<SubTexture>> animations)
		{
			m_Animations.push_back(animations);
		}

		void TransitionTo(uint16_t index)
		{
			m_CurrentAnimation = index;
		}

		void Update(float ts)
		{
			Animation& current = m_Animations[m_CurrentAnimation];

			m_AnimationStep += ts * current.AnimationSpeed;

			float progress = (std::abs(glm::sin(m_AnimationStep)) / 2.0f) - (std::abs(glm::cos(m_AnimationStep)) / 2.0f) + 0.5f;

			current.OnUpdate(progress);
		}

		void SetSpeed(float speed) { m_Animations[m_CurrentAnimation].AnimationSpeed = speed; }

		const std::shared_ptr<SubTexture>& GetCurrentAnimation() { 
			int a = m_CurrentAnimation;

			auto& current = m_Animations[m_CurrentAnimation];

			return current.Sprites[current.CurrentSprite];
		}

	private:

		struct Animation
		{
			float AnimationSpeed = 1.0f;
			int8_t CurrentSprite = 0;
			std::vector<std::shared_ptr<SubTexture>> Sprites;

			void OnUpdate(float progress)
			{
				CurrentSprite = progress * (Sprites.size() - 1);
			}

			Animation() = default;
			Animation(std::initializer_list<std::shared_ptr<SubTexture>>& sprites) : Sprites(sprites) {};
		};

		
		float m_AnimationStep = 0;
		uint16_t m_CurrentAnimation;
		std::vector<Animation> m_Animations;
	};

}