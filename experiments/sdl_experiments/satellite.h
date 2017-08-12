#ifndef SATELLITE_H_INCLUDED
#define SATELLITE_H_INCLUDED

#include <se/ode/runge4.h>
#include <se/geometry/v3d.h>

using namespace se::geometry;
using namespace se::ode;

class Satellite
{
public:
	typedef vec<v3d<double>, 2> state_t; //v3d position and v3d velocity
private:
	typedef Runge4<double, state_t > RNG;
	state_t state;
	RNG rng;

	struct f
	{
		void operator()(const RNG::time_t dt, const RNG::state_t& v, RNG::state_t& result)
		{
			const double gamma_m1_m2 = 1000000.;
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

		v[0] = -10.;
		v[1] = 20.;
		v[2] = 0.;

	}

	void update(double dt)
	{
		rng.update(dt);
	}

	const state_t& get_state() const
	{
		return state;
	}

};
#endif
