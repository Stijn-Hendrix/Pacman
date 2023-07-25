#include "ppch.h"
#include "Player.h"

#include "Renderer/Renderer.h"
#include "Core/Input.h"

namespace Pacman {

	Player::Player()
		: m_PacmanTexture(Texture::Create("assets/textures/pacman.png"))
	{
	}

	void Player::OnUpdate(float ts)
	{
		constexpr float moveSpeed = 3.0f;

		if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= ts * moveSpeed;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += ts * moveSpeed;
		}

		if (Input::IsKeyPressed(Key::S))
		{
			m_Position.y -= ts * moveSpeed;
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			m_Position.y += ts * moveSpeed;
		}
	}

	void Player::OnDraw()
	{
		Renderer::DrawQuad(m_Position, m_PacmanTexture);
	}

}