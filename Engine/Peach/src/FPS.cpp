#include "PeachPCH.h"
#include "FPS.h"

#include "Time.h"

void FPS::Initialize()
{
}

void FPS::FixedUpdate()
{
}

void FPS::Update()
{
	m_AmountOfPassedFrames++;

	m_PassedTime += peach::Time::GetInstance().GetElapsedSec();

	if (m_PassedTime > m_PassTime)
	{
		m_AverageFPS = static_cast<int>(static_cast<float>(m_AmountOfPassedFrames) / m_PassTime);
		m_AmountOfPassedFrames = 0;
		m_PassedTime = 0;
	}
}

void FPS::LateUpdate()
{
}

void FPS::Render()
{
}