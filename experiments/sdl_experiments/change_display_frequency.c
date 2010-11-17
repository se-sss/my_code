#include "change_display_frequency.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

unsigned change_display_frequency(unsigned freq)
{
  DEVMODE d;
  LONG status;
  memset(&d, 0, sizeof d);

  d.dmSize = sizeof d;
  d.dmDisplayFrequency = freq;
  d.dmFields = DM_DISPLAYFREQUENCY;

  status = ChangeDisplaySettings(&d, CDS_UPDATEREGISTRY);

  if (DISP_CHANGE_SUCCESSFUL == status)
  {
    printf("Frequency changed to %d Hz\n", d.dmDisplayFrequency);
  }
  else
  {
    const char *error_str = "";
    switch (status)
    {

      case DISP_CHANGE_BADDUALVIEW:
        error_str =
          "The settings change was unsuccessful because the system is DualView capable.";
        break;
      case DISP_CHANGE_BADFLAGS:
        error_str = "An invalid set of flags was passed in.";
        break;
      case DISP_CHANGE_BADMODE:
        error_str = "The graphics mode is not supported.";
        break;
      case DISP_CHANGE_BADPARAM:
        error_str =
          "An invalid parameter was passed in. This can include an invalid flag or combination of flags.";
        break;
      case DISP_CHANGE_FAILED:
        error_str = "The display driver failed the specified graphics mode.";
        break;
      case DISP_CHANGE_NOTUPDATED:
        error_str = "Unable to write settings to the registry.";
        break;
      case DISP_CHANGE_RESTART:
        error_str =
          "The computer must be restarted for the graphics mode to work.";
        break;
    }

    fprintf(stderr, "Failed to change frequency. Error code is %d: %s\n",
            status, error_str);

  }

  return d.dmDisplayFrequency;
}
