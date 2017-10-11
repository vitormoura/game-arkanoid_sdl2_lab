#include "stdafx.h"
#include "sprite.h"

sprite::sprite(SDL_Texture * texture, int width, int height) :
	sprite::sprite(texture, SDL_Rect{ 0,0,width, height })
{
}

sprite::sprite(SDL_Texture * texture, const SDL_Rect& sourceRect) :
	m_texture(texture), m_source(sourceRect)
{
	assert(texture != nullptr);
	assert(m_source.w > 0);
	assert(m_source.h > 0);
}

void sprite::render(SDL_Renderer * canvas, SDL_Rect* dest)
{
	assert(canvas != nullptr);
	assert(dest != nullptr);

	SDL_RenderCopy(canvas, m_texture, &m_source, dest);
}

sprite::~sprite()
{
	debug_print(__FUNCTION__)
}
