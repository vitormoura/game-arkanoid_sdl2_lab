#pragma once
#ifndef __spritesheet__
#define __spritesheet__

#include "sprite.h"

//representa um conjunto uma folha de sprites, organizando sprites em frames de um grid retangular
class spritesheet : public sprite
{

public:
	spritesheet(SDL_Texture* texture, int width, int height, int frame_width, int frame_height);
	virtual ~spritesheet();

public:

	//largura de cada frame
	inline int frame_width()	const { return m_frame_width; }

	//altura de  cada frame
	inline int frame_height()	const { return m_frame_height; }

	//quantidade total de frames do spritesheet
	inline int frame_qtd()		const { return m_qtd_cols * m_qtd_rows; }

public:

	//renderiza o sprite do frame localizado na linha e colunas informadas
	int render_frame(SDL_Renderer * canvas, const SDL_Rect* dest, int row, int col);

private:
	
	int m_qtd_rows;
	int m_qtd_cols;
	int m_frame_width;
	int m_frame_height;
};

#endif // !__spritesheet__