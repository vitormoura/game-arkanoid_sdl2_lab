#include "stdafx.h"
#include "input_manager.h"


input_manager::input_manager()
{
}

bool input_manager::init()
{
	return true;
}

void input_manager::clean()
{
	debug_print(__FUNCTION__)
	
	m_kb_handlers.clear();
	m_exit_handlers.clear();
	m_mouse_handlers.clear();
}

void input_manager::register_handler(kb_handler * handler)
{
	m_kb_handlers.push_back(handler);
}

void input_manager::register_handler(exit_handler * handler)
{
	m_exit_handlers.push_back(handler);
}

void input_manager::register_handler(mouse_handler * handler)
{
	m_mouse_handlers.push_back(handler);
}

void input_manager::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			for (auto h : m_kb_handlers) {
				if (h->is_enabled()) {
					h->on_keyevent(event.key);
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			for (auto h : m_mouse_handlers) {
				if (h->is_enabled()) {
					h->on_mousebutton(event.button);
				}
			}
			break;
								
		case SDL_MOUSEMOTION:
			for (auto h : m_mouse_handlers) {
				if (h->is_enabled()) {
					h->on_mousemove(event.motion);
				}
			}
			break;

		case SDL_QUIT:
			for (auto h : m_exit_handlers) {
				h->on_exit();
			}
			break;

		default:
			break;
		}
	}
}


input_manager::~input_manager()
{
	debug_print(__FUNCTION__)
}