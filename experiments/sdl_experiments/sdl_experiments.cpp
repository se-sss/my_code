#include "SDL.h"
#include <cstdio>
int main(int argc, char* argv[])
{
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
	{
        fprintf(stderr, "Не могу инициализировать SDL: %s\n", SDL_GetError());
        exit(1);
    }

	const SDL_VideoInfo * info = SDL_GetVideoInfo();
	SDL_Rect ** modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
    printf("Available Modes\n");
    for(int i=0;modes[i];++i)
	{
		printf("  %d x %d\n", modes[i]->w, modes[i]->h);
	}

char* p	;


SDL_Surface *screen;
 
    screen = SDL_SetVideoMode(1024, 600, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
    if ( screen == NULL ) {// Если установить разрешение не удалось
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(1);
    }
	p = (char*) screen->pixels;



	while(true)
	{
		*(p++) = 100;
		SDL_UpdateRect(screen, 0, 0, 1024, 600);
		SDL_Delay(100);
		
	}
	

    atexit(SDL_Quit);
 

	return 0;
}

