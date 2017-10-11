#include "stdafx.h"
#include "content_manager.h"
#include "texture_packer_reader.hpp"

content_manager::content_manager() 
{
}

bool content_manager::init(SDL_Renderer * renderer)
{
	assert(renderer != nullptr);

	this->clean();

	m_renderer = renderer;
	m_sprites.clear();

	TTF_Init();

	return true;
}

void content_manager::clean()
{
	debug_print(__FUNCTION__);

	for (auto kv : m_sprites) {
		SDL_DestroyTexture(kv.second->texture());
		delete kv.second;
	}

	for (auto f : m_fonts) {
		TTF_CloseFont(f.second);
	}

	for (auto a : m_atlas) {
		safe_delete(a.second);
	}
	
	m_fonts.clear();
	m_sprites.clear();
	m_atlas.clear();

	m_renderer = nullptr;
}

sprite* content_manager::load_sprite(const std::string local)
{
	assert(local.size() > 0);
	assert(m_renderer != nullptr);

	//Verificando se o sprite já está em cache
	auto spr = m_sprites[local];

	if (spr != nullptr)
		return spr;

	//Caso ele não exista ainda, podemos iniciar a carga desse sprite
	auto tempSurface = IMG_Load(local.c_str());

	if (tempSurface == nullptr)
		return nullptr;
	
	auto txt = SDL_CreateTextureFromSurface(m_renderer, tempSurface);

	if (!txt)
		return nullptr;

	SDL_FreeSurface(tempSurface);

	//Obtendo informações sobre a imagem carregada
	auto rect = SDL_Rect{};

	if (SDL_QueryTexture(txt, NULL, NULL, &rect.w, &rect.h)) {
		return nullptr;
	} 
				
	//Salvando em cache local
	spr = new sprite(txt, rect.w, rect.h);
	m_sprites[local] = spr;

	return spr;
}

spritesheet * content_manager::load_spritesheet(const std::string local, int frame_width, int frame_height)
{
	assert(frame_width > 0);
	assert(frame_height > 0);
	assert(local.size() > 0);
	
	//Inicialmente vamos tentar carregar o sprite completo 
	auto sprite = this->load_sprite(local);

	if (sprite == nullptr)
		return nullptr;

	//Caso ele exista, vamos substituí-lo pela spritesheet
	auto ssheet = new spritesheet(sprite->texture(), sprite->width(), sprite->height(), frame_width, frame_height);
		
	m_sprites[local] = ssheet;
	
	//Remove memória alocada pelo objeto original
	delete sprite;

	return ssheet;
}

sprite_atlas * content_manager::load_sprite_atlas(const string local)
{
	assert(local.size() > 0);
	assert(m_renderer != nullptr);

	//Verificando se o atlas já está em cache
	auto atlas = m_atlas[local];

	if (atlas != nullptr)
		return atlas;

	//Vamos procurar ler o arquivo de atlas informado
	tpckreader::texture_atlas_reader<> reader;
	auto txtAtlas = reader.read_texture_atlas(local.c_str());

	if (txtAtlas->image_path.size() == 0) {
		return nullptr;
	}

	//Em seguida carregar o arquivo referenciado pelo atlas como um sprite
	sprite* atlasSprite = this->load_sprite(txtAtlas->image_path);
	
	if (atlasSprite == nullptr) {
		return nullptr;
	}

	atlas = new sprite_atlas(atlasSprite->texture(), std::move(txtAtlas));
	m_atlas[local] = atlas;

	return atlas;
}

TTF_Font * content_manager::load_font(const std::string local)
{
	auto ttf_font = m_fonts[local];

	if (ttf_font != nullptr)
		return ttf_font;

	ttf_font = TTF_OpenFont(local.c_str(), 32);

	if (ttf_font == nullptr) {
		cout << "nao foi possivel carregar fonte solicitada: " << TTF_GetError() << endl;
		return nullptr;
	}

	m_fonts[local] = ttf_font;

	return ttf_font;
}

SDL_Palette * content_manager::load_color_pallete()
{
	return nullptr;
}

content_manager::~content_manager()
{
	debug_print(__FUNCTION__)
}