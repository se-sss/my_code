#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include <boost/array.hpp>
#include <se/utils/find_end_type.h>

namespace se
{
  namespace geometry
  {
    template < typename T , std::size_t N> class vec
    {
    private:
      boost::array < T, N > data;

    public:
      typedef T value_type;
	  typedef typename se::utils::find_end_type < T >::value_type end_type;

      vec()
      {
        data.assign(T());
      }


      vec(const T & a, const T & b, const T & c)
      {
        data[0] = a;
        data[1] = b;
        data[2] = c;
      }


      vec & operator+=(const vec & v)
      {
        data[0] += v.data[0];
        data[1] += v.data[1];
        data[2] += v.data[2];
        return *this;
      }

      template < typename P > vec & operator*=(const P & k)
      {

        const end_type k_casted = static_cast < end_type > (k);
        data[0] *= k_casted;
        data[1] *= k_casted;
        data[2] *= k_casted;
        return *this;
      }

      vec & operator*=(const end_type & k)
      {
        data[0] *= k;
        data[1] *= k;
        data[2] *= k;
        return *this;
      }

      vec & operator-=(const vec & v)
      {
        data[0] -= v.data[0];
        data[1] -= v.data[1];
        data[2] -= v.data[2];
        return *this;
      }

      const vec & operator+() const
      {
        return *this;
      }

      vec operator-() const
      {
        return vec(-this->data[0], -this->data[1], -this->data[2]);
      }

      vec operator+(const vec & v) const
      {
        return (vec(*this) += v);
      }

      vec operator-(const vec & v) const
      {
        return (vec(*this) -= v);
      }

      T & operator[] (int i)
      {
        return data[i];
      }

      const T & operator[] (int i) const
      {
        return data[i];
      }

      T operator, (const vec & v) const
      {
        return this->data[0] * v.data[0] +
          this->data[1] * v.data[1] + this->data[2] * v.data[2];
      }

      vec operator^(const vec & v) const
      {
        const T a = this->data[1] * v.data[2] - this->data[2] * v.data[1];
        const T b = this->data[2] * v.data[0] - this->data[0] * v.data[2];
        const T c = this->data[0] * v.data[1] - this->data[1] * v.data[0];

          return vec < T > (a, b, c);
      }

      T square_length() const
      {
        return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
      }

      vec &normalize()
      {
        const double inv_length = 1. / sqrt(this->square_length());
        data[0] *= inv_length;
        data[1] *= inv_length;
        data[2] *= inv_length;
      }

      static vec get_normalized(const vec& v)
      {
        return (vec(v)).normalize();
      }

      template < typename P, typename Q, std::size_t N >
        friend vec < Q, N > operator*(const P k, const vec < Q, N > &v);

      template < typename P, typename Q, std::size_t N >
        friend vec < Q, N > operator*(const vec < Q, N > &v, const P k);

      template < typename P, typename Q, std::size_t N >
        friend vec < Q, N > operator/(const vec < Q, N > &v, const P k);

    };

    template < typename P, typename Q, std::size_t N >
      vec < Q, N > operator*(const P k, const vec < Q, N > &v)
    {
      const Q a = (Q) (k * v.data[0]);
      const Q b = (Q) (k * v.data[1]);
      const Q c = (Q) (k * v.data[2]);
      return vec < Q > (a, b, c);
    }

    template < typename P, typename Q, std::size_t N >
      vec < Q, N > operator*(const vec < Q, N > &v, const P k)
    {
      const Q a = (Q) (k * v.data[0]);
      const Q b = (Q) (k * v.data[1]);
      const Q c = (Q) (k * v.data[2]);
      return vec < Q > (a, b, c);

    }

    template < typename P, typename Q, std::size_t N >
      vec < Q, N > operator/(const vec < Q, N > &v, const P k)
    {
      const Q a = (Q) (v.data[0] / k);
      const Q b = (Q) (v.data[1] / k);
      const Q c = (Q) (v.data[2] / k);
      return vec < Q > (a, b, c);

    }

  }
}
#endif
