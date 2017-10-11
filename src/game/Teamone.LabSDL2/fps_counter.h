#pragma once
#ifndef __fps_counter__
#define __fps_counter__

//fps_counter conta a quantidade de atualizações por segundo
class fps_counter
{

public:
	fps_counter();
	~fps_counter();
		
	//update registra uma atualização
	virtual void update(float elapsedTime);

public:

	//fps retorna a quantidade de frames por segundo
	inline float fps() { return m_fps; }

private:
	int		m_frame_count;
	float	m_elapsed_time;
	float	m_fps;

};

#endif