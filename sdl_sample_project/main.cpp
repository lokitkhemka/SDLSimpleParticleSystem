#include <iostream>
#include <math.h>
#include <SDL.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
#include "Particle.h"
#include <assert.h>

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(0));
	Screen screen;

	if (!screen.Init())
	{
		cout << "Error in SDL." << endl;
	}

	Swarm swarm;
	while (true)
	{

		int elapsed = SDL_GetTicks();
		//screen.clear();
		swarm.Update(elapsed);
		unsigned char red =(unsigned char)(1 +  sin(elapsed * 0.0007))*(255 / 2);
		unsigned char green = (unsigned char)(1 + sin(elapsed * 0.001))*(255 / 2);
		unsigned char blue =  (unsigned char)(1 + sin(elapsed * 0.0009))*(255 / 2);

		Particle * const pParticles = swarm.particles();
		for (int i = 0; i < Swarm::nParticles; i++) {
			Particle particle = pParticles[i];

			int x = (int)((particle.m_x + 1) * (Screen::SCREEN_WIDTH - 1) / 2) ;
			int y = (int)((particle.m_y * (Screen::SCREEN_WIDTH - 1) / 2 ) + (Screen::SCREEN_HEIGHT/2));

			//x = (x >= Screen::SCREEN_WIDTH) ? Screen::SCREEN_WIDTH - 1 : x;
			//y = (y >= Screen::SCREEN_HEIGHT) ? Screen::SCREEN_HEIGHT - 1 : y;

			//assert(x < Screen::SCREEN_WIDTH);
			//assert(y < Screen::SCREEN_HEIGHT);


			screen.setPixel(x, y, red, green, blue);

		}
		screen.BoxBlur();
		screen.update();
		if (!screen.ProcessEvents()) {
			break;
		}
		
	}

	
	screen.close();

	return 0;

}