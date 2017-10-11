#include "stdafx.h"
#include "ball.h"
#include "constantes.h"

ball::ball()
	: m_body(nullptr), m_speed(M)
{
	m_position = Vector2f::Zero();
}

ball::~ball()
{
}

SDL_Rect ball::get_bounds()
{
	return SDL_Rect({
		(int)m_position.x(),
		(int)m_position.y(),
		(int)m_body->width(),
		(int)m_body->height()
	});
}

void ball::render(SDL_Renderer * canvas, SDL_Rect * dest)
{
	m_body->render(canvas, dest);
}

void ball::render(SDL_Renderer * canvas)
{
	SDL_Rect dest = this->get_bounds();

	this->render(canvas, &dest);
}

bool ball::load(content_manager * cm)
{
	auto atlas = cm->load_sprite_atlas("assets/arkanoid_atlas.xml");

	assert(atlas != nullptr);

	m_body = atlas->get_sprite("ballBlue.png");

	return m_body != nullptr;
}

void ball::update(float elapsedTime)
{
	m_position += (m_direction * elapsedTime * m_speed);

	this->ensure_boundaries();
}

void ball::ensure_boundaries()
{
	int hitLocation = false;
	Vector2f pos = m_position;
	auto w = m_body->width();
	auto h = m_body->height();
		
	if (pos.x() < m_boundaries.x) {
		pos = Vector2f({ m_boundaries.x, m_position.y() });
		hitLocation = 4;
	}
	else if ((pos.x() + w) > (m_boundaries.x + m_boundaries.w)) {
		pos = Vector2f({ (m_boundaries.x + m_boundaries.w) - w, pos.y() });
		hitLocation = 2;
	}

	if (m_position.y() < m_boundaries.y) {
		pos = Vector2f({ pos.x(), m_boundaries.y });
		hitLocation = 1;
	}
	else if ((pos.y() + h) > (m_boundaries.y + m_boundaries.h)) {
		pos = Vector2f({
			pos.x(),
			(m_boundaries.y + m_boundaries.h) - h
		});
		hitLocation = 3;
	}
	
	if (hitLocation) {
									
		switch (hitLocation) {
		case 1:
			set_direction(Vector2f(m_direction.x(), m_direction.y() * -1));
			break;
		case 2:
		case 4:
			set_direction(Vector2f(m_direction.x() * -1, m_direction.y()));
			break;
		case 3:
			m_visible = false;
			break;
		}
	}

	this->set_position(pos);
}

bool ball::is_enabled()
{
	return game_object::is_enabled();
}

void ball::on_mousebutton(const SDL_MouseButtonEvent & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		game_object::set_direction(Vector2f(e.x, e.y) - m_position);
	}
}

void ball::on_mousemove(const SDL_MouseMotionEvent & e)
{
}

bool ball::hit(game_object * b, SDL_Rect& intersection)
{
	SDL_Rect block = b->get_bounds();
	SDL_Rect me = this->get_bounds();
		
	return SDL_IntersectRect(&block, &me, &intersection);
}
