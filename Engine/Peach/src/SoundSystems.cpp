#include "MiniginPCH.h"
#include "SoundSystems.h"
#include <iostream>

SDLMixerSoundSystem::SDLMixerSoundSystem() : SoundSystem()
{
	//Initialize SDL_Mixer
	if ( SDL_Init(SDL_INIT_AUDIO) < 0 )
	{
		std::cerr << "SDLMixerSoundSystem(), error when calling SDL_Init: " << SDL_GetError( ) << std::endl;
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

SoundEffectID SDLMixerSoundSystem::AddSound(const std::string& filePath)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	SoundEffectID newID { 0 };
	if (m_SoundEffects.empty())
	{
		newID = static_cast<SoundEffectID>(m_SoundEffects.size()) + 1;
	}

	auto* newChunk = Mix_LoadWAV(filePath.c_str());
	if (!newChunk)
	{
		std::cerr << "SDLMixerSoundSystem::AddSound(), error when calling Mix_LoadWAV : " << Mix_GetError( ) << std::endl;
	}

	m_SoundEffects.insert(std::make_pair(newID,newChunk));
	return newID;
}

MusicID SDLMixerSoundSystem::AddMusic(const std::string& filePath)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	MusicID newID { 0 };
	if (m_Music.empty())
	{
		newID = static_cast<MusicID>(m_SoundEffects.size()) + 1;
	}

	auto* newChunk = Mix_LoadMUS(filePath.c_str());
	if (!newChunk)
	{
		std::cerr << "SDLMixerSoundSystem::AddMusic(), error when calling Mix_LoadMUS : " << SDL_GetError( ) << std::endl;
	}

	m_Music.insert(std::make_pair(newID,newChunk));
	return newID;
}

void SDLMixerSoundSystem::PlayMusic(const MusicID id, const int )
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
		std::cerr<< "SDLMixerSoundSystem::PlayMusic(), music with id " <<id <<" could not be played. "<< Mix_GetError () <<std::endl;
	}
	
}

void SDLMixerSoundSystem::PlaySoundEffect(const SoundEffectID id, const int volume)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	
	if (m_SoundEffects.find(id) == m_SoundEffects.end())
	{
		std::cerr << "SDLMixerSoundSystem::PlaySoundEffect(), sound with id: " << id << " was not found" << std::endl;
	}
	
	Mix_VolumeChunk(m_SoundEffects[id],volume);
	Mix_PlayChannel( -1, m_SoundEffects[id], 0 );
	
}


void MutedSoundSystem::PlayMusic(const SoundEffectID id, const int)
{
	std::cout << "Playing music: "<< id << std::endl;
}

void MutedSoundSystem::PlaySoundEffect(const MusicID id, const int)
{
	std::cout << "Playing sound effect: " << id << std::endl;
	
}


