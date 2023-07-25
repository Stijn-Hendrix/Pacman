#include "ppch.h"
#include "Game.h"

#include "Renderer/Renderer.h"

namespace Pacman {
	
	Game::Game(uint32_t width, uint32_t height)
		: m_Camera(width, height)
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
		m_Board.OnUpdate(ts);
		m_Player.OnUpdate(ts);


		Renderer::BeginScene(m_Camera);
		m_Board.OnDraw();
		m_Player.OnDraw();
	}

	void Game::OnEnd()
	{
		Renderer::ShutDown();
	}

}