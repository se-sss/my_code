#include <stdio.h>

#include "rnd_utils.h"

#define M 5
#define N 16
int main()
{
  int arr[M];
  int i;

  printf("Taking %d out of %d (range 0..%d):\n", M, N, N - 1);

  take_m_out_of_n(M, N, arr);

  for (i = 0; i < M; ++i)
  {
    printf("%d\n", arr[i]);
  }

  return 0;
}
