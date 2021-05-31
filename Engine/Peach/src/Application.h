#pragma once
#include "MathStructs.h"
#include <iostream>
struct SDL_Window;

namespace peach
{
	class Application
	{
	public:
		Application(IVector2 windowDimension = {640,480});
		virtual ~Application();

		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		void Run();

		IVector2 GetWindowDimensions()const;

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		IVector2 m_WindowDimensions;

	};
}

