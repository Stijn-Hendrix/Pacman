#include "ppch.h"
#include "Player.h"

#include "Renderer/Renderer.h"
#include "Core/Input.h"

#include "Board.h"

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

	void Player::OnUpdate(float ts, Board& board)
	{

		if (Input::IsKeyPressed(Key::A))
		{
			if (CanMoveInDirection(board, { -1, 0, 0 }, ts))
			{
				m_Direction = { -1, 0, 0 };
				m_Angle = 0;
				m_Invert = true;
			}
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			if (CanMoveInDirection(board, { 1, 0, 0 }, ts))
			{
				m_Direction = { 1, 0, 0 };
				m_Angle = 0;
				m_Invert = false;
			}
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			if (CanMoveInDirection(board, { 0, -1, 0 }, ts))
			{
				m_Direction = { 0, -1, 0 };
				m_Angle = -90;
				m_Invert = false;
			}
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			if (CanMoveInDirection(board, { 0, 1, 0 }, ts))
			{
				m_Direction = { 0, 1, 0 };
				m_Angle = 90;
				m_Invert = false;
			}
		}

		UpdateMovement(ts, board);
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

	void Player::UpdateMovement(float ts, Board& board)
	{
		constexpr float movementSpeed = 2.0f;

		auto& playerPosition = m_Position;
		auto& playerDirection = m_Direction;
		glm::vec3 newPos = playerPosition + (playerDirection * ts) * movementSpeed;
		glm::vec3 newPosOffset = newPos + playerDirection / 2.0f;


		uint8_t nextTile = board.GetTileFromPos(newPosOffset.x, newPosOffset.y);
		if ((nextTile & WALL) == 0)
		{
			SetPosition(newPos);
		}

		uint8_t currentTile = board.GetTileFromPos(m_Position.x, m_Position.y);
		if (currentTile & COIN)
		{
			board.RemoveCoin(m_Position.x, m_Position.y);
		}
	}

	bool Player::CanMoveInDirection(Board& board, const glm::vec3& direction, float ts)
	{
		bool isInCenterOfTile = board.IsInCenterOfTile(m_Position.x, m_Position.y);

		if (direction == -m_Direction)
		{
			isInCenterOfTile = true; // Ignore if the player is in the center of a tile
		}

		glm::vec3 newPosOffset = m_Position + (direction * ts) + direction;
		return !board.IsWall(newPosOffset.x, newPosOffset.y) && isInCenterOfTile;
	}

}