#ifndef __label__
#define __label__

#include "game_object.h"

using namespace std;

//label pode ser utilizado para exibir texto
class label :
	public game_object
{

public:
	label();
	~label();

public:
	void set_text(string text);
	void set_color(const SDL_Color& c);

	virtual SDL_Rect get_bounds() {
		return SDL_Rect({ (int)m_position.x(), (int)m_position.y(), m_source_rect.w, m_source_rect.h });
	}

	virtual inline void set_position(const Vector2f& pos) { game_object::set_position(pos); }

public:
	// Inherited via game_object
	virtual void render(SDL_Renderer * canvas, SDL_Rect * dest) override;
	virtual void render(SDL_Renderer * canvas) override;
	virtual bool load(content_manager * cm) override;
	virtual void update(float elapsedTime) override;

private:
	SDL_Texture*	m_text_texture;
	TTF_Font*		m_font;
	string			m_text;
	SDL_Color		m_fg_color;
	SDL_Color		m_bg_color;
	SDL_Rect		m_source_rect;
};

#endif // !__label__