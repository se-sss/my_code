#include <math.h>
#include <stdio.h>

#define max(a, b) (((a) > (b)) ? a : b)
struct vec2d
{
  float x;
  float y;
};

float mul(struct vec2d *v1, struct vec2d *v2)
{
  return v1->x * v2->x + v1->y * v2->y;
}
float length(struct vec2d *v)
{
  return (float) sqrt(v->x * v->x + v->y * v->y);
}

void normalize(struct vec2d *v)
{
  float lng = length(v);
  v->x /= lng;
  v->y /= lng;
}

void rotate(struct vec2d *src, struct vec2d *dst, float gamma)
{

  dst->x = src->x * cos(gamma) - src->y * sin(gamma);
  dst->y = src->x * sin(gamma) + src->y * cos(gamma);
  normalize(dst);
}

int main()
{
  const float f = 4.f;
  const float a = 10.f;
  const float T = 0.013f;
  const float v_max = 320.f;
  const float v_stop = 100.f;
  const float v1 = v_max * (1 - a * T) / (1 - f * T);

  int frame = 0;

  struct vec2d pos = { 0.f, 0.f };
  struct vec2d v = { 0.f, 0.f };
  struct vec2d wish_dir;

  float speed;
  float cos_best;
  float gamma_best;

  float v_ground_reasonable =
    (float) sqrt((-30 * 30 + a * T * (2 - a * T) * v_max * v_max) /
                 (f * T * (2 - f * T)));

  while (1)
  {
    printf("t=%.3f  ", frame * T);
    printf("x=%.3f y=%.3f", pos.x, pos.y);
    printf("  vx=%.3f vy=%.3f", v.x, v.y);

    speed = length(&v);
    printf("  speed=%.3f", speed);

    if (speed < 1.f)
    {
      wish_dir.x = 1.f;
      wish_dir.y = 0.f;
    }
    else if (speed <= v1)
    {
      wish_dir.x = v.x;
      wish_dir.y = v.y;
      normalize(&wish_dir);
    }
    else
    {
      cos_best = ((1 - a * T) / (1 - f * T)) * v_max / speed;

      if (cos_best > 1.f)
        cos_best = 1.f;         //just in case of rounding errors

      gamma_best = (float) acos(cos_best);

      rotate(&v, &wish_dir, gamma_best);

    }

    printf("  wish_dir.x=%.3f wish_dir.y=%.3f\n", wish_dir.x, wish_dir.y);

    {
      float control = speed < v_stop ? v_stop : speed;
      float drop = control * f * T;

      if (speed < 1.f)
      {
        v.x = v.y = 0.f;
      }
      else
      {
        float newspeed = speed - drop;
        newspeed = max(newspeed, 0.f);

        normalize(&v);
        v.x *= newspeed;
        v.y *= newspeed;
      }

    }

    {
      float currentspeed, addspeed;
      speed = length(&v);

      currentspeed = mul(&v, &wish_dir);
      addspeed = v_max - currentspeed;

      if (addspeed > 0)
      {
        float accelspeed = a * T * v_max;
        if (accelspeed > addspeed)
          accelspeed = addspeed;

        v.x += wish_dir.x * accelspeed;
        v.y += wish_dir.y * accelspeed;
      }

    }

    pos.x += v.x * T;
    pos.y += v.y * T;
    ++frame;

  }
  return 0;
}
