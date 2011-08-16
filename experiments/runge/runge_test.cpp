#include "runge.h"

#include <se/geometry/vec.h>
#include <se/geometry/quaternion.h>
#include <boost/math/quaternion.hpp>
#include <complex>

using namespace se::geometry;

typedef Runge4<double, v3d<v3d<double> > > RNG;

void gf(const RNG::time_t t, const RNG::state_t& v, RNG::state_t& result)
{
	return;
}

class A
{
};

template<typename T>
void f(const T& a)
{
}

int main(int argc, char* argv[])
{
	f(A());

	RNG::state_t data;
	RNG r(data, gf, 0);
	r.update(0.1);

	return 0;
}

