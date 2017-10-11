#ifndef __pause_gamestate__
#define __pause_gamestate__

#include "game_state.h"

class pause_gamestate :
	public game_state
{

public:
	pause_gamestate();
	virtual ~pause_gamestate();

public:

	// Inherited via game_state
	virtual int id() override;
	virtual void update(float elapsedTime) override;
	virtual void render(SDL_Renderer * r) override;
	virtual void on_exit(game * g) override;
	virtual void on_enter(game * g) override;
	virtual void on_pause(game * g) override;
	virtual void on_resume(game * g) override;

private:
	bool m_initialized;
};

#endif // !__pause_gamestate__
