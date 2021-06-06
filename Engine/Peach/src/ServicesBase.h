#pragma once
using MusicId = unsigned short;
using SoundId = unsigned short;

class SoundSystem
{
public:

	virtual ~SoundSystem() = default;

	virtual MusicId AddSound(const std::string& filePath) = 0;
	virtual SoundId AddMusic(const std::string& filePath) = 0;

	virtual void PlayMusic(const MusicId id, const int volume = 10) = 0;
	virtual void PlaySoundEffect(const SoundId id, const int volume = 10) = 0;
};


class NullSoundSystem final : public SoundSystem
{
public:
	NullSoundSystem() = default;

	MusicId AddSound(const std::string&) override { return static_cast<MusicId>(-1); }
	SoundId AddMusic(const std::string&) override { return static_cast<SoundId>(-1); }
	virtual void PlayMusic(const MusicId, const int) override {}
	virtual void PlaySoundEffect(const SoundId, const int) override {}
};

class ServiceLocator final
{
	static SoundSystem* m_SsInstance;
	static NullSoundSystem m_SsDefault;
public:
	static SoundSystem*& GetSoundSystem() { return m_SsInstance; };
	static void RegisterSoundSystem(SoundSystem* ss)
	{
		m_SsInstance = ss;
	};
};

inline NullSoundSystem ServiceLocator::m_SsDefault;
inline SoundSystem* ServiceLocator::m_SsInstance = &m_SsDefault;