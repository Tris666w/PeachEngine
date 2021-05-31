#include "PeachPCH.h"
#include "Application.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"

using namespace std;
using namespace std::chrono;
using namespace peach;

Application::Application(IVector2 windowDimensions)
	:m_WindowDimensions(windowDimensions)
{
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

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_WindowDimensions.x,
		m_WindowDimensions.y,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void Application::LoadGame() const
{
}

void Application::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Application::Run()
{
	Initialize();

	ResourceManager::GetInstance().Init();

	InputManager::GetInstance().Init();

	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

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

			doContinue = input.ProcessInput();
			while (lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerFrame;
			}

			sceneManager.Update();
			sceneManager.LateUpdate();

			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

IVector2 peach::Application::GetWindowDimensions() const
{
	return m_WindowDimensions;
}

