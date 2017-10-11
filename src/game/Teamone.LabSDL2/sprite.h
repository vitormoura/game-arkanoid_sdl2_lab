#pragma once
#ifndef __sprite__
#define __sprite__

//Representa um sprite
class sprite
{

public:
	sprite(SDL_Texture* texture, int width, int height);
	sprite(SDL_Texture* texture, const SDL_Rect& sourceRect);

	virtual ~sprite();

public:
	
	//recupera referência para textura
	inline SDL_Texture* texture()	const { return m_texture; }

	//recupera largura
	inline size_t		width()		const { return m_source.w; }

	//recupera altura
	inline size_t		height()	const {	return m_source.h; }
	
public:

	//renderiza sprite utilizando o renderer e destino informados
	void render(SDL_Renderer * canvas, SDL_Rect* dest);

protected:

	SDL_Texture* m_texture;
	SDL_Rect m_source;
};

#endif // !__sprite__
