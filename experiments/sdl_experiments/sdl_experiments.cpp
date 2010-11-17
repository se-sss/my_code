#include "SDL.h"
#include <cstdio>
#define WIDTH 320
#define HEIGHT 240
#include "change_display_frequency.h"

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

  change_display_frequency(60);
  SDL_Delay(10000);
  change_display_frequency(75);

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

  obj q;
  q.x = 10;
  q.y = 20;
  q.dir = true;

  while (true)
  {
    checkInput();

    if (q.dir)
    {
      q.x++;
      if (q.x >= screen->w)
      {
        q.dir = !q.dir;
      }

    }
    else
    {
      q.x--;
      if (q.x < 0)
      {
        q.dir = !q.dir;
      }
    }

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

    for (int x = 0; x < screen->w; ++x)
    {
      int y = x * x / 100;
      if (y >= screen->h)
        break;

      drawPixel(screen, x, y, 220, 0, 0);
    }

    drawPixel(screen, q.x, q.y, 0, 255, 0);

    if (SDL_MUSTLOCK(screen))
    {
      SDL_UnlockSurface(screen);
    }

    SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
    SDL_Delay(10);
  }

  atexit(SDL_Quit);

  return 0;
}
