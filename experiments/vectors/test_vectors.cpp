// vectors.cpp : Defines the entry point for the console application.
//

//#include "v2d.h"
//#include "v3d.h"
//#include <boost/math/quaternion.hpp>
//#include "quaternion.h"
//#include <complex>
//#include "tensor.h"

//#include <boost/numeric/ublas/vector.hpp>
//#include "TwoStateValue.h"

#include <se/geometry/vec.h>

int main(int argc, char* argv[])
{
	using namespace se::geometry;
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




	return 0;
}

