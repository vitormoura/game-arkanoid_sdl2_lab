#include "stdafx.h"
#include "sound_manager.h"

sound_manager::sound_manager()
{
}

sound_manager::~sound_manager()
{
	debug_print(__FUNCTION__)
}

void sound_manager::init()
{
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);
}

void sound_manager::clean()
{
	m_music.clear();
	m_sfx.clear();

	Mix_CloseAudio();
}

bool sound_manager::load_sound(const string & local, const string id, sound_types type)
{
	assert(local.size() > 0);
	assert(id.size() > 0);
	
	if (type == sound_types::music) {

		Mix_Music* m = m_music[id];
		
		if (m != nullptr) {
			return true;
		}

		m = Mix_LoadMUS(local.c_str());

		if (m == nullptr) {
			cout << "could not load music file: " << Mix_GetError() << endl;
			return false;
		}

		m_music[id] = m;

		return true;
	}
	else if( type == sound_types::sfx) {
		
		Mix_Chunk* sfx = m_sfx[id];

		if (sfx != nullptr)
			return true;

		sfx = Mix_LoadWAV(local.c_str());

		if (sfx == nullptr) {
			cout << "could not load sfx file: " << Mix_GetError() << endl;
			return false;
		}

		m_sfx[id] = sfx;

		return true;
	}

	return false;
}

void sound_manager::play_music(const string id, int loops)
{
	assert(m_music[id] != nullptr);
	assert(loops >= 0);
		
	Mix_PlayMusic(m_music[id], loops);
}

void sound_manager::play_sfx(const string id)
{
	assert(m_sfx[id] != nullptr);
			
	Mix_PlayChannel(-1, m_sfx[id], 0);
}

void sound_manager::pause_music()
{
	Mix_PauseMusic();
}

void sound_manager::resume_music()
{
	Mix_ResumeMusic();
}
