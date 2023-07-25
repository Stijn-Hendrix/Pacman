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

	glm::vec3 test = { 0,0,0 };

	void Game::OnUpdate(float ts)
	{
		test.x += ts * 0.01f;
		Renderer::DrawQuad(test);

	}

	void Game::OnEnd()
	{
		Renderer::ShutDown();
	}

}