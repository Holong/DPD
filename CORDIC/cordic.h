#ifndef __CORDIC_H__
#define __CORDIC_H__

#define CORDIC_cos_float(theta, precision)	CORDIC_tri_float(theta, precision, 0)
#define CORDIC_sin_float(theta, precision)	CORDIC_tri_float(theta, precision, 1)

double CORDIC_sqrt_float(double x, double y, int precision);
double CORDIC_tri_float(double theta, int precision, int sel);

#endif
