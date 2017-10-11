#include "stdafx.h"
#include "spritesheet.h"


spritesheet::spritesheet(SDL_Texture * texture, int width, int height, int frame_width, int frame_height)
	: sprite::sprite(texture, width, height), m_frame_height(frame_height), m_frame_width(frame_width)
{
	assert(frame_width > 0);
	assert(frame_height > 0);

	m_qtd_rows = height / frame_height;
	m_qtd_cols = width / frame_width;
}

int spritesheet::render_frame(SDL_Renderer * canvas, const SDL_Rect* dest, int row, int col)
{
	assert(row >= 0 && row < m_qtd_rows);
	assert(col >= 0 && col < m_qtd_cols);

	auto sourceR = SDL_Rect{ col * m_frame_width, row * m_frame_height, m_frame_width, m_frame_height };

	return SDL_RenderCopy(canvas, m_texture, &sourceR, dest);
}

spritesheet::~spritesheet()
{
	debug_print(__FUNCTION__)
}


