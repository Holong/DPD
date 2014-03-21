#include "fixed.h"

#define CORDIC_cos_float(theta, precision)	CORDIC_tri_float(theta, precision, CORDIC_cos)
#define CORDIC_sin_float(theta, precision)	CORDIC_tri_float(theta, precision, CORDIC_sin)

double CORDIC_sqrt_float(double x, double y, int precision)
{
	FIXED x_fix = float_to_fixed(x, precision);
	FIXED y_fix = float_to_fixed(y, precision);

	FIXED ret_value = CORDIC_sqrt(x_fix, y_fix, precisio);

	return fixed_to_float(ret_value, precision);
}
	
double CORDIC_tri_float(double theta, int precision, FIXED (*func)(FIXED, int))
{
	FIXED theta_fix = float_to_fixed(theta, precision);

	FIXED ret_value = func(theta_fix, precision);

	return fixed_to_float(ret_value, precision);
}

FIXED CORDIC_sqrt(FIXED x, FIXED y, int precision);
FIXED CORDIC_cos(FIXED theta, int precision);
FIXED CORDIC_sin(FIXED theta, int precision);
