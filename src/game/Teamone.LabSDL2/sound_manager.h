#ifndef __sound_manager__
#define __sound_manager__

#include <map>

using namespace std;

class sound_manager
{
	
public:
	enum sound_types {
		music,
		sfx
	};
	
public:
	sound_manager();
	~sound_manager();

public:
	void init();
	void clean();
	
	bool load_sound(const string& local, const string id, sound_types type);
	void play_music(const string id, int loops);
	void play_sfx(const string id);

	void pause_music();
	void resume_music();

private:
	map<string, Mix_Music*> m_music;
	map<string, Mix_Chunk*> m_sfx;
};

#endif // !__sound_manager__
