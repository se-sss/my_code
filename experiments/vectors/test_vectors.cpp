// vectors.cpp : Defines the entry point for the console application.
//

#include "v2d.h"
#include "v3d.h"
#include <boost/mpl/list.hpp>
typedef boost::mpl::list<
		v2d<double>, v3d<double>
    > types;

//#include <boost/math/quaternion.hpp>
#include "quaternion.h"
#include <complex>
#include "tensor.h"

#include "TwoStateValue.h"

int main(int argc, char* argv[])
{
	matrix<5, 10, float> p;
	p[2][4][5][3][5] = 2.f;

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

