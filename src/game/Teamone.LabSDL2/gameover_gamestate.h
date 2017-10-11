#pragma once
#include "game_state.h"
#include "label.h"

class gameover_gamestate :
	public game_state
{

private:
	label* m_message;

public:
	gameover_gamestate();
	~gameover_gamestate();

	
	virtual int id() override;
	virtual void update(float elapsedTime) override;
	virtual void render(SDL_Renderer * r) override;
	virtual void on_exit(game * g) override;
	virtual void on_enter(game * g) override;
	virtual void on_pause(game * g) override;
	virtual void on_resume(game * g) override;
};

