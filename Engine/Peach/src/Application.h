#pragma once
#include "Core.h"
namespace peach
{
	class PEACH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();

}

