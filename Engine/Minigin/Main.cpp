#include "PeachPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#pragma warning(push)
#pragma warning(disable:26812)
#include "SDL.h"
#include "Peach.h"
#pragma warning(pop)

int main(int, char* []) {
	peach::Minigin engine;
	engine.Run();
	return 0;
}