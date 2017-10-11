#ifndef __content_manager__
#define __content_manager__

#include <map>
#include "sprite.h"
#include "sprite_atlas.h"
#include "spritesheet.h"

using namespace std;

//Carrega e gerencia assets de jogo
class content_manager
{

public:
	content_manager();
	~content_manager();
	
public:

	//inicializa o content manager
	bool init(SDL_Renderer* renderer);

	//realiza rotinas de encerramento do content manager
	void clean();

	//load_sprite carrega um novo sprite para o content manager
	sprite* load_sprite(const string local);

	//load_spritesheet carrega um spritesheet para o content manager
	spritesheet* load_spritesheet(const string local, int frame_width, int frame_height);

	//load_spriteatlas carrega um atlas de sprites
	sprite_atlas* load_sprite_atlas(const string local);

	//load_font carrega uma fonte de texto
	TTF_Font* load_font(const string local);
	
	//load_color_pallete carrega paleta de cores padrão
	SDL_Palette* load_color_pallete();

private:
	map<string, sprite*>		m_sprites;
	map<string, TTF_Font*>		m_fonts;
	map<string, sprite_atlas*>	m_atlas;
	SDL_Renderer*				m_renderer;
	SDL_Palette*				m_pallete;
};

#endif

