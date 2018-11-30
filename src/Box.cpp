#include "Box.h"



Box::Box(int width, int height, SDL_Point position, SDL_Color c)
{
	m_color = c;
	m_width = width;
	m_height = height;
	m_position = position;
}


Box::~Box()
{
}

void Box::Move(int x, int y)
{
	m_position.x = m_position.x + x;
	m_position.y = m_position.y + y;
}

void Box::Draw(SDL_Renderer & r)
{
	m_rect = SDL_Rect({ m_position.x, m_position.y, m_width, m_height });
	SDL_SetRenderDrawColor(&r, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(&r, &m_rect);
}