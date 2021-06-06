#pragma once
#include <iostream>
#include <string>

#include <glm/vec2.hpp>

struct SDL_Window;

namespace peach
{
	class Application
	{
	public:
		Application();
		Application(glm::vec2 windowDimension);
		virtual ~Application();

		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		void Run();

		static glm::vec2 GetWindowDimensions();
		void SetApplicationName(const std::string& name) { m_ApplicationName = name; }

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		inline static glm::vec2 m_WindowDimensions = { 640,480 };
		std::string m_ApplicationName;
	};
}

