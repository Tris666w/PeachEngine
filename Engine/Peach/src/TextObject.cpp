#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ComponentBase.h"

#pragma warning (disable: 4100)

peach::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr)
{ }

peach::TextObject::~TextObject()
{
	for (ComponentBase* pComponentBase : m_pComponents)
	{
		delete pComponentBase;
		pComponentBase = nullptr;
	}
}

void peach::TextObject::AddComponent(ComponentBase* newComponent)
{
	if (newComponent)
		m_pComponents.push_back(newComponent);
}

void peach::TextObject::Initialize()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Initialize();
	}
}

void peach::TextObject::FixedUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void peach::TextObject::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}

	for (ComponentBase* element : m_pComponents)
	{
		element->Update();
	}
}

void peach::TextObject::LateUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->LateUpdate();
	}
}

void peach::TextObject::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	for (ComponentBase* element : m_pComponents)
	{
		element->Render();
	}
}

// This implementation uses the "dirty flag" pattern
void peach::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void peach::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}