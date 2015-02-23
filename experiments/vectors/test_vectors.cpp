// vectors.cpp : Defines the entry point for the console application.
//

//#include "v2d.h"
//#include "v3d.h"
#include <boost/math/quaternion.hpp>
#include <se/geometry/quaternion.h>
#include <complex>
//#include "tensor.h"

#include <boost/numeric/ublas/vector.hpp>
//#include "TwoStateValue.h"

#include <se/geometry/vec.h>
#include <complex>

using namespace se::geometry;

void test1()
{
	vec<float, 4> v1;
	vec<long double, 4> v2;
	vec<float, 4> v3 = v1;

	+v1;
	-v1;
	v1+v3;
	v1-v3;
	v1*=1.f;
	v1*=1.;

	v1 = v1*2.;
	v1 /= 5.L;
	v1 = (v1 / 5.) + v1;

	v1.normalize();
}

void test2()
{
	vec<std::complex<float>, 4> v1;
	v1[1] = std::complex<float>(1, 2);

	v1 / 3.;

	v1 *= std::complex<float>(1, 2);
	v1 * std::complex<float>(1, 2);

	v1 /= std::complex<float>(1, 2);
	v1 / std::complex<float>(1, 2);
}


template <typename T>
void test3()
{
	vec<T, 5> v1;

	v1 / 3.;

	v1 *= 3.L;
	v1 * 3.L;

	v1 /= 1;
	v1 / 3.;
}

int main(int argc, char* argv[])
{
	test1();
	test2();

	test3<boost::math::quaternion<float> >();
	return 0;
}

