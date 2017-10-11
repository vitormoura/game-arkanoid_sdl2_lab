#include "stdafx.h"
#include "gameover_gamestate.h"
#include "game.h"


gameover_gamestate::gameover_gamestate()
	: m_message(nullptr)
{
}

gameover_gamestate::~gameover_gamestate()
{
}

int gameover_gamestate::id()
{
	return 999;
}

void gameover_gamestate::update(float elapsedTime)
{
}

void gameover_gamestate::render(SDL_Renderer * r)
{
	if (m_message != nullptr) {
		SDL_RenderClear(r);

		m_message->render(r);

		SDL_RenderPresent(r);
	}
}

void gameover_gamestate::on_exit(game * g)
{
}

void gameover_gamestate::on_enter(game * g)
{
	if (m_message == nullptr) {

		m_message = new label();
		m_message->load(g->content());
		m_message->set_text("GAME OVER");
		m_message->set_position(Vector2f(g->get_width() / 2, g->get_height() / 2));

	}
}

void gameover_gamestate::on_pause(game * g)
{
}

void gameover_gamestate::on_resume(game * g)
{
}
