#include "PeachPCH.h"
#include "FPS.h"

#include "GameTime.h"
namespace peach
{
	void FPS::Update()
	{
		m_AmountOfPassedFrames++;

		m_PassedTime += peach::GameTime::GetInstance().GetElapsedSec();

		if (m_PassedTime > m_PassTime)
		{
			m_AverageFPS = static_cast<int>(static_cast<float>(m_AmountOfPassedFrames) / m_PassTime);
			m_AmountOfPassedFrames = 0;
			m_PassedTime = 0;
		}
	}
}
