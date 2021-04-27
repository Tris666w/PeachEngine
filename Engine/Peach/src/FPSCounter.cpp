#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "FPS.h"
#include "TextObject.h"

FPSCounter::FPSCounter(peach::TextObject* pTextObject)
	:m_pTextObject(pTextObject)
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
	m_pTextObject->SetText(std::to_string(m_pFPS->GetAverageFPS()));
}

void FPSCounter::LateUpdate()
{
}

void FPSCounter::Render()
{
}