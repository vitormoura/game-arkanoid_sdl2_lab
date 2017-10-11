#include "stdafx.h"
#include "game.h"
#include "label.h"
#include "play_gamestate.h"
#include "pause_gamestate.h"


game::game() : 
	m_running(false), 
	m_state(this), 
	m_playstate(new play_gamestate()),
	m_pausestate(new pause_gamestate())
{
}

bool game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	debug_print(__FUNCTION__);

	using namespace std;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		
		m_width = width;
		m_height = height;
		m_window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
		
		if (m_window != nullptr) {
			
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);

			if (m_renderer != nullptr) {
												
				if (m_content.init(m_renderer)) {
					
					m_sounds.init();
					
					m_state.push_state(m_playstate.get());

					m_input.register_handler(dynamic_cast<input_manager::kb_handler*>(this));
					m_input.register_handler(dynamic_cast<input_manager::exit_handler*>(this));
															
					return true;
				}
			}
		}
	}

	return false;
}

void game::clean()
{
	debug_print(__FUNCTION__)

	using namespace std;
			
	m_state.clean();
	m_input.clean();
	m_content.clean();
	m_sounds.clean();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void game::run()
{
	assert(!this->m_running);
		
	m_running = true;
		
	Uint32 FPS = 60;
	Uint32 DELAY_TIME = 1000.f / FPS;
	Uint32 frameStart, frameTime = 0;

	while (this->isRunning()) {
		frameStart = SDL_GetTicks();

		//update
		m_input.update();
		m_state.update(frameTime / 1000.0f);

		//render
		m_state.render(m_renderer);
				
		frameTime = SDL_GetTicks() - frameStart;

		///*
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));

			frameTime += (int)DELAY_TIME;
		}
		//*/

		m_fps_counter.update(frameTime / 1000.0f);
	}
}


void game::on_keyevent(const SDL_KeyboardEvent& k)
{
	if (k.type == SDL_KEYDOWN) {
		if (k.keysym.scancode == SDL_SCANCODE_RETURN) {
			
			auto pause = m_pausestate.get();

			if (m_state.is(pause)) {
				m_state.pop_state();
			}
			else {
				m_state.push_state(pause);
			}
		}
	}
		
}

void game::on_exit()
{
	m_running = false;
}

bool game::is_enabled()
{
	return true;
}

game::~game()
{
	debug_print(__FUNCTION__)
}