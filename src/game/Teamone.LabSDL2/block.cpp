#include "stdafx.h"
#include "block.h"
#include <array>


block::block(int x, int y)
	: m_body(nullptr)
{
	m_static = false;
	this->set_position(Vector2f(x, y));
}

block::~block()
{
}

void block::render(SDL_Renderer * canvas, SDL_Rect * dest)
{
	m_body->render(canvas, dest);
}

void block::render(SDL_Renderer * canvas)
{
	auto dest = this->get_bounds();

	this->render(canvas, &dest);
}

bool block::load(content_manager * cm)
{
	const std::array<const char*, 3> ops{
		{ 
			"element_red_rectangle.png" , 
			"element_blue_rectangle.png" , 
			"element_green_rectangle.png" 
		}
	};
	
	auto atlas = cm->load_sprite_atlas("assets/arkanoid_atlas.xml");
	
	assert(atlas != nullptr);

	m_body = atlas->get_sprite(ops[rand() % 3]);

	return m_body != nullptr;
}

void block::update(float elapsedTime)
{
	
}
