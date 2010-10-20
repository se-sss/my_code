#ifndef V3D_H_INCLUDED
#define V3D_H_INCLUDED

#include <boost/array.hpp>

template <typename T>
class v3d
{
	private:
	boost::array<T, 3> data;

public:
	v3d()
	{
		data[0] = data[1] = data[2] = (T) 0;
	}

	v3d(const v3d& v)
	{
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
	}


	v3d(const T a, const T b, const T c)
	{
		data[0] = a;
		data[1] = b;
		data[2] = c;
	}

	v3d& operator=(const v3d& v)
	{
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		return *this;
	}

	v3d& operator+=(const v3d& v)
	{
		data[0] += v.data[0];
		data[1] += v.data[1];
		data[2] += v.data[2];
		return *this;
	}

	template<typename P>
	v3d& operator*=(const P k)
	{
		const T k_casted = (T) k;
		data[0] *= k_casted;
		data[1] *= k_casted;
		data[2] *= k_casted;
		return *this;
	}

	v3d& operator-=(const v3d& v)
	{
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		data[2] -= v.data[2];
		return *this;
	}


	const v3d& operator+() const
	{
		return *this;
	}


	v3d operator-() const
	{
		return v3d<T>(-this->data[0],
					-this->data[1],
					-this->data[2]);
	}

	v3d operator+(const v3d& v) const
	{
		return (v3d(*this) += v);
	}

	v3d operator-(const v3d& v) const
	{
		return (v3d(*this) -= v);
	}

	T operator,(const v3d& v) const
	{
		return  this->data[0] * v.data[0] +
			this->data[1] * v.data[1] +
			this->data[2] * v.data[2];
	}

	v3d operator^(const v3d& v) const
	{
		const T a = this->data[1] * v.data[2] - this->data[2] * v.data[1];
		const T b = this->data[2] * v.data[0] - this->data[0] * v.data[2];
		const T c = this->data[0] * v.data[1] - this->data[1] * v.data[0];

		return  v3d<T>(a, b, c);
	}

	T square_length() const
	{
		return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
	}

	v3d<T>& normalize()
	{
		const double inv_length = 1. / sqrt(this->square_length());
		data[0] *= inv_length;
		data[1] *= inv_length;
		data[2] *= inv_length;
	}

	static v3d<T> get_normalized(const v3d<T>& v)
	{
		return v3d<T>(v).normalize();
	}


	
	template<typename P, typename Q>
	friend v3d<Q> operator*(const P k, const v3d<Q> & v);

	template<typename P, typename Q>
	friend v3d<Q> operator*(const v3d<Q> & v, const P k);

	template<typename P, typename Q>
	friend v3d<Q> operator/(const v3d<Q> & v, const P k);



};

template<typename P, typename Q>
v3d<Q> operator*(const P k, const v3d<Q> & v)
{
		const Q a = (Q) (k * v.data[0]);
		const Q b = (Q) (k * v.data[1]);
		const Q c = (Q) (k * v.data[2]);
		return v3d<Q>(a, b, c);
}

template<typename P, typename Q>
v3d<Q> operator*(const v3d<Q> & v, const P k)
{
		const Q a = (Q) (k * v.data[0]);
		const Q b = (Q) (k * v.data[1]);
		const Q c = (Q) (k * v.data[2]);
		return v3d<Q>(a, b, c);

}

template<typename P, typename Q>
v3d<Q> operator/(const v3d<Q> & v, const P k)
{
		const Q a = (Q) (v.data[0] / k);
		const Q b = (Q) (v.data[1] / k);
		const Q c = (Q) (v.data[2] / k);
		return v3d<Q>(a, b, c);

}



#endif

