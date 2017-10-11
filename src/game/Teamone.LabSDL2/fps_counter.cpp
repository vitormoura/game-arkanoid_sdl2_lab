#include "stdafx.h"
#include "fps_counter.h"


fps_counter::fps_counter()
	: m_fps(0), m_frame_count(0), m_elapsed_time(0)
{
}

fps_counter::~fps_counter()
{
}

void fps_counter::update(float elapsedTime)
{
	m_frame_count++;
	m_elapsed_time += elapsedTime;
	
	if (m_elapsed_time >= 1.0f) {
		m_elapsed_time = m_elapsed_time - 1.f;
		m_fps = m_frame_count;
		
		m_frame_count = 0;
	}
}
