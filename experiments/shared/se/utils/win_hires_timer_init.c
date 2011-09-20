#include "win_hires_timer_init.h"

#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>
#include <Mmsystem.h>

static void deinit(void)
{
  timeEndPeriod(1);
}

void init_hires_timer(void)
{
  if (timeBeginPeriod(1) != TIMERR_NOERROR)
  {
    fprintf(stderr, "Failed to change timer resolution\n");
  }
  atexit(&deinit);
}

void print_device_caps(void)
{
  TIMECAPS time_caps;
  timeGetDevCaps(&time_caps, sizeof(time_caps));

  printf("Timer: min res=%d  max res=%d\n", time_caps.wPeriodMin, time_caps.wPeriodMax);

  //std::cout<<"Min res="<<time_caps.wPeriodMin<<"   Max res="<<time_caps.wPeriodMax<<std::endl;

}
