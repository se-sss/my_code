#include "SDL.h"
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <Mmsystem.h>
#define WIDTH 320
#define HEIGHT 240
#include <se/utils/change_display_frequency.h>

#include "satellite.h"

double time_change_ms()
{
	/*
	static clock_t t1 = clock();
	clock_t t2;
    t2 = clock();
	clock_t delta = t2 - t1;
	t1 = t2;
    return (int) (delta * 1000 / CLOCKS_PER_SEC);
	*/

	__int64 pcount;
	static __int64 startcount;
	static DWORD starttime;
	static bool first = true;

	QueryPerformanceCounter ((LARGE_INTEGER *)&pcount);
	__int64 freq;

	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	if (first) 
	{
			first = false;
			startcount = pcount;
			return 0;
	}

	double delta = (double) (pcount - startcount);
	startcount = pcount;
	return delta / freq;

}

void checkInput()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {

    switch (event.type)
    {
      case SDL_KEYDOWN:
        printf("Key press detected\n");
        break;

      case SDL_KEYUP:
        printf("Key release detected\n");
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          printf("Escape\n");
          exit(0);
        }

        break;

      case SDL_QUIT:
        printf("Quit msg\n");
        exit(0);
        break;

      default:
        break;

    }

  }

}

void drawPixel(SDL_Surface * screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if(x < 0 || x > screen->w - 1 ||
		y < 0 || y > screen->h - 1) return; 

	Uint32 color = SDL_MapRGB(screen->format, r, g, b);

  if (screen->format->palette || screen->format->BitsPerPixel == 8)
  {
    Uint8 *pixel = (Uint8 *) screen->pixels + (screen->w * y + x);
    *pixel = color;
  }
  else
  {
    char *pixel = (char *) screen->pixels +
      screen->format->BytesPerPixel * (screen->w * y + x);

    switch (screen->format->BitsPerPixel)
    {
      case 16:
        *((Uint16 *) pixel) = color;
        break;
      case 24:
        {
          Uint8 *p = (Uint8 *) pixel;
          if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
          {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
          }
          else
          {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
          }
        }
        break;
      case 32:
        *((Uint32 *) pixel) = color;
        break;
      default:
        fprintf(stderr, "Unexpected bpp: \n", screen->format->BitsPerPixel);
    }
  }

}

struct obj
{
  int x, y;
  bool dir;
};

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Cannot init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  const SDL_VideoInfo *info = SDL_GetVideoInfo();
  SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
  printf("Available Modes\n");
  for (int i = 0; modes[i]; ++i)
  {
    printf("  %d x %d\n", modes[i]->w, modes[i]->h);
  }

//  change_display_frequency(60);
//  SDL_Delay(10000);
//  change_display_frequency(75);

  SDL_Surface *screen;
  //ChangeDisplaySettings;

  screen =
    SDL_SetVideoMode(WIDTH, HEIGHT, 24,
                     SDL_SWSURFACE | SDL_DOUBLEBUF /*|SDL_FULLSCREEN */ );
  if (screen == NULL)
  {                             // ≈сли установить разрешение не удалось
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(1);
  }

if(TIMERR_NOERROR == timeBeginPeriod(1))
{
	printf("Timer resolution changed\n");
}
else
{
	printf("Failed to change timer resolution\n");
}

Satellite satellite;
  while (true)
  {
    //printf("delta  (ms)=  %f\n", time_change_ms());
    double dt = time_change_ms();
    printf("%lf\n", dt);

    checkInput();

	satellite.update(dt);
    /* Lock the screen for direct access to the pixels */
    if (SDL_MUSTLOCK(screen))
    {
      if (SDL_LockSurface(screen) < 0)
      {
        fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
        exit(1);
      }
    }

    memset(screen->pixels, 0,
           screen->format->BytesPerPixel * screen->w * screen->h);


		const Satellite::state_t& state = satellite.get_state();
		int x = (int) state[0][0];
		int y = (int) state[0][1];
		x += screen->w / 2;
		y += screen->h / 2;
		drawPixel(screen, screen->w / 2, screen->h / 2, 0, 255, 0);

	drawPixel(screen, x, y, 255, 255, 0);

    if (SDL_MUSTLOCK(screen))
    {
      SDL_UnlockSurface(screen);
    }

    SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
    SDL_Delay(0);
  }

  timeEndPeriod(1);

  atexit(SDL_Quit);

  return 0;
}
