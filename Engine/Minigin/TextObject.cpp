#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ComponentBase.h"

#pragma warning (disable: 4100)

dae::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr)
{ }

dae::TextObject::~TextObject()
{
	for (ComponentBase* pComponentBase : m_pComponents)
	{
		delete pComponentBase;
		pComponentBase = nullptr;
	}
}

void dae::TextObject::AddComponent(ComponentBase* newComponent)
{
	if (newComponent)
		m_pComponents.push_back(newComponent);
}

void dae::TextObject::Initialize()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->Initialize();
	}
}

void dae::TextObject::FixedUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->FixedUpdate();
	}
}

void dae::TextObject::Update()
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

void dae::TextObject::LateUpdate()
{
	for (ComponentBase* element : m_pComponents)
	{
		element->LateUpdate();
	}
}

void dae::TextObject::Render() const
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
void dae::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}