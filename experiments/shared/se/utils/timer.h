#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <ctime>

#ifdef WIN32
#include <Windows.h>
#include <Mmsystem.h>
#endif

namespace se
{
  namespace utils
  {

    namespace timer_implementations
    {
      struct ansi
      {
      };

#ifdef WIN32
      struct win_hires
      {
      };
#endif
    }

    template < typename FLOAT, typename IMPLEMENTATION =
      timer_implementations::ansi > class timer
    {
    };

      template < typename FLOAT > class timer < FLOAT,
      timer_implementations::ansi >
    {
    private:
      clock_t t;
    public:
      timer():t(clock())
      {
        if (t == (clock_t) (-1))        //timer unavailable
        {
        }
      }
      FLOAT dt()
      {
        clock_t t_new = clock();
        clock_t delta = t_new - t;
        t = t_new;
        return FLOAT(delta) / CLOCKS_PER_SEC;
      }
    };

#ifdef WIN32
    template < typename FLOAT > class timer < FLOAT,
      timer_implementations::win_hires >
    {
    private:
      static __int64 query_counter()
      {
        __int64 cnt;
        QueryPerformanceCounter((LARGE_INTEGER *) & cnt);
        return cnt;
      }
      __int64 count;
    public:
    timer():count(query_counter())
      {
      }
      FLOAT dt()
      {
        __int64 count_new = query_counter();
        __int64 delta = count_new - count;
        count = count_new;

        __int64 freq;
        QueryPerformanceFrequency((LARGE_INTEGER *) & freq);
        return FLOAT(delta) / freq;
      }
    };
#endif
  }
}

#endif
