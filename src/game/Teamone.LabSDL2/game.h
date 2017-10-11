#ifndef __game__
#define __game__

#include "input_manager.h"
#include "content_manager.h"
#include "state_manager.h"
#include "game_state.h"
#include "fps_counter.h"
#include "label.h"
#include "sound_manager.h"

using namespace std;

class game : 
	public input_manager::kb_handler, 
	public input_manager::exit_handler
{

public:
	game();
	~game();

public:
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void run();
	void clean();

	inline bool isRunning() { return m_running; }
	inline sound_manager* sounds() { return &m_sounds; }
	inline content_manager* content() { return &m_content; }
	inline input_manager* input() { return &m_input; }
	inline SDL_Renderer* renderer() { return m_renderer; }
	inline float fps() { return m_fps_counter.fps(); }
	inline state_manager* state() { return &m_state; }

public:
	inline int get_width() { return m_width; }
	inline int get_height() { return m_height; }

public:
	virtual void on_keyevent(const SDL_KeyboardEvent& k) override;
	virtual void on_exit() override;
	virtual bool is_enabled() override;

private:
	bool			m_running;
	SDL_Window*		m_window;
	SDL_Renderer*	m_renderer;
	
	sound_manager	m_sounds;
	content_manager m_content;
	input_manager	m_input;
	state_manager	m_state;
	fps_counter		m_fps_counter;
	size_t			m_width;
	size_t			m_height;

private:
	unique_ptr<game_state>	m_playstate;
	unique_ptr<game_state>	m_pausestate;
};

#endif