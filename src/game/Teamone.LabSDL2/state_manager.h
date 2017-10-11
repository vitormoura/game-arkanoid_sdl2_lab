#ifndef __state_manager__
#define __state_manager__

#include "game_state.h"

using namespace std;

//state_manager controla um conjunto de estados de jogo, definindo apenas um como estado atual por vez
class state_manager
{

public:
	state_manager(game* g);
	~state_manager();

public:

	//currente recupera apontamento para o estado de jogo atual
	inline game_state* current() { return m_states.back(); }

public:

	//push_state adiciona um novo estado à pilha de estados atual
	void push_state(game_state* s);
	
	//change_state muda imediatamente o estado atual
	void change_state(game_state* s);

	//pop_state remove o estado atual 
	game_state* pop_state();
		
	//update atualiza situação do estado de jogo atual
	void update(float elapsedTime);

	//render renderiza estado de jogo atual
	void render(SDL_Renderer* r);

	//clean remove todos os estados registrados
	void clean();

	//is retorna verdadeiro se o estado informado é o estado atual
	bool is(game_state* s) { return this->current() == s; }
		
private:
	vector<game_state*> m_states;
	game*				m_game;

};

#endif // !__state_manager__