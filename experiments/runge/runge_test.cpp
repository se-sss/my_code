#include "runge.h"

#include <se/geometry/vec.h>
#include <se/geometry/quaternion.h>
#include <boost/math/quaternion.hpp>
#include <complex>

using namespace se::geometry;

class Satellite
{
private:
	typedef vec<v3d<double>, 2> state_t; //v3d position and v3d velocity
	typedef Runge4<double, state_t > RNG;
	state_t state;
	RNG rng;

	struct f
	{
		void operator()(const RNG::time_t dt, const RNG::state_t& v, RNG::state_t& result)
		{
			const double gamma_m1_m2 = 100.;
			result[0] = v[1];

			const v3d<double>& r = v[0];
			result[1] =(-gamma_m1_m2 / (r, r)) * r.get_normalized();

		}
	};
	

public:
	Satellite():rng(state, f(), 0.)
	{
		v3d<double>& r = state[0];
		v3d<double>& v = state[1];

		r[0] = 100.;
		r[1] = 50.;
		r[2] = 0.;

		v[0] = -1.;
		v[1] = 2.;
		v[2] = 0.;

	}

	void update(double dt)
	{
		rng.update(dt);
	}

};

int main(int argc, char* argv[])
{
	Satellite satellite;

	while(true)
	{
		satellite.update(1.);
	}

	return 0;
}

