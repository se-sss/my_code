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
      v3d():vec()
      {
      }

      v3d(const T & a, const T & b, const T & c)
      {
        data[0] = a;
        data[1] = b;
        data[2] = c;
      }

      v3d operator^(const v3d & v) const
      {
        const T a = this->data[1] * v.data[2] - this->data[2] * v.data[1];
        const T b = this->data[2] * v.data[0] - this->data[0] * v.data[2];
        const T c = this->data[0] * v.data[1] - this->data[1] * v.data[0];

          return v3d < T > (a, b, c);
      }
    };


  }
}
#endif
