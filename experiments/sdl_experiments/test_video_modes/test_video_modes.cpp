#include "SDL.h"
#include <cstdio>
#include <ctime>
#include <cmath>
//#include <se/utils/change_display_frequency.h>
//#include <se/utils/timer.h>
//#include <boost/chrono.hpp>
//#include <se/utils/win_hires_timer_init.h>

/*
double time_change_ms()
{
  static se::utils::timer < double,
    se::utils::timer_implementations::win_hires > timer;

  return timer.dt();
}
*/
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
  if (x < 0 || x > screen->w - 1 || y < 0 || y > screen->h - 1)
    return;

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
        fprintf(stderr, "Unexpected bpp: %d\n", screen->format->BitsPerPixel);
    }
  }

}

int main(int argc, char *argv[])
{
//  using namespace boost::chrono;

//  init_hires_timer();

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

//  const int availableSDLDrivers =  SDL_GetNumVideoDrivers();
//  printf("Available SDL drivers: %d\n", availableSDLDrivers);
//  for(int i = 0; i <availableSDLDrivers; ++i)
//  {
//      printf("%d) %s\n", i + 1, SDL_GetVideoDriver(i));
//  }

//  change_display_frequency(60);
//  SDL_Delay(10000);
//  change_display_frequency(75);

  SDL_Surface *screen;
//ChangeDisplaySettings;

for (int vid_mode = 0; modes[vid_mode]; ++vid_mode)
{

  screen = SDL_SetVideoMode( modes[vid_mode]->w, modes[vid_mode]->h, 24,
                     SDL_SWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN  );
  if (screen == NULL)
  {                             // ≈сли установить разрешение не удалось
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(1);
  }

printf("BytesPerPixel: %d\n", screen->format->BytesPerPixel);
printf("  %d x %d\n", modes[vid_mode]->w, modes[vid_mode]->h);

//  print_device_caps();
//  init_hires_timer();

/*
  {//borders
     for(int i = 0; i < screen->w; ++i)
     {
          drawPixel(screen, i, 0, 255, 0, 0);
          drawPixel(screen, i, screen->h, 255, 0, 0);
     }
     for(int i = 0; i < screen->h; ++i)
     {
          drawPixel(screen, 0, i, 255, 0, 0);
          drawPixel(screen, screen->w, i, 255, 0, 0);
     }
  }
*/

  {                             //FUGURES
    int R = fmin(screen->w, screen->h) / 2;
    int xC = screen->w / 2;
    int yC = screen->h / 2;
    for (int i = 1; i < 25; ++i)
      for (int j = 1; j < 25; ++j)
      {

        memset(screen->pixels, 0,
               screen->format->BytesPerPixel * screen->w * screen->h);

  {//borders
     for(int i = 0; i < screen->w; ++i)
     {
          drawPixel(screen, i, 0, 255, 0, 0);
          drawPixel(screen, i, screen->h - 1, 255, 0, 0);
     }
     for(int i = 0; i < screen->h; ++i)
     {
          drawPixel(screen, 0, i, 255, 0, 0);
          drawPixel(screen, screen->w - 1, i, 255, 0, 0);
     }
  }


        for (double fi = 0.; fi <= 2 * 3.141593; fi += 0.001)
        {
          double x = sin(i * fi);
          double y = cos(j * fi);

          double r = sqrt(x * x + y * y);
          if (r > 1.)
            r = 1.;
          if (r < 0.)
            r = 0.;
          int colorRed = (int) (255. * (r));
          int colorBlue = (int) (255. * (1. - r));
          drawPixel(screen, xC + (int) (x * R), yC + (int) (y * R), colorRed,
                    0, colorBlue);
        }

        if (SDL_MUSTLOCK(screen))
        {
          SDL_UnlockSurface(screen);
        }

        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
        SDL_Delay(250);

      }
  }

SDL_Delay(2000);
}

//  Satellite satellite;

//  high_resolution_clock::time_point start = high_resolution_clock::now();
  int i = 0;
  while (++i < 0)
  {
    //printf("delta  (ms)=  %f\n", time_change_ms());
//    double dt = time_change_ms();
//    printf("%lf\n", dt);

  //  high_resolution_clock::time_point stop = high_resolution_clock::now();
//    high_resolution_clock::duration elapsed = stop - start;
  //  start = stop;

    //if (nanoseconds(elapsed).count() > 0)
//    {
  //    std::cout << nanoseconds(elapsed) << std::endl;
//    }

    checkInput();

  //  satellite.update(dt);
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

//    const Satellite::state_t & state = satellite.get_state();
    int x = 0;
    int y = 0;
    x += screen->w / 2;
    y += screen->h / 2;
    drawPixel(screen, screen->w / 2, screen->h / 2, 0, 255, 0);

    drawPixel(screen, x, y, 255, 255, 0);

    if (SDL_MUSTLOCK(screen))
    {
      SDL_UnlockSurface(screen);
    }

    SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
    SDL_Delay(1);
  }

//  atexit(SDL_Quit);
    SDL_Quit();

  return 0;
}
