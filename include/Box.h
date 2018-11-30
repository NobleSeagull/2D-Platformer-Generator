#ifndef _BOX_H
#define _BOX_H

#include <SDL.h>
#include <SDL_image.h>

class Box
{
public:
	Box(int width, int height, SDL_Point position, SDL_Color c);
	~Box();

	void Move(int x, int y);

	void Draw(SDL_Renderer & r);

	SDL_Point position() { return m_position; };

private:
	int m_width;
	int m_height;

	SDL_Point m_position;

	SDL_Rect m_rect;

	SDL_Color m_color;

};
#endif
