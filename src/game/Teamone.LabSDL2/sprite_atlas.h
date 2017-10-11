#ifndef __sprite_atlas__
#define __sprite_atlas__

#include <memory>
#include <map>
#include "sprite.h"
#include "texture_packer_reader.hpp"

using namespace std;

class sprite_atlas
{

private:
	unique_ptr<tpckreader::texture_atlas>	m_atlas;
	map<string, sprite*>		m_sprites;
	SDL_Texture*				m_texture;

public:
	sprite_atlas(SDL_Texture* texture, unique_ptr<tpckreader::texture_atlas> atlas);
	~sprite_atlas();
	
public:
	sprite* get_sprite(string sprite);

};

#endif

