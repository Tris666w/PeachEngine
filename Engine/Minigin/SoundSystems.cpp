#include "MiniginPCH.h"
#include "SoundSystems.h"
#include <iostream>
#include <SDL_mixer.h>

SDLMixerSoundSystem::SDLMixerSoundSystem() : SoundSystem()
{

	if ( SDL_Init(SDL_INIT_AUDIO) < 0 )
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_Init: " << SDL_GetError( ) << std::endl;
		return;
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}
}

SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
	Mix_Quit();
}

void SDLMixerSoundSystem::Play(const sound_id id, const float volume)
{
	std::cout<<"Playing "<<id<< " at volume "<<volume<<std::endl;
}

void MutedSoundSystem::Play(const sound_id id, const float)
{
	std::cout<<"Sound is "<< id <<std::endl;
}
