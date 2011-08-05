#ifndef V2D_H_INCLUDED
#define V2D_H_INCLUDED

#include <cmath>
#include <boost/array.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/mpl/if.hpp>


template <typename T>
class v2d
{
	private:
	typedef typename boost::is_arithmetic<T>::type elements_are_arithmetic;
	boost::array<T, 2> data;

public:
	v2d()
	{
		data[0] = data[1] = T();
	}

	explicit v2d(const v2d& v)
	{
		data[0] = v.data[0];
		data[1] = v.data[1];
	}


	v2d(const T& a, const T& b)
	{
		data[0] = a;
		data[1] = b;
	}

	v2d& operator=(const v2d& v)
	{
		data[0] = v.data[0];
		data[1] = v.data[1];
		return *this;
	}

	v2d& operator+=(const v2d& v)
	{
		data[0] += v.data[0];
		data[1] += v.data[1];
		return *this;
	}

	template<typename P>
	v2d& operator*=(const P& k)
	{
		typedef boost::mpl::if_<elements_are_arithmetic,
			T, P>::type cast_type;

		const cast_type k_casted = static_cast<cast_type>(k);
		data[0] *= k_casted;
		data[1] *= k_casted;
		return *this;
	}

	template<>
	v2d& operator*=(const T& k)
	{
		data[0] *= k;
		data[1] *= k;
		return *this;
	}


	v2d& operator-=(const v2d& v)
	{
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		return *this;
	}

	const v2d& operator+() const
	{
		return *this;
	}

	v2d operator-() const
	{
		return (v2d(- this->data[0],  -this->data[1]));
	}

	v2d operator+(const v2d& v) const
	{
		return (v2d(*this) += v);
	}

	v2d operator-(const v2d& v) const
	{
		return (v2d(*this) -= v);
	}

	T& operator[](int i) 
	{ 
		return data[i];
	}

	const T& operator[](int i) const 
	{ 
		return data[i];
	}

	T operator,(const v2d& v) const
	{
		return this->data[0] * v.data[0] + this->data[1] * v.data[1];
	}

	T square_length() const
	{
		return data[0] * data[0] + data[1] * data[1];
	}

	v2d<T>& normalize()
	{
		const double inv_length = 1. / sqrt(this->square_length());
		data[0] *= inv_length;
		data[1] *= inv_length;
		return *this;
	}

	template<typename ANY>
	v2d<float>& normalize()
	{
		const float inv_length = (float) (1. / sqrt(this->square_length()));
		data[0] *= inv_length;
		data[1] *= inv_length;
		return *this;
	}




	static v2d<T> get_normalized(const v2d<T>& v)
	{
		return v2d<T>(v).normalize();
	}


	template<typename P, typename Q>
	friend v2d<Q> operator*(const P k, const v2d<Q> & v);

	template<typename P, typename Q>
	friend v2d<Q> operator*(const v2d<Q> & v, const P k);

	template<typename P, typename Q>
	friend v2d<Q> operator/(const v2d<Q> & v, const P k);

};

template<typename P, typename Q>
v2d<Q> operator*(const P k, const v2d<Q> & v)
{
		const Q a = (Q) (k * v.data[0]);
		const Q b = (Q) (k * v.data[1]);
		return v2d<Q>(a, b);
}

template<typename P, typename Q>
v2d<Q> operator*(const v2d<Q> & v, const P k)
{
		const Q a = (Q) (k * v.data[0]);
		const Q b = (Q) (k * v.data[1]);
		return v2d<Q>(a, b);
}

template<typename P, typename Q>
v2d<Q> operator/(const v2d<Q> & v, const P k)
{
		const Q a = (Q) (v.data[0] / k);
		const Q b = (Q) (v.data[1] / k);
		return v2d<Q>(a, b);
}



#endif

