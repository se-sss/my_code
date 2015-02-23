#include <math.h>
#include <stdio.h>

int main()
{
  const float f = 6.f;
  const float a = 10.f;
  const float T = 0.013f;
  float v_max = 320.f;

  float v_ground_reasonable =
    (float) sqrt((-30 * 30 + a * T * (2 - a * T) * v_max * v_max) /
                 (f * T * (2 - f * T)));

  while (1)
  {
    scanf("%f", &v_max);
    v_ground_reasonable =
      (float) sqrt((-30 * 30 + a * T * (2 - a * T) * v_max * v_max) /
                   (f * T * (2 - f * T)));
    printf("v_max=%f  v_reasonable=%f\n", v_max, v_ground_reasonable);
  }
  return 0;
}
