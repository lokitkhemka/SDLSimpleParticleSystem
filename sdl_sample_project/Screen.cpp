#include <cstring>
#include "Screen.h"
#include <iostream>


Screen::Screen():
	m_window(NULL),
	m_renderer(NULL),
	m_texture(NULL),
	m_buffer1(NULL),
	m_buffer2(NULL)
{
}

bool Screen::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Explosion",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL)
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

	std::memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
	std::memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}

bool Screen::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}
	return true;
}

void Screen::close()
{
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void Screen::update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));

	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);

	SDL_RenderPresent(m_renderer);
}


void Screen::BoxBlur()
{
	Uint32 *Temp;
	Temp = m_buffer2;
	m_buffer2 = m_buffer1;
	m_buffer1 = Temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{

			int RedTotal = 0;
			int GreenTotal = 0;
			int BlueTotal = 0;

			for (int row = -1; row <= 1; row++)
			{
				for (int col = -1; col <= 1; col++)
				{
					int CurrentX = x + col;
					int CurrentY = y + row;

					if (CurrentX >= 0 && CurrentX < SCREEN_WIDTH && CurrentY >= 0 && CurrentY < SCREEN_HEIGHT)
					{
						Uint32 Color = m_buffer2[CurrentY *SCREEN_WIDTH + CurrentX];

						Uint8 red = Color >> 24;
						Uint8 green = Color >> 16;
						Uint8 blue = Color >> 8;

						RedTotal += red;
						GreenTotal += green;
						BlueTotal += blue;
					}
				}

			}
			Uint8 red = RedTotal / 9;
			Uint8 green = GreenTotal / 9;
			Uint8 blue = BlueTotal / 9;
			setPixel(x, y, red, green, blue);
		}
	}
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	if (x <0 || x> SCREEN_WIDTH-1 || y < 0 || y > SCREEN_HEIGHT-1)
	{
		return;
	}
	Uint32 colour = 0;

	colour += red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF;

	m_buffer1[(y*SCREEN_WIDTH) + x] = colour;
}
