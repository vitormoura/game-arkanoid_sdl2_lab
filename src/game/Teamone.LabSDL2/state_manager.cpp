#include "stdafx.h"
#include "state_manager.h"


state_manager::state_manager(game* g)
	: m_game(g)
{
}

void state_manager::change_state(game_state * s)
{
	//Remove estado atual e inicia novo estado
	this->pop_state();
	this->push_state(s);
}

void state_manager::push_state(game_state * s)
{
	assert(s != nullptr);

	if( m_states.size() > 0)
		m_states.back()->on_pause(m_game);

	m_states.push_back(s);

	s->on_enter(m_game);
}

game_state * state_manager::pop_state()
{
	assert(m_states.size() > 0);

	//Recupera estado atual e executa rotina de encerramento
	auto s = m_states.back();
	s->on_exit(m_game);
		
	//Remove para que o estado atual passe a ser o ultimo estado 
	m_states.pop_back();

	if (m_states.size() > 0)
		m_states.back()->on_resume(m_game);

	return s;
}

void state_manager::update(float elapsedTime)
{
	this->current()->update(elapsedTime);
}

void state_manager::render(SDL_Renderer * r)
{
	this->current()->render(r);
}

void state_manager::clean()
{
	debug_print(__FUNCTION__)

	for (auto s : m_states) {
		s->on_exit(m_game);
	}
	
	m_states.clear();
}

state_manager::~state_manager()
{
	debug_print(__FUNCTION__)
}
