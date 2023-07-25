#include "ppch.h"
#include "Board.h"

#include "Renderer/Renderer.h"

namespace Pacman {

// E = Empty
// W = Wall
#define _ 0
#define W 1

#define EMPTY 0
#define WALL 1


	Board::Board()
	{
		m_Coin = Texture::Create("assets/textures/coin.png");

		//m_Tiles.resize(m_Width * m_Height);

		m_Tiles = {
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, _, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, W, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, W, W,
			_, _, _, _, _, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, _, _, _, _, _,
			_, _, _, _, _, W, _, W, W, _, _, _, _, _, _, _, _, _, _, W, W, _, W, _, _, _, _, _,
			_, _, _, _, _, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, _, _, _, _, _,
			_, _, _, _, _, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, _, _, _, _, _,
			_, _, _, _, _, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, _, _, _, _, _,
			_, _, _, _, _, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, _, _, _, _, _,
			W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, W, W, W, W, _, W, W, W, W, W, _, W, W, _, W, W, W, W, W, _, W, W, W, W, _, W,
			W, _, _, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, W, _, _, _, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, W, W, _, W, W, _, W, W, _, W, W, W, W, W, W, W, W, _, W, W, _, W, W, _, W, W, W,
			W, _, _, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, W, W, _, _, _, _, _, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, W, W, W, W, W, W, W, W, W, W, _, W, W, _, W, W, W, W, W, W, W, W, W, W, _, W,
			W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W,
			W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		};
	}

	void Board::OnUpdate(float ts)
	{
	}

	void Board::OnDraw()
	{
		const float halfWidth = m_Width / 2.0f;
		const float halfHeight = m_Height / 2.0f;

		for (uint32_t x = 0; x < m_Width; x++)
		{
			for (uint32_t y = 0; y < m_Height; y++)
			{
				if (m_Tiles[CoordToIndex(x, y)] == WALL)
				{
					//Renderer::DrawQuad({ x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 }, { 1,1 }, m_Wall);
					//Renderer::DrawQuad({ x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 }, { 1, 1 }, { 0.37f, 0.12f, 1.0f, 1.0f });

					bool a = true;

					if (CoordToIndex(x - 1, y) != -1 && m_Tiles[CoordToIndex(x - 1, y)] == _)
					{
						Renderer::DrawQuad({ x - halfWidth + .5f, y - halfHeight + 0.5f, 0 }, { 0.1f, 0.5f }, { 0.337f, 0.341f, 1.0f, 1.0f });
						a = false;
					}
					if (CoordToIndex(x + 1, y) != -1 && m_Tiles[CoordToIndex(x + 1, y)] == _)
					{
						Renderer::DrawQuad({ x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 }, { 0.1f, 0.5f }, { 0.337f, 0.341f, 1.0f, 1.0f });
						a = false;
					}
					if (CoordToIndex(x, y - 1) != -1 && m_Tiles[CoordToIndex(x, y - 1)] == _)
					{
						Renderer::DrawQuad({ x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 }, { 0.5f ,  0.1f }, { 0.337f, 0.341f, 1.0f, 1.0f });
						a = false;
					}
					if (CoordToIndex(x, y + 1) != -1 && m_Tiles[CoordToIndex(x, y + 1)] == _)
					{
						Renderer::DrawQuad({ x - halfWidth + 0.5f, y - halfHeight + 0.5f, 0 }, { 0.5f ,  0.1f }, { 0.337f, 0.341f, 1.0f, 1.0f });
						a = false;
					}

					if (a)
					{
						Renderer::DrawQuad({ x - halfWidth + .5f, y - halfHeight + 0.5f, 0 }, { 0.5f , 0.5f }, { 0.337f, 0.341f, 1.0f, 1.0f });
					}
				}
				else
				{
					Renderer::DrawQuad({ x - halfWidth + .5f, y - halfHeight + 0.5f, 0 }, { 0.8f, 0.8f }, m_Coin);
				}
			}
		}
	}
}