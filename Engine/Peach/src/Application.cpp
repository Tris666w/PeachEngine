#include "PeachPCH.h"
#include "Application.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "Logger.h"
#include <SDL.h>
#include <SDL_image.h>

#include "CollisionManager.h"
#include "Texture2D.h"

using namespace std;
using namespace std::chrono;
using namespace peach;


Application::Application()
	:m_ApplicationName()
{
}

Application::Application(glm::vec2 windowDimensions)
	: m_ApplicationName()
{
	m_WindowDimensions = windowDimensions;

}

Application::~Application()
{
}

void Application::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	std::string windowText = "Peach Engine: ";
	windowText.append(m_ApplicationName);

	m_Window = SDL_CreateWindow(
		windowText.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		static_cast<int>(m_WindowDimensions.x),
		static_cast<int>(m_WindowDimensions.y),
		SDL_WINDOW_OPENGL
	);


	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	//Create window icon
	ResourceManager::GetInstance().Init();
	auto const pSurface = IMG_Load("Resources/Images/Engine_icon.png");
	SDL_SetWindowIcon(m_Window, pSurface);
}

void Application::LoadGame() const
{
}

void Application::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Logger::Release();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Application::Run()
{
	Initialize();

	Logger::Initialize();
	LoadGame();
	{

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& collisionManager = CollisionManager::GetInstance();

		sceneManager.Initialize();
		sceneManager.PostInitialize();
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.f;

		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float const elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();

			GameTime::GetInstance().SetElapsedSec(elapsedSec);

			lastTime = currentTime;
			lag += elapsedSec;

			while (lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerFrame;
			}

			doContinue = sceneManager.Update();

			collisionManager.CheckCollisions();

			sceneManager.LateUpdate();

			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

glm::vec2 peach::Application::GetWindowDimensions()
{
	return m_WindowDimensions;
}

