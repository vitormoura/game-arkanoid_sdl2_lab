#include "stdafx.h"
#include "game_object.h"


game_object::game_object()
	: m_position(Vector2f::Zero()), m_enabled(true), m_visible(true), m_direction(Vector2f::Zero())
{
}

game_object::~game_object()
{
}
