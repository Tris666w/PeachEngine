#include "MiniginPCH.h"
#include "SoundSystems.h"
#include <iostream>

SDLMixerSoundSystem::SDLMixerSoundSystem() : SoundSystem()
{
}

SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
	
}

void SDLMixerSoundSystem::Play(const sound_id id, const float volume)
{
	std::cout<<"Playing "<<id<< " at volume "<<volume<<std::endl;
}

void MutedSoundSystem::Play(const sound_id id, const float)
{
	std::cout<<"Sound is "<< id <<std::endl;
}
