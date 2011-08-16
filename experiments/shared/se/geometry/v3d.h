#ifndef V3D_H_INCLUDED
#define V3D_H_INCLUDED

#include <boost/array.hpp>
#include <se/geometry/vec.h>

namespace se
{
  namespace geometry
  {
    template < typename T > class v3d : public vec<T, 3>
    {
    public:
      v3d()
      {
      }

      v3d(const v3d& v)
      {
      }


      v3d(const T & a, const T & b, const T & c)
      {
        (*this)[0] = a;
        (*this)[1] = b;
        (*this)[2] = c;
      }

      v3d operator^(const v3d & v) const
      {
        const T a = (*this)[1] * v[2] - (*this)[2] * v[1];
        const T b = (*this)[2] * v[0] - (*this)[0] * v[2];
        const T c = (*this)[0] * v[1] - (*this)[1] * v[0];

          return v3d < T > (a, b, c);
      }
    };


  }
}
#endif
