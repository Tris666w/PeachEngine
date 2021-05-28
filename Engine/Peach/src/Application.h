#pragma once
struct SDL_Window;
#include <iostream>

namespace peach
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		void Run();

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}

