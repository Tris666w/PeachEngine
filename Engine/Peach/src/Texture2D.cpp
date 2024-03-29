#include "PeachPCH.h"
#include "Texture2D.h"
#include <SDL.h>

peach::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* peach::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

peach::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
