#pragma once
#include "game_object.h"

class sprite_object :
	public game_object
{

private:
	sprite*		m_me;

public:
	sprite_object(sprite* me);
	~sprite_object();
	
public:
	virtual SDL_Rect get_bounds() override;
	virtual void render(SDL_Renderer * canvas, SDL_Rect * dest) override;
	virtual void render(SDL_Renderer * canvas) override;
	virtual bool load(content_manager * cm) override;
	virtual void update(float elapsedTime) override;
};

