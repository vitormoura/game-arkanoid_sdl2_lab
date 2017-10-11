#pragma once
#ifndef __input_manager__
#define __input_manager__

using namespace std;

//input_manager verifica ocorrência de eventos, notificando componentes registrados
class input_manager
{
public:

	//kb_handler define operações de componentes interessados em eventos de teclado
	class kb_handler {
	public:
		virtual bool is_enabled() = 0;
		virtual void on_keyevent(const SDL_KeyboardEvent& k) = 0;
	};

	//exit_handler define de componentes interessados em eventos de encerramento do jogo
	class exit_handler {
	public:
		virtual void on_exit() = 0;
	};

	//mouse_handler define componentes interessados em eventos de mouse
	class mouse_handler {
	public:
		virtual bool is_enabled() = 0;
		virtual void on_mousebutton(const SDL_MouseButtonEvent& e)	= 0;
		virtual void on_mousemove(const SDL_MouseMotionEvent& e) = 0;
	};


public:

	input_manager();
	~input_manager();

	//init inicializa gerenciador
	bool init();

	//update busca ocorrência de novos eventos e avisa handlers interessados 
	void update();

	//clean remove todos os handlers registrados
	void clean();
		
	//register_handler registra um novo handler para eventos de teclado
	void register_handler(kb_handler* handler);

	//register_handler registra um novo handler para eventos de enerramento
	void register_handler(exit_handler*	handler);

	//register_handler registra um novo handler para eventos de mouse
	void register_handler(mouse_handler* handler);

private:
	vector<kb_handler*>		m_kb_handlers;
	vector<exit_handler*>	m_exit_handlers;
	vector<mouse_handler*>	m_mouse_handlers;
};

#endif // !__input_manager__