#include "win_hires_timer_init.h"

#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>
#include <Mmsystem.h>

static void deinit()
{
  timeEndPeriod(1);
}

void init_hires_timer()
{
  if (timeBeginPeriod(1) != TIMERR_NOERROR)
  {
    fprintf(stderr, "Failed to change timer resolution\n");
  }
  atexit(&deinit);
}
