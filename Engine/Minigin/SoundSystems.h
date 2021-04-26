#pragma once
#include "ServicesBase.h"
#include <map>
#include <mutex>
#include <SDL_mixer.h>
#include <thread>
#include <queue>

class SDLMixerSoundSystem final: public SoundSystem
{
public:
	SDLMixerSoundSystem();
	~SDLMixerSoundSystem()override;

	SDLMixerSoundSystem(const SDLMixerSoundSystem& other) = delete;
	SDLMixerSoundSystem(SDLMixerSoundSystem&& other) noexcept = delete;
	SDLMixerSoundSystem& operator=(const SDLMixerSoundSystem& other) = delete;
	SDLMixerSoundSystem& operator=(SDLMixerSoundSystem&& other) noexcept = delete;
	
	SoundEffectID AddSound(const std::string& filePath) override;
	MusicID AddMusic(const std::string& filePath) override;

	void PlayMusic(const MusicID id, const int volume) override;
	void PlaySoundEffect(const SoundEffectID id, const int volume) override;

private:
	//SDL_Mixer logic data-members
	using SoundEffectPair = std::pair<SoundEffectID,Mix_Chunk*>;
	using MusicPair = std::pair<SoundEffectID,Mix_Music*>;
	
	std::map<SoundEffectID, Mix_Chunk*> m_SoundEffects = {};
	std::map<MusicID, Mix_Music*> m_Music = {};
	
	std::mutex m_Mutex{};

};

class MutedSoundSystem final: public SoundSystem
{
public:
	void PlayMusic(const SoundEffectID id, const int volume) override;
	void PlaySoundEffect(const MusicID id, const int volume) override;
};
