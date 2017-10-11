#include "stdafx.h"
#include "sprite_atlas.h"



sprite_atlas::sprite_atlas(SDL_Texture* texture, unique_ptr<tpckreader::texture_atlas> atlas) :
	m_atlas(move(atlas)), m_texture(texture)
{
}

sprite_atlas::~sprite_atlas()
{
	debug_print(__FUNCTION__)

	for (auto s : m_sprites) {
		safe_delete(s.second);
	}

	m_sprites.clear();
}

sprite * sprite_atlas::get_sprite(string sprite_id)
{
	//Verificando se o sprite já está em cache
	auto spr = m_sprites[sprite_id];

	if (spr != nullptr)
		return spr;

	if (m_atlas->sprites.find(sprite_id) == m_atlas->sprites.end())
		return nullptr;

	auto regSpr = m_atlas->sprites[sprite_id].get();

	spr = m_sprites[sprite_id] = new sprite(m_texture, SDL_Rect{ regSpr->x, regSpr->y, (int)regSpr->w, (int)regSpr->h });
	
	return spr;
}
