#include "stdafx.h"
#include "pause_gamestate.h"
#include "game.h"

pause_gamestate::pause_gamestate()
	: m_initialized(false)
{
}

pause_gamestate::~pause_gamestate()
{
}

int pause_gamestate::id()
{
	return 1;
}

void pause_gamestate::update(float elapsedTime)
{
}

void pause_gamestate::render(SDL_Renderer * r)
{
}

void pause_gamestate::on_exit(game * g)
{
}

void pause_gamestate::on_enter(game * g)
{
	if (!m_initialized) {
		m_initialized = g->sounds()->load_sound("./Assets/sfx_pause.wav", "PAUSE", sound_manager::sound_types::sfx);
	}

	g->sounds()->play_sfx("PAUSE");
}

void pause_gamestate::on_pause(game * g)
{
}

void pause_gamestate::on_resume(game * g)
{
}