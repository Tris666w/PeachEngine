#pragma once
#include "ServicesBase.h"

class SDLMixerSoundSystem final: public SoundSystem
{
public:
	SDLMixerSoundSystem();
	~SDLMixerSoundSystem()override;
	void Play(sound_id id, float volume) override;
	
};

class MutedSoundSystem final: public SoundSystem
{
public:
	void Play(sound_id id, float volume) override;
};
