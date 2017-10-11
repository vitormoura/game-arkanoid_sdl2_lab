#include "stdafx.h"
#include "sprite_object.h"


sprite_object::sprite_object(sprite* me):
	m_me(me)
{
	m_static = true;
}

sprite_object::~sprite_object()
{
}

SDL_Rect sprite_object::get_bounds()
{
	return SDL_Rect({
		(int)m_position.x(),
		(int)m_position.y(),
		(int)m_me->width(),
		(int)m_me->height()
	});
}

void sprite_object::render(SDL_Renderer * canvas, SDL_Rect * dest)
{
	m_me->render(canvas, dest);
}

void sprite_object::render(SDL_Renderer * canvas)
{
	auto dest = get_bounds();
	this->render(canvas, &dest);
}

bool sprite_object::load(content_manager * cm)
{
	return m_me != nullptr;
}

void sprite_object::update(float elapsedTime)
{
}
