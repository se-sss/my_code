#include "runge.h"
#include "../vectors/v2d.h"
#include "../vectors/v3d.h"
#include "../vectors/quaternion.h"

#include <boost/mpl/if.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/math/quaternion.hpp>
#include <complex>
/*
typedef Runge4<double, v2d<v3d<double> > > RNG;

void gf(const RNG::time_t t, const RNG::state_t& v, RNG::state_t& result)
{
	return;
}
template<typename A, typename B>
class S
{
public:
	A f(B b)
	{
		typedef boost::mpl::if_<boost::is_same<B, float>, B, float>::type to_type;

		return to_type(b);
	}
};
*/
int main(int argc, char* argv[])
{
	v3d<double> v1(1., 2., 3.);
	v1 *= 1.f;
	v1 *= 2.;
	v1 *= 3.L;

	v3d<v2d<float> > v2;
	v2 *= 3.L;

	v3d<quaternion<float> > v3;
	v3 *= 2.;
	v3 *= 3.f;

	v3d<quaternion<long double> > v4;
	v4 *= 2.;
	v4 *= 3.f;


	v3d<boost::math::quaternion<float> > v5;
//	v5 *= 2.5;
	v5 *= 2.f;
	

//	RNG::state_t data;
//	RNG r(data, gf, 0);
//	r.update(0.1f);

//	v2d<v3d<float> > v1;
//	v3d<v2d<float> > v2;

/*	v2 *= 1.;
	v1 *= 1.;


	v2 *= 1.f;
	v1 *= 1.f;

	v2 *= 1.L;
	v1 *= 1.L;

	v2 *= 1;
	v1 *= 1;

	v1 * 1.L;
	v2* 1.L;
*/




	//v3d<float> v4 = v3;

	boost::math::quaternion<double> q1;
	boost::math::quaternion<double> q2;

	q1 += q2;


	return 0;
}

