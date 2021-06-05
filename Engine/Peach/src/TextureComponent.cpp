#include "PeachPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

peach::TextureComponent::TextureComponent(const std::string& assetPath, float width, float height)
	:ComponentBase(),
	m_Dimensions(width, height, 0)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetPath);
}

void peach::TextureComponent::Initialize()
{
}

void peach::TextureComponent::Update()
{
}

void peach::TextureComponent::Render()const
{
	if (!m_Texture)
		return;

	if (m_SourceRectSet)
	{
		const auto& pos = GetParent()->GetpTransform()->GetPosition();
		if (m_Dimensions.x > 0 && m_Dimensions.y > 0)
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Dimensions.x, m_Dimensions.y, m_SourceRect);
		else
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_SourceRect);
	}
	else
	{
		const auto& pos = GetParent()->GetpTransform()->GetPosition();
		if (m_Dimensions.x > 0 && m_Dimensions.y > 0)
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Dimensions.x, m_Dimensions.y);
		else
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

	}


}

void peach::TextureComponent::SetTexture(const std::string& assetPath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetPath);
}

void peach::TextureComponent::SetDimensions(float width, float height)
{
	m_Dimensions = { width,height ,0 };
}

SDL_Rect peach::TextureComponent::GetTextureDimensions() const
{
	SDL_Rect dimensionRect{ 0,0 };

	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dimensionRect.w, &dimensionRect.h);

	return dimensionRect;
}

void peach::TextureComponent::SetSourceRect(SDL_Rect srcRect)
{
	m_SourceRect = srcRect;
	m_SourceRectSet = true;
}
