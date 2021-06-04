#include "PeachPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

peach::TextureComponent::TextureComponent(const std::string& assetPath, float width, float height)
	:ComponentBase(),
	m_Dimensions(width, height,0)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(assetPath);
}

void peach::TextureComponent::Render()const
{
	if (m_Texture)
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
	m_Dimensions = { width,height ,0};
}
