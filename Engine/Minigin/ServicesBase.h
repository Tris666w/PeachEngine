#pragma once
using SoundEffectID =  unsigned short;
using MusicID =  unsigned short;

class SoundSystem
{
public:
	
	virtual ~SoundSystem() = default;

	virtual SoundEffectID AddSound(const std::string& filePath) = 0;
	virtual MusicID AddMusic(const std::string& filePath) = 0;
	
	virtual void PlayMusic(const SoundEffectID id, const int volume) = 0;
	virtual void PlaySoundEffect(const MusicID id, const int volume) = 0;
};


class NullSoundSystem final: public SoundSystem
{
public:
	NullSoundSystem() = default;
	
	SoundEffectID AddSound(const std::string& ) override { return static_cast<SoundEffectID>(-1);}
	MusicID AddMusic(const std::string& ) override {return static_cast<MusicID>(-1);}
	virtual void PlayMusic(const SoundEffectID , const int ) override {}
	virtual void PlaySoundEffect(const MusicID , const int ) override{}
};

class ServiceLocator final
{
	static SoundSystem* m_SsInstance;
	static NullSoundSystem m_SsDefault;
public:
	static SoundSystem& GetSoundSystem() {return *m_SsInstance;};
	static void RegisterSoundSystem(SoundSystem* ss)
	{
		m_SsInstance = ss;
	};
};

inline NullSoundSystem ServiceLocator::m_SsDefault;
inline SoundSystem* ServiceLocator::m_SsInstance = &m_SsDefault;