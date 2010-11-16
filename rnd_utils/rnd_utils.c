#include <stdlib.h>
#include <assert.h>

#include "rnd_utils.h"

void take_m_out_of_n(int m, int n, int *dest)
{
  assert(n >= 0);
  assert(m >= 0);
  assert(m <= n);

  while (m > 0)
  {
    if (rand() % n-- < m)
    {
      --m;
      *(dest++) = n;
    }
  }
}
