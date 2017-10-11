#ifndef __ball__
#define __ball__

#include "game_object.h"
#include "input_manager.h"
#include "sprite.h"
#include "block.h"

//ball é o projetil que o jogador direciona para destruir blocos
class ball :
	public game_object,
	public input_manager::mouse_handler
{

private:
	SDL_Rect	m_boundaries;
	sprite*		m_body;
	size_t		m_speed;
	float		m_last_direction_angle;
	bool		m_alive;

public:
	ball();
	virtual ~ball();

public:
	
	inline void		set_boundaries(const SDL_Rect& rect) { m_boundaries = rect; }
	inline void		set_speed(size_t speed) { m_speed = speed; }
	inline size_t	get_speed() { return m_speed; }
		
public:
	virtual SDL_Rect get_bounds() override;
	virtual void render(SDL_Renderer * canvas, SDL_Rect * dest) override;
	virtual void render(SDL_Renderer * canvas) override;
	virtual bool load(content_manager * cm) override;
	virtual void update(float elapsedTime) override;

	virtual bool is_enabled() override;
	virtual void on_mousebutton(const SDL_MouseButtonEvent & e) override;
	virtual void on_mousemove(const SDL_MouseMotionEvent & e) override;

	bool hit(game_object* b, SDL_Rect& intersection);

private:
	void ensure_boundaries();

	
	
};

#endif // !__ball__