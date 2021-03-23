#pragma once
using sound_id = unsigned short;
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const sound_id id, const float volume) = 0;
};


class NullSoundSystem final: public SoundSystem
{
public:
	NullSoundSystem() = default;
	
	void Play(const sound_id, const float) override {};
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