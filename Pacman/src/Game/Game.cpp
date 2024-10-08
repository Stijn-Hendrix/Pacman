#include "ppch.h"
#include "Game.h"

#include "Renderer/Renderer.h"

namespace Pacman {
	
	Game::Game(uint32_t width, uint32_t height)
		: m_Board(std::make_shared<Board>()), m_Camera(width, height, {13.5f,13.5f,0})
	{
	}

	void Game::OnResizeViewport(uint32_t width, uint32_t height)
	{
	}

	void Game::OnStart()
	{
		Renderer::Init();
	}


	void Game::OnUpdate(float ts)
	{
		
		m_Board->OnUpdate(ts);
		if (m_Board->IsGameOver())
		{
			m_Board = std::make_shared<Board>();
		}
	}

	void Game::OnDraw(float ts)
	{
		Renderer::BeginScene(m_Camera);
		m_Board->OnDraw(ts);
	}

	void Game::OnEnd()
	{
		Renderer::ShutDown();
	}

}