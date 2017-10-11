#ifndef __game_state__ 
#define __game_state__

#include "content_manager.h"

class game;

//game_state representa um estado do jogo abstrato
class game_state
{

public:
	
	virtual ~game_state() {};

public:

	//id retorna identificador �nico do estado
	virtual int id() = 0;

	//update atualiza estado de jogo
	virtual void update(float elapsedTime)	= 0;

	//render rederiza o estado do jogo
	virtual void render(SDL_Renderer * r)	= 0;
	
	//on_exit � disparado sempre que o estado de jogo � removido
	virtual void on_exit(game* g)			= 0;

	//on_enter � disparado sempre que o estado de jogo se torna ativo
	virtual void on_enter(game* g)			= 0;

	//on_hold � disparado sempre quando o estado � colocado em segundo plano
	virtual void on_pause(game* g)			= 0;

	//on_resume � disparado sempre que o estado � retomado a partir do segundo plano
	virtual void on_resume(game* g)			= 0;
	
};

#endif // ! 

