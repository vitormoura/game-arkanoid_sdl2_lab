#ifndef __player__
#define __player__

#include "input_manager.h"
#include "game_object.h"

//player representa um jogador
class player : 
	public game_object,
	public input_manager::kb_handler
{


private:
	sprite*		m_me;
	float		m_speed;
	SDL_Rect	m_boundaries;

public:
	player();
	~player();
		
public:

	virtual void render(SDL_Renderer * canvas, SDL_Rect * dest) override;
	virtual void render(SDL_Renderer * canvas) override;

	virtual bool load(content_manager * cm) override;
	virtual void update(float elapsedTime) override;

	void set_boundaries(SDL_Rect rect);

	virtual inline SDL_Rect get_bounds() {
		return SDL_Rect({
			(int)m_position.x(),
			(int)m_position.y(),
			(int)m_me->width(),
			(int)m_me->height()
		});
	}

private:

	// Inherited via kb_handler
	virtual bool is_enabled() override;
	virtual void on_keyevent(const SDL_KeyboardEvent & k) override;

};

#endif // !__player__