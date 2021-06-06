#include "QbertPCH.h"
#include "QuitCommand.h"

void Qbert::QuitCommand::Execute()
{
	SDL_Event sdlEvent{};
	sdlEvent.type = SDL_QUIT;

	SDL_PushEvent(&sdlEvent);
}
