#include "QbertPCH.h"

#include "FPSCounter.h"
#include "FPS.h"
#include "TextComponent.h"
namespace peach
{
	FPSCounter::FPSCounter(peach::TextComponent* pTextComp)
		:m_pTextComp(pTextComp)
		, m_pFPS(new FPS())
	{
	}

	FPSCounter::~FPSCounter()
	{
		delete m_pFPS;
		m_pFPS = nullptr;
	}

	void FPSCounter::Initialize()
	{
	}

	void FPSCounter::FixedUpdate()
	{
	}

	void FPSCounter::Update()
	{
		m_pFPS->Update();
		m_pTextComp->SetText(std::to_string(m_pFPS->GetAverageFPS()));
	}

	void FPSCounter::LateUpdate()
	{
	}

	void FPSCounter::Render()const
	{
	}
}