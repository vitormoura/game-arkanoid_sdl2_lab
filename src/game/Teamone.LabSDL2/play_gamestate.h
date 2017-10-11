#ifndef __play_gamestate__
#define __play_gamestate__

#include "game_state.h"
#include "player.h"
#include "label.h"
#include "ball.h"
#include "block.h"

//play_gamestate representa o estado de jogo ativo
class play_gamestate :
	public game_state
{

private:
	vector<game_object*>	m_objects;
	player*					m_player;
	label*					m_fps_label;
	ball*					m_ball;
	SDL_Color				m_bgcolor;
	game*					m_game;
	int m_points;
	int m_lives;
	SDL_Rect m_game_boundaries;

public:
	play_gamestate();
	virtual ~play_gamestate();
	
public:

	// Inherited via game_state
	virtual int id() override;
	virtual void update(float elapsedTime) override;
	virtual void render(SDL_Renderer * r) override;
	virtual void on_exit(game* g) override;
	virtual void on_enter(game* g) override;
	virtual void on_pause(game * g) override;
	virtual void on_resume(game* g) override;

private:
	void prepare_block_grid();
	void reset_ball();

};

#endif // !__play_gamestate__