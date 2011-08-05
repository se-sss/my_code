#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "v3d.h"

template<typename T>
class quaternion
{

private:
	T r;
	v3d<T> v;

public :



	template<typename P, typename Q>
	friend quaternion<Q> operator*(const P k, const quaternion<Q> & q);

	template<typename P, typename Q>
	friend quaternion<Q> operator*(const quaternion<Q> & q, const P k);

	template<typename P>
	friend quaternion<P> operator*(const quaternion<P>& q, const v3d<P>& vec);

	template<typename P>
	friend quaternion<P> operator*(const v3d<P>& vec, const quaternion<P>& q);

	template<typename P>
	friend quaternion<P> operator*(const quaternion<P>& q1, const quaternion<P>& q2);

	template<typename P, typename Q>
	friend quaternion<Q> operator/(const P k, const quaternion<Q> & q);

	template<typename P, typename Q>
	friend quaternion<Q> operator/(const quaternion<Q> & q, const P k);

	template<typename P>
	friend quaternion<P> operator/(const quaternion<P>& q, const v3d<P>& vec);

	template<typename P>
	friend quaternion<P> operator/(const v3d<P>& vec, const quaternion<P>& q);

	template<typename P>
	friend quaternion<P> operator/(const quaternion<P>& q1, const quaternion<P>& q2);


	quaternion():r()
	{
	}

	quaternion(const T real_part) :
			r(real_part)
	{
	}

	quaternion(const v3d<T>& vector_part) :
			r(), v(vector_part)
	{
	}

	quaternion(const T& real_part, const v3d<T>& vector_part) :
			r(real_part), v(vector_part)
	{
	}

	quaternion(const quaternion& q) : r(q.r), v(q.v)
	{
	}

	quaternion(const T& a, const T& b, const T& c, const T& d) :
			 r(a), v(b, c, d)
	{
	}

	quaternion& operator=(const quaternion& q)
	{
		r = q.r;
		v = q.v;
		return *this;
	}

	quaternion& operator+=(const quaternion& q)
	{
		r += q.r;
		v += q.v;
		return *this;
	}

	quaternion& operator-=(const quaternion& q)
	{
		r += q.r;
		v += q.v;
		return *this;
	}

	template<typename P>
	quaternion& operator*=(const P& k)
	{
		r *= k;
		v *= k;
		return *this;
	}

	template<>
	quaternion& operator*=(const T& k)
	{
		r *= k;
		v *= k;
		return *this;
	}

	template<>
	quaternion& operator*=(const quaternion& q)
	{
		r = r * q.r - (v, q.v);
		v = r * q.v + q.r * v + v ^ q.v;
		return *this;
	}

	template<>
	quaternion& operator*=(const v3d<T>& q)
	{
		r =   - (v, q);
		v = r * q + v ^ q;
		return *this;
	}



	const quaternion& operator+() const
	{
		return *this;
	}


	quaternion operator-() const
	{
		return quaternion(-this->r, -this->v);
	}

	quaternion operator+(const quaternion& q) const
	{
		return (quaternion(*this) += q);
	}

	quaternion operator-(const quaternion& q) const
	{
		return (quaternion(*this) -= q);
	}

	T norm()const
	{
		return  r * r + v.square_length();
	}

	quaternion<T>& normalize()
	{
		const T q_norm = r * r + v.square_length();
		const double inv_length = 1. / sqrt(q_norm);
		r *= inv_length;
		v *= inv_length;
	}

	quaternion conj() const
	{
		return quaternion(this->r, -this->v);
	}


	quaternion inverse() const
	{
		return 1 / *this;
	}

	T& real()
	{
		return r;
	}

	const T& real() const
	{
		return r;
	}

	v3d<T>& vector()
	{
		return v;
	}

	const v3d<T>& vector() const
	{
		return v;
	}
};

template<typename P, typename Q>
quaternion<Q> operator*(const P k, const quaternion<Q> & q)
{
		return quaternion<Q>((Q) k * q.r, q.v * k);
}

template<typename P, typename Q>
quaternion<Q> operator*(const quaternion<Q> & q, const P k)
{
		return quaternion<Q>((Q) k * this->r, this->v * k);
}

template<typename P>
quaternion<P> operator*(const quaternion<P>& q, const v3d<P>& vec)
{
	return quaternion<P>(-(q.v, vec), q.r * vec + q.v ^ vec);
}

template<typename P>
quaternion<P> operator*(const v3d<P>& vec, const quaternion<P>& q)
{
	return quaternion<P>(-(q.v, vec), q.r * vec + (q.v ^ vec));
}

template<typename P>
quaternion<P> operator*(const quaternion<P>& q1, const quaternion<P>& q2)
{
	return quaternion<P>(q1.r * q2.r - (q1.v, q2.v),
					q1.r * q2.v + q2.r * q1.v + q1.v ^ q2.v);
}

template<typename P, typename Q>
quaternion<Q> operator/(const P k, const quaternion<Q> & q)
{
		return ((Q) k / q.norm()) * q.conj();
}

template<typename P, typename Q>
quaternion<Q> operator/(const quaternion<Q> & q, const P k)
{
		return quaternion<Q>(q.r / (Q) k, q.v / (Q) k);
}

template<typename P>
quaternion<P> operator/(const quaternion<P>& q, const v3d<P>& vec)
{
	return q * quaternion<P>(vec).inverse();
}

template<typename P>
quaternion<P> operator/(const v3d<P>& vec, const quaternion<P>& q)
{
	return quaternion<P>(vec) * q.inverse();
}

template<typename P>
quaternion<P> operator/(const quaternion<P>& q1, const quaternion<P>& q2)
{
	return q1 * q2.inverse();
}


#endif

