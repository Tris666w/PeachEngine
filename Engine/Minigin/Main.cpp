#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#pragma warning(push)
#pragma warning(disable:26812)
#include "SDL.h"
#include "Minigin.h"
#pragma warning(pop)

int main(int, char* []) {
	dae::Minigin engine;
	engine.Run();
	return 0;
}