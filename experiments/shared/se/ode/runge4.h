#ifndef RUNGE4_H_INCLUDED
#define RUNGE4_H_INCLUDED

#include <boost/function.hpp>

namespace se
{
  namespace ode
  {
    template < typename T, typename STATE > class Runge4
    {
    public:
      typedef boost::function < void (const T dt, const STATE & v,
                                      STATE & result) > f_t;
      typedef STATE state_t;
      typedef T time_t;
    private:
        state_t & v;
      f_t f;
      time_t t;
        Runge4(Runge4 &);       //no copy constructor
        Runge4 & operator=(const Runge4 &);     //no assignment

    public:

        Runge4(state_t & data_vector, f_t func, time_t t0):v(data_vector),
        f(func), t(t0)
      {
      }

      void update(T dt)
      {
        STATE k1;
        STATE k2;
        STATE k3;
        STATE k4;

        time_t half_step = time_t(0.5) * dt;

        time_t half = t + half_step;
        time_t next = t + dt;

          f(t, v, k1);

        state_t tmp1 = (v + half_step * k1);
          f(half, tmp1, k2);

        const state_t tmp2(v + half_step * k2);
          f(half, tmp2, k3);

        const state_t tmp3(v + dt * k3);
          f(next, tmp3, k4);

          v += time_t((1. / 6.) * dt) * (k1 + 2 * k2 + 2 * k3 + k4);
          t = next;
      }

    };
  }
}
#endif
