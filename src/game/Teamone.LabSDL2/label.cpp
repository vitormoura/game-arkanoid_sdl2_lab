#include "stdafx.h"
#include "label.h"



label::label() :
	m_text("label"), 
	m_fg_color(SDL_Color{ 255,255,255,255 }), 
	m_bg_color(SDL_Color{ 0,0,0,255 }), 
	m_text_texture(nullptr), 
	m_source_rect(SDL_Rect{})
{
}

label::~label()
{
	debug_print(__FUNCTION__);

	if (m_text_texture != nullptr) {
		SDL_DestroyTexture(m_text_texture);
	}

}

void label::set_text(string text)
{
	if (m_text.compare(text) != 0) {

		if (m_text_texture != nullptr) {
			SDL_DestroyTexture(m_text_texture);
			m_text_texture = nullptr;
		}

		m_text.assign(text);
	}
}

void label::set_color(const SDL_Color & c)
{
	m_fg_color = c;

	if (m_text_texture != nullptr) {
		SDL_DestroyTexture(m_text_texture);
		m_text_texture = nullptr;
	}
}

void label::render(SDL_Renderer * canvas, SDL_Rect * dest)
{
	if (m_text_texture == nullptr) {

		auto surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_fg_color);

		if (surface != nullptr) {
			m_text_texture = SDL_CreateTextureFromSurface(canvas, surface);
			
			if (m_text_texture != nullptr) {
				SDL_QueryTexture(m_text_texture, NULL, NULL, &m_source_rect.w, &m_source_rect.h);
			}
			
			SDL_FreeSurface(surface);
		}
	} 

	SDL_RenderCopy(canvas, m_text_texture, nullptr, dest);
}

void label::render(SDL_Renderer * canvas)
{
	auto dest = this->get_bounds();
	this->render(canvas, &dest);
}

bool label::load(content_manager * cm)
{
	m_font = cm->load_font("./Assets/arial.ttf");

	return m_font != nullptr;
}

void label::update(float elapsedTime)
{
}
