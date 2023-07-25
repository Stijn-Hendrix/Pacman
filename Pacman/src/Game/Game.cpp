#include "ppch.h"
#include "Game.h"

#include "Renderer/Renderer.h"

namespace Pacman {

	void Game::OnResizeViewport(uint32_t width, uint32_t height)
	{
	}

	void Game::OnStart()
	{
		Renderer::Init();
	}


	void Game::OnUpdate(float ts)
	{
		Renderer::DrawQuad(glm::vec3(0), {1,1,1,1});
	}

	void Game::OnEnd()
	{
		Renderer::ShutDown();
	}

}