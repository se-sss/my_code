#include <cstdio>
#include "SDL.h"

int main()
{
   printf("Hello world!\n");
   if(SDL_Init(SDL_INIT_VIDEO) < 0)
   {
       fprintf(stderr, "Cannot init SDL: %s\n", SDL_GetError());
   }

   const SDL_VideoInfo* info = SDL_GetVideoInfo();
   SDL_Rect** modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
   printf("Available modes:\n");
   for(int i = 0; modes[i]; ++i)
   {
       printf("   %d x %d\n", modes[i]->w, modes[i]->h);
   }
}