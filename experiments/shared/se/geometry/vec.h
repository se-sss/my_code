#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include <boost/array.hpp>
#include <se/utils/find_end_type.h>

namespace se
{
  namespace geometry
  {
    template < typename T, std::size_t N > class vec
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

      vec & operator+=(const vec & v)
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] += v.data[i];
        }
        return *this;
      }

      vec & operator-=(const vec & v)
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] -= v.data[i];
        }
        return *this;
      }

      template < typename P > vec & operator*=(const P & k)
      {
        const end_type k_casted = static_cast < end_type > (k);
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] *= k_casted;
        }
        return *this;
      }

      template < typename P,
        template < typename > class CLASS > vec & operator*=(const CLASS < P >
                                                             &k)
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] *= k;
        }
        return *this;
      }

      vec & operator*=(const end_type & k)
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] *= k;
        }
        return *this;
      }

      template < typename P > vec & operator/=(const P & k)
      {
        const end_type k_inv =
          static_cast < end_type > (1) / static_cast < end_type > (k);

        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] *= k_inv;
        }
        return *this;
      }

      template < typename P,
        template < typename > class CLASS > vec & operator/=(const CLASS < P >
                                                             &k)
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] /= k;
        }
        return *this;
      }

      vec & operator/=(const end_type & k)
      {
        end_type k_inv = static_cast < end_type > (1) / k;

        for (std::size_t i = 0; i < N; ++i)
        {
          data[i] *= k_inv;
        }
        return *this;
      }

      const vec & operator+() const
      {
        return *this;
      }

      vec operator-() const
      {
        vec r = *this;
        for (std::size_t i = 0; i < N; ++i)
        {
          r.data[i] = r.data[i];
        }

        return r;
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
        T t = T(); //T t(); - func prototype
        for (std::size_t i = 0; i < N; ++i)
        {
          t += data[i] * v.data[i];
        }

        return t;
      }

      T square_length() const
      {
        return (*this, *this);
      }

      vec & normalize()
      {
        const double inv_length = 1. / sqrt(this->square_length());

        return *this *= inv_length;
      }

      static vec get_normalized(const vec & v)
      {
        return (vec(v)).normalize();
      }

      vec get_normalized() const
      {
        return (vec(*this)).normalize();
      }


      template < typename P > vec operator*(const P k) const
      {
        return vec(*this) *= k;
      }

      template < typename P, typename Q, std::size_t L >
        friend vec < Q, L > operator*(const P & k, const vec < Q, L > &v);

      template < typename P > vec operator/(const P & k) const
      {
        return vec(*this) /= k;
      }

    };

    template <typename P, typename Q, std::size_t L >
      vec < Q, L > operator*(const P & k, const vec < Q, L > &v)
    {
       return vec<Q, L>(v) *= k;
    }
  }
}
#endif
