#include <cstdio>
#include <vector>
#include "SDL.h"

int main()
{
   if(SDL_Init(SDL_INIT_VIDEO) < 0)
   {
       fprintf(stderr, "Cannot init SDL: %s\n", SDL_GetError());
       return -1;
   }

   std::vector<std::pair<int, int> > resolutions;

   SDL_Rect** modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
   for(int i = 0; modes[i]; ++i)
   {
       resolutions.push_back(std::make_pair(modes[i]->w, modes[i]->h));
   }

   SDL_Quit();

   printf("Available %lu mode(s):\n", resolutions.size());
   for(int i = 0; i < resolutions.size(); ++i)
   {
       printf("   %d x %d\n", resolutions[i].first, resolutions[i].second);
   }
   return 0;
}
