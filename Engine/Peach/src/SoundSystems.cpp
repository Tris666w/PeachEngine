#include "PeachPCH.h"
#include "SoundSystems.h"
#include <iostream>

SDLMixerSoundSystem::SDLMixerSoundSystem() : SoundSystem()
{
	//Initialize SDL_Mixer
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDLMixerSoundSystem(), error when calling SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDLMixerSoundSystem(), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}
}

SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
	Mix_Quit();
}

MusicId SDLMixerSoundSystem::AddSound(const std::string& filePath)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	MusicId newID = GetAvailableSoundID();

	auto* newChunk = Mix_LoadWAV(filePath.c_str());
	if (!newChunk)
	{
		std::cerr << "SDLMixerSoundSystem::AddSound(), error when calling Mix_LoadWAV : " << Mix_GetError() << std::endl;
	}

	m_SoundEffects.insert(std::make_pair(newID, newChunk));
	return newID;
}

SoundId SDLMixerSoundSystem::AddMusic(const std::string& filePath)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	SoundId newID = GetAvailableMusicID();


	auto* newChunk = Mix_LoadMUS(filePath.c_str());
	if (!newChunk)
	{
		std::cerr << "SDLMixerSoundSystem::AddMusic(), error when calling Mix_LoadMUS : " << SDL_GetError() << std::endl;
	}

	m_Music.insert(std::make_pair(newID, newChunk));
	return newID;
}

void SDLMixerSoundSystem::PlayMusic(const SoundId id, const int)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_Music.find(id) == m_Music.end())
	{
		std::cerr << "SDLMixerSoundSystem::PlayMusic(), music with id: " << id << " was not found" << std::endl;
	}

	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}

	Mix_VolumeMusic(MIX_MAX_VOLUME);

	if (Mix_PlayMusic(m_Music[id], 0) == -1)
	{
		std::cerr << "SDLMixerSoundSystem::PlayMusic(), music with id " << id << " could not be played. " << Mix_GetError() << std::endl;
	}

}

void SDLMixerSoundSystem::PlaySoundEffect(const MusicId id, const int volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	if (m_SoundEffects.find(id) == m_SoundEffects.end())
	{
		std::cerr << "SDLMixerSoundSystem::PlaySoundEffect(), sound with id: " << id << " was not found" << std::endl;
	}

	Mix_VolumeChunk(m_SoundEffects[id], volume);
	Mix_PlayChannel(-1, m_SoundEffects[id], 0);

}

MusicId SDLMixerSoundSystem::GetAvailableSoundID() const
{
	bool hasFoundNewID = false;
	MusicId newID = 0;
	while (!hasFoundNewID)
	{
		if (std::find_if(m_SoundEffects.begin(), m_SoundEffects.end(),
			[&newID](const auto& pair) {
				if (pair.first == newID)
					return true;
				else
					return false;
			}) == m_SoundEffects.end())
		{
			hasFoundNewID = true;
		}
		else
			++newID;
	}
	return newID;
}


SoundId SDLMixerSoundSystem::GetAvailableMusicID() const
{
	bool hasFoundNewID = false;
	SoundId newID = 0;
	while (!hasFoundNewID)
	{
		if (std::find_if(m_Music.begin(), m_Music.end(),
			[&newID](const auto& pair) {
				if (pair.first == newID)
					return true;
				else
					return false;
			}) == m_Music.end())
		{
			hasFoundNewID = true;
		}
		else
			++newID;
	}
	return newID;
}


void MutedSoundSystem::PlayMusic(const MusicId id, const int)
{
	std::cout << "Playing music: " << id << std::endl;
}

void MutedSoundSystem::PlaySoundEffect(const SoundId id, const int)
{
	std::cout << "Playing sound effect: " << id << std::endl;

}


