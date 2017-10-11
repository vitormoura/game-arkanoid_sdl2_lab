#ifndef __game_object__
#define __game_object__

#include "content_manager.h"

using namespace Eigen;
using namespace std;

//game_object representa um objeto de jogo genérico
class game_object
{

protected:
	Vector2f		m_position;
	bool			m_enabled;
	bool			m_visible;
	bool			m_static;
	Vector2f		m_direction;

public:
	game_object();
	~game_object();

public:
	//set_direction  redefine a direção do game_objetc
	virtual inline void set_direction(Vector2f dir) { dir.normalize(); m_direction = dir; }
		
	//set_position redefine a posição do game_object
	virtual inline void set_position(const Vector2f& pos) { m_position = pos; }

	//set_visible define se o objeto é ou não visível
	virtual inline void set_visible(bool visible) { m_visible = visible; }

	//is_enabled retorna se o objeto está ativo ou não
	inline bool is_enabled() const { return m_enabled; }

	//is_visible retorna se o objeto está ou não visível
	inline bool is_visible() const { return m_visible; }

	inline bool is_static() const { return m_static; }

	//get_direction recupera direção apontada pelo game_object
	inline Vector2f get_direction() const { return m_direction; }

	//get_bounds recupera corpo do gameobject
	virtual inline SDL_Rect get_bounds() = 0;

public:

	//render desenha representação do gameobject no renderer e destino inforamdos
	virtual void render(SDL_Renderer* canvas, SDL_Rect* dest)	= 0;

	//render desenha representação do gameobjet no renderer e posição padrão 
	virtual void render(SDL_Renderer* canvas)					= 0;

	//load carrega recursos necessários para correto funcionamento do gameobject
	virtual bool load(content_manager* cm)						= 0;
	
	//update executa rotinas para atualizar estado atual do gameobject
	virtual void update(float elapsedTime)						= 0;
		
	//disable torna o gameobjet inativo
	inline void disable() { m_enabled = false; }

	//enable torna o gameobject ativo
	inline void enable() { m_enabled = true; }
};

#endif

