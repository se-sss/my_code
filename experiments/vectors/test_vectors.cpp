// vectors.cpp : Defines the entry point for the console application.
//

#include "v2d.h"
#include "v3d.h"
#include <boost/math/quaternion.hpp>
#include "quaternion.h"
#include <complex>
//#include "tensor.h"

#include <boost/numeric/ublas/vector.hpp>
#include "TwoStateValue.h"

int main(int argc, char* argv[])
{

	v3d<double> v1(1., 2., 3.);
	v1 *= 1.f;
	v1 *= 2.;
	v1 *= 3.L;

	-v1;
	v3d<double> vvv(v1);
	v1=vvv;

	v3d<v2d<float> > v2;
	v2 *= 2;
	v2 *= 3.L;

	v3d<quaternion<float> > v3;
	v3 *= 2.;
	v3 *= 3.f;

	v3d<quaternion<long double> > v4;
	v4 *= 2.;
	v4 *= 3.f;


	v3d<boost::math::quaternion<float> > v5;
	v5 *= 2.5;
	v5 *= 2.f;

	v3d<std::complex<float> > v6;
	v6 *= 2.5;
	v6 *= 2.f;

	 
	v6 = v6;
	
/*
	boost::numeric::ublas::vector<double> v7(3);

	boost::numeric::ublas::vector<boost::math::quaternion<std::complex<float> > > v8(3);
	v8 *= 2.f;

	boost::numeric::ublas::vector<long double> v9(3);
*/



//	matrix<5, 10, float> p;
//	p[2][4][5][3][5] = 2.f;

TwoStateValue<double> data1;
TwoStateValue<double> data2(data1);
data1 = 2.f;
data1.commit();
double tmp = data1();
data2 += tmp;
data1.commit();
data2.commit();
data2.direct_access_to_new_value() = 5.;
data2.commit();
return 0;
}

