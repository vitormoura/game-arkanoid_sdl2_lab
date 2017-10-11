#include "stdafx.h"
#include "play_gamestate.h"
#include "game.h"
#include "block.h"
#include "ball.h"
#include "constantes.h"
#include "sprite_object.h"
#include "gameover_gamestate.h"

play_gamestate::play_gamestate()
	: m_player(nullptr),
	m_fps_label(nullptr),
	//m_bgcolor(SDL_Color{ 100, 149, 237, 255 }),
	m_bgcolor(SDL_Color{ 0, 0, 0, 255 })
{
}

void play_gamestate::update(float elapsedTime)
{
	for (auto o : m_objects) {

		if (o->is_enabled()) {

			o->update(elapsedTime);

			if (o != m_ball && !o->is_static()) {

				SDL_Rect intersection;

				if (m_ball->hit(o, intersection)) {

					if (o == m_player) {

						auto playerBounds = m_player->get_bounds();
						auto playerCenterX = playerBounds.x + (playerBounds.w / 2);
						auto ballBounds = m_ball->get_bounds();
						auto ballCenterX = ballBounds.x + (ballBounds.w / 2);

						if (abs(ballCenterX - playerCenterX) < (playerBounds.w / 4)) {
							m_ball->set_direction(Vector2f::UnitY() * -1);
						}
						else {

							if (m_player->get_direction().x() > 0) {

								Rotation2Df rotation(1.04);
								m_ball->set_direction(rotation * Vector2f::UnitY() * -1);
							}
							else {
								Rotation2Df rotation(-1.04);
								m_ball->set_direction(rotation * Vector2f::UnitY() * -1);
							}
						}
						
						m_game->sounds()->play_sfx("BALL_HIT");

					}
					else {

						m_ball->set_direction(m_ball->get_direction() * -1);
						o->set_visible(false);
						o->disable();

						m_points++;
						
						m_game->sounds()->play_sfx("BLOCK_HIT");
					}

					m_ball->set_speed(m_ball->get_speed() * 1.05);
				}

			}
		}
	}

	//Verificando se a bola ainda existe
	if (!m_ball->is_visible()) {
		m_lives -= 1;

		if (m_lives == 0) {
			m_game->state()->change_state(new gameover_gamestate());
		}
				
		this->reset_ball();
	}

	m_fps_label->set_text(to_string(this->m_points));
}

void play_gamestate::render(SDL_Renderer * r)
{
	//Redefinindo cor padrão de fundo
	SDL_SetRenderDrawColor(r, m_bgcolor.r, m_bgcolor.g, m_bgcolor.b, m_bgcolor.a);

	SDL_RenderClear(r);
		
	for (auto o : m_objects) {

		if (o->is_visible()) {
			o->render(r);
		}
	}

	SDL_RenderPresent(r);
}

void play_gamestate::on_exit(game* g)
{
	g->sounds()->pause_music();
}

void play_gamestate::on_enter(game* g)
{
	//Vamos criar os objetos do gamestate se player ainda não existe
	if (m_player == nullptr) {

		m_game_boundaries = SDL_Rect { M, M, g->get_width() - M, g->get_height() - M };

		//background
		auto bgSprite = g->content()->load_sprite("./Assets/breakout_bg.png");
		m_objects.push_back(new sprite_object(bgSprite));

		/*
		//Desenho das laterais da tela
		auto atlas = g->content()->load_sprite_atlas("./Assets/arkanoid_atlas.xml");
		auto blockSpr = atlas->get_sprite("element_grey_square_glossy.png");

		for (size_t i = 1; i < (g->get_width() / M - 1); i++)
		{
			auto so = new sprite_object(blockSpr);
			so->set_position(Vector2f(i * M, 0));

			m_objects.push_back(so);
		}

		for (size_t i = 0; i < g->get_height() / M; i++)
		{
			auto so1 = new sprite_object(blockSpr);
			so1->set_position(Vector2f(0, i * M));

			auto so2 = new sprite_object(blockSpr);
			so2->set_position(Vector2f((globalBoundaries.x + globalBoundaries.w), i * M));

			m_objects.push_back(so1);
			m_objects.push_back(so2);
		}
		*/

		m_player = new player();
		m_fps_label = new label();
		m_ball = new ball();

		m_objects.push_back(m_player);
		m_objects.push_back(m_fps_label);
		m_objects.push_back(m_ball);

		this->prepare_block_grid();

		for (auto o : m_objects) {
			o->load(g->content());
		}

		m_player->set_position(Vector2f{ m_game_boundaries.w / 2 - (m_player->get_bounds().w / 2), m_game_boundaries.h - M });
		m_player->set_boundaries(m_game_boundaries);
		
		reset_ball();
		
		g->sounds()->load_sound("./Assets/sfx_crystal_bowl.wav", "BLOCK_HIT", sound_manager::sound_types::sfx);
		g->sounds()->load_sound("./Assets/sfx_ball_hit.wav", "BALL_HIT", sound_manager::sound_types::sfx);
		g->sounds()->load_sound("./Assets/music_stage_001.wav", "MUSIC_STAGE_000", sound_manager::sound_types::music);

		//Registramos a ball junto ao input manager
		g->input()->register_handler(m_ball);
		g->input()->register_handler(m_player);

		m_points = 0;
		m_lives = 3;
	}

	m_game = g;

	g->sounds()->play_music("MUSIC_STAGE_000", 5);
	m_player->enable();
}

void play_gamestate::reset_ball()
{
	m_ball->set_position(Vector2f{ m_game_boundaries.x + m_game_boundaries.w / 2, m_game_boundaries.y + m_game_boundaries.h / 2 });
	m_ball->set_boundaries(m_game_boundaries);
	m_ball->set_direction(Vector2f::Ones());
	m_ball->set_speed(M * 5);
	m_ball->set_visible(true);
}

void play_gamestate::on_pause(game * g)
{
	if (m_player != nullptr) {
		for (auto o : m_objects) {
			o->disable();
		}

		g->sounds()->pause_music();
	}
}

void play_gamestate::on_resume(game * g)
{
	for (auto o : m_objects) {
		o->enable();
	}
	
	g->sounds()->resume_music();
}

void play_gamestate::prepare_block_grid()
{
	int anchorX = 50;
	int anchorY = 50;

	for (size_t l = 0; l < 3; l++)
	{
		for (size_t c = 0; c < 7; c++)
		{
			auto b = new block((c * M2 * 1.1) + 10 + anchorX, (l * M * 1.1) + anchorY);
			m_objects.push_back(b);
		}
	}
}

int play_gamestate::id()
{
	return 2;
}

play_gamestate::~play_gamestate()
{
	debug_print(__FUNCTION__)

		for (auto o : m_objects) {
			safe_delete(o);
		}
}
