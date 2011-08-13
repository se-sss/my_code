#include "runge.h"
#include "../vectors/v2d.h"
#include "../vectors/v3d.h"
#include "../vectors/quaternion.h"

#include <boost/mpl/if.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/math/quaternion.hpp>
#include <complex>

typedef Runge4<double, v2d<v3d<double> > > RNG;

void gf(const RNG::time_t t, const RNG::state_t& v, RNG::state_t& result)
{
	return;
}

int main(int argc, char* argv[])
{
	RNG::state_t data;
	RNG r(data, gf, 0);
	r.update(0.1f);

	return 0;
}

