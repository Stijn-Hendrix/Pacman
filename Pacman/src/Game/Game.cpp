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


		m_PacmanTexture = Texture::Create("assets/textures/pacman.png");
		m_GhostTexture = Texture::Create("assets/textures/red-ghost.png");
	}


	void Game::OnUpdate(float ts)
	{
		Renderer::BeginScene(m_Camera);

		Renderer::DrawQuad(glm::vec3(0));
		Renderer::DrawQuad(glm::vec3(0.5f,0,0), m_PacmanTexture);
		Renderer::DrawQuad(glm::vec3(-0.5f,0,0), m_GhostTexture);
	}

	void Game::OnEnd()
	{
		Renderer::ShutDown();
	}

}