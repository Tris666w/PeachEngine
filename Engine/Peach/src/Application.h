#pragma once
#include <iostream>
#include <string>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

struct SDL_Window;

namespace peach
{
	class Application
	{
	public:
		Application(glm::vec3 windowDimension = {640,480,0});
		virtual ~Application();

		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		void Run();

		glm::vec3 GetWindowDimensions()const;
		void SetApplicationName(const std::string& name){m_ApplicationName = name;}
	
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		glm::vec3 m_WindowDimensions;
		std::string m_ApplicationName;
	};
}

