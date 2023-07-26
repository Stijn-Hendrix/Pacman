#include "ppch.h"
#include "Player.h"

#include "Renderer/Renderer.h"
#include "Core/Input.h"

#include "Board.h"

namespace Pacman {

	Player::Player()
		: Character()
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

	void Player::OnUpdate(float ts, Board& board)
	{

		if (Input::IsKeyPressed(Key::A))
		{
			if (CanChangeDirection(board, Direction::Left, ts))
			{
				SetDirection(Direction::Left);
			}
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			if (CanChangeDirection(board, Direction::Right, ts))
			{
				SetDirection(Direction::Right);
			}
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			if (CanChangeDirection(board, Direction::Down, ts))
			{
				SetDirection(Direction::Down);
			}
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			if (CanChangeDirection(board, Direction::Up, ts))
			{
				SetDirection(Direction::Up);
			}
		}

		UpdateMovement(ts, board);
	}


	void Player::UpdateMovement(float ts, Board& board)
	{
		constexpr float movementSpeed = 5.0f;

		auto& playerPosition = m_Position;
		auto& playerDirection = m_Direction;
		glm::vec2 newPos = playerPosition + (playerDirection * ts) * movementSpeed;
		glm::vec2 newPosOffset = newPos + playerDirection / 2.0f;

		if (!board.TileHasFlag(newPosOffset.x, newPosOffset.y, WALL))
		{
			SetPosition(newPos);
		}
	
		if (board.TileHasFlag(m_Position.x, m_Position.y, COIN))
		{
			board.RemoveCoin(m_Position.x, m_Position.y);
			m_CollectedCoins++;
		}
		
		DoCorrectPosition();

		LOG(m_Position.x << " " << m_Position.y);
	}
}