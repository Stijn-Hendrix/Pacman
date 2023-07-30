#include "ppch.h"
#include "Player.h"

#include "Renderer/Renderer.h"
#include "Core/Input.h"

#include "Board.h"

namespace Pacman {

	Player::Player(Board* board)
		: Character(board)
	{
		auto texture = Texture::Create("assets/textures/pacman.png");

		m_Animation =
		{ 
			SubTexture::CreateFromCoords(texture, { 0, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 1, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 2, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 3, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 4, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 5, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 6, 0 }, { 16,16 }),
			SubTexture::CreateFromCoords(texture, { 7, 0 }, { 16,16 })
		};
		m_Animation.SetSpeed(4);
	}

	void Player::OnUpdate(float ts)
	{

		if (Input::IsKeyPressed(Key::A))
		{
			if (CanChangeDirection(Direction::Left))
				SetDirection(Direction::Left);
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			if (CanChangeDirection(Direction::Right))
				SetDirection(Direction::Right);
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			if (CanChangeDirection(Direction::Down))
				SetDirection(Direction::Down);
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			if (CanChangeDirection(Direction::Up))
				SetDirection(Direction::Up);
		}

		UpdateMovement(ts);
	}


	void Player::UpdateMovement(float ts)
	{
		constexpr float movementSpeed = 4.0f;

		glm::vec2 forward = m_Position + m_Direction * 0.51f;

;		bool colision = m_Board->TileHasFlag(forward, WALL);

		if (!colision) {
			m_Position += m_Direction * movementSpeed * ts;

			if (m_Board->TileHasFlag(m_Position, COIN))
			{
				m_Board->RemoveCoin(m_Position);
				m_CollectedCoins++;
			}
		}
		else
		{
			auto& [x, y] = m_Board->PositionToCoord(m_Position);
			m_Position.x = x;
			m_Position.y = y;
		}
	}
}