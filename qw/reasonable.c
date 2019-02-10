#include <math.h>
#include <stdio.h>

int main()
{
  const float f = 4.f;
  const float a = 10.f;
  const float T = 0.013f;
  float v_max = 320.f;
  float v_ground_reasonable = 0.f;
  float v_ground_ultimate = 0.f;

  scanf("%f", &v_max);
  v_ground_reasonable =
      (float) sqrt((-30 * 30 + a * T * (2 - a * T) * v_max * v_max) /
                   (f * T * (2 - f * T)));

  v_ground_ultimate = v_max * (float) sqrt((a / f) * ((2 - a * T) / (2 - f * T)));

  printf("v_max=%f  v_reasonable=%f v_ultimate=%f\n", v_max, v_ground_reasonable, v_ground_ultimate);

  return 0;
}
