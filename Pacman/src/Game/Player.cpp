#include "ppch.h"
#include "Player.h"

#include "Renderer/Renderer.h"
#include "Core/Input.h"

namespace Pacman {

	Player::Player()
	{
		auto texture = Texture::Create("assets/textures/pacman.png");
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 0, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 1, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 2, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 3, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 4, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 5, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 6, 0 }, { 16,16 }));
		m_PackmanAnimations.push_back(SubTexture::CreateFromCoords(texture, { 7, 0 }, { 16,16 }));

		m_CurrentAnimation = 0;
	}

	void Player::OnUpdate(float ts)
	{
		constexpr float moveSpeed = 3.0f;

		if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= ts * moveSpeed;
			m_Angle = 0;
			m_Invert = true;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += ts * moveSpeed;
			m_Angle = 0;
			m_Invert = false;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_Position.y -= ts * moveSpeed;
			m_Angle = -90;
			m_Invert = false;
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			m_Position.y += ts * moveSpeed;
			m_Angle = 90;
			m_Invert = false;
		}

		UpdateAnimation(ts);
	}

	void Player::OnDraw()
	{
		Renderer::DrawQuadRotated(m_Position, { m_Invert ? -1 : 1, 1 }, m_Angle, m_PackmanAnimations[m_CurrentAnimation]);
	}

	void Player::UpdateAnimation(float ts)
	{
		m_AnimationStep += ts * 5;
		m_CurrentAnimation = std::round(std::abs(glm::sin(m_AnimationStep)) * (m_PackmanAnimations.size() - 1));
	}

}