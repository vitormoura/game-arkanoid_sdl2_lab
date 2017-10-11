#include "stdafx.h"
#include "player.h"
#include "constantes.h"

player::player()
{
	m_static = false;
	m_position = Vector2f::Zero();
	m_enabled = true;
	m_speed = 5;
}

void player::render(SDL_Renderer * canvas, SDL_Rect* dest)
{
	m_me->render(canvas, dest);
}

void player::render(SDL_Renderer * canvas)
{
	auto dest = get_bounds();

	this->render(canvas, &dest);
}

bool player::load(content_manager * cm)
{
	auto atlas = cm->load_sprite_atlas("assets/arkanoid_atlas.xml");

	assert(atlas != nullptr);

	m_me = atlas->get_sprite("paddleBlu.png");

	return m_me != nullptr;
}

void player::update(float elapsedTime)
{
	m_position += m_direction * M * m_speed * elapsedTime;

	if (m_position.x() < m_boundaries.x) {
		m_position = Vector2f(m_boundaries.x, m_position.y());
		m_direction = Vector2f::Zero();
	}
	else if (m_position.x() + m_me->width() > (m_boundaries.x + m_boundaries.w)) {
		m_position = Vector2f((m_boundaries.x + m_boundaries.w) - m_me->width(), m_position.y());
		m_direction = Vector2f::Zero();
	}
}

void player::set_boundaries(SDL_Rect rect)
{
	m_boundaries = rect;
}

bool player::is_enabled()
{
	return game_object::is_enabled();
}

void player::on_keyevent(const SDL_KeyboardEvent & k)
{
	if (k.type == SDL_KEYDOWN) {
		
		if (k.keysym.scancode == SDL_SCANCODE_LEFT) {
			m_direction = Vector2f::UnitX() * -1;
		}
		else if (k.keysym.scancode == SDL_SCANCODE_RIGHT) {
			m_direction = Vector2f::UnitX();
		}
	}
}

player::~player()
{
	debug_print(__FUNCTION__)
}