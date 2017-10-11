#pragma once
#ifndef __block__
#define __block__

#include "game_object.h"
#include "sprite.h"

class block :
	public game_object
{

public:
	block(int x, int y);
	virtual ~block();

public:
	inline size_t get_width() { return m_body->width(); }
	inline size_t get_height() { return m_body->height(); }
	inline SDL_Rect get_bounds() {
		return SDL_Rect({
			(int)m_position.x(),
			(int)m_position.y(),
			(int)m_body->width(),
			(int)m_body->height()
		});
	}

public:
	
	virtual void render(SDL_Renderer * canvas, SDL_Rect * dest) override;
	virtual void render(SDL_Renderer * canvas) override;
	virtual bool load(content_manager * cm) override;
	virtual void update(float elapsedTime) override;

private:
	sprite* m_body;
};

#endif // !__block__