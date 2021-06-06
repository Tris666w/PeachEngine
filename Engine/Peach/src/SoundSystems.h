#pragma once
#include "ServicesBase.h"
#include <map>
#include <mutex>
#include <SDL_mixer.h>

class SDLMixerSoundSystem final : public SoundSystem
{
public:
	SDLMixerSoundSystem();
	~SDLMixerSoundSystem()override;

	SDLMixerSoundSystem(const SDLMixerSoundSystem& other) = delete;
	SDLMixerSoundSystem(SDLMixerSoundSystem&& other) noexcept = delete;
	SDLMixerSoundSystem& operator=(const SDLMixerSoundSystem& other) = delete;
	SDLMixerSoundSystem& operator=(SDLMixerSoundSystem&& other) noexcept = delete;

	MusicId AddSound(const std::string& filePath) override;
	SoundId AddMusic(const std::string& filePath) override;

	void PlayMusic(const SoundId id, const int volume) override;
	void PlaySoundEffect(const MusicId id, const int volume) override;

private:
	//SDL_Mixer logic data-members
	using SoundEffectPair = std::pair<MusicId, Mix_Chunk*>;
	using MusicPair = std::pair<MusicId, Mix_Music*>;

	std::map<MusicId, Mix_Chunk*> m_SoundEffects = {};
	std::map<SoundId, Mix_Music*> m_Music = {};

	MusicId GetAvailableSoundID()const;
	SoundId GetAvailableMusicID() const;


	std::mutex m_Mutex{};

};

class MutedSoundSystem final : public SoundSystem
{
public:
	void PlayMusic(const MusicId id, const int volume) override;
	void PlaySoundEffect(const SoundId id, const int volume) override;
};
