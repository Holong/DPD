#include "fixed.h"
#include "lookup.h"


struct point {
	FIXED x;
	FIXED y;
	FIXED z;
};

typedef enum __type {
	CIRCULAR,
	LINEAR,
	HYPERBOLIC
} type;

typedef enum __mode {
	ROTATION,
	VECTORING
} mode;

extern struct lookup_info_fixed circular_table_fixed[TABLE_LENGTH];
extern struct lookup_info_fixed linear_table_fixed[TABLE_LENGTH];
extern struct lookup_info_fixed hyperbolic_table_fixed[TABLE_LENGTH];

int select_direction(mode cal_mode, struct point pt)
{
	int d;

	if(cal_mode == ROTATION)
		if((int)pt.z > 0)
			d = 1;
		else
			d = -1;
	else
		if(((int)pt.x > 0 && (int)pt.y > 0) || ((int)pt.x < 0 && (int)pt.y < 0))
			d = -1;
		else
			d = 1;

	return d;
}


struct point cal_circular(struct point p0, mode cal_mode, int iterations)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;
	for(i = 0; i < iterations; i++) {
		
		pt0 = pt1;
		d = select_direction(cal_mode, pt0);
		
		if(d > 0) {
			pt1.x = pt0.x - (pt0.y >> i);
			pt1.y = pt0.y + (pt0.x >> i);
			pt1.z = pt0.z - circular_table_fixed[i].radian;
		}
		else {
			pt1.x = pt0.x + (pt0.y >> i);
			pt1.y = pt0.y - (pt0.x >> i);
			pt1.z = pt0.z + circular_table_fixed[i].radian;
		}
	}

	return pt1;
}
	
struct point cal_linear(struct point p0, mode cal_mode, int iterations)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;
	
	for(i = 0; i < iterations; i++) {

		pt0 = pt1;
		d = select_direction(cal_mode, pt0);
		
		if(d > 0) {
			pt1.x = pt0.x;
			pt1.y = pt0.y + (pt0.x >> i);
			pt1.z = pt0.z - linear_table_fixed[i].tangent;
		}
		else {
			pt1.x = pt0.x;
			pt1.y = pt0.y - (pt0.x >> i);
			pt1.z = pt0.z + linear_table_fixed[i].tangent;
		}
	}

	return pt1;
}
	
struct point cal_hyperbolic(struct point p0, mode cal_mode, int iterations)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;

	for(i = 0; i < iterations; i++) {
		
		pt0 = pt1;
		d = select_direction(cal_mode, pt0);
		
		if(d > 0) {
			pt1.x = pt0.x + (pt0.y >> i);
			pt1.y = pt0.y + (pt0.x >> i);
			pt1.z = pt0.z - hyperbolic_table_fixed[i].radian;
		}
		else {
			pt1.x = pt0.x + (pt0.y >> i);
			pt1.y = pt0.y + (pt0.x >> i);
			pt1.z = pt0.z + hyperbolic_table_fixed[i].radian;
		}
	}

	return pt1;
}
	
struct point generalized_cordic(struct point p0, type cal_type,
		mode cal_mode, int precision)
{	
	struct point result;

	switch(cal_type) {
		case CIRCULAR:
			result = cal_circular(p0, cal_mode, precision);
			break;
		case LINEAR:
			result = cal_linear(p0, cal_mode, precision);
			break;
		case HYPERBOLIC:
			result = cal_hyperbolic(p0, cal_mode, precision);
			break;
	}

	return result;
}

FIXED CORDIC_cos_sin(FIXED theta, int precision, int sel)
{
	struct point pt0;
	struct point result;

	pt0.x = float_to_fixed(INV_K, precision);
	pt0.y = 0;
	pt0.z = theta;

	result = generalized_cordic(pt0, CIRCULAR, ROTATION, precision);

	if(sel == 0)
		return result.x;
	else
		return result.y;
}

FIXED CORDIC_atan(FIXED x, FIXED y, int precision)
{
	struct point pt0;
	struct point result;

	pt0.x = x;
	pt0.y = y;
	pt0.z = 0;
	result = generalized_cordic(pt0, CIRCULAR, VECTORING, precision);

	return result.z;
}


FIXED CORDIC_sqrt(FIXED x, FIXED y, int precision)
{
	struct point pt0;
	struct point result;

	pt0.x = x;
	pt0.y = y;
	pt0.z = 0;
	result = generalized_cordic(pt0, CIRCULAR, VECTORING, precision);

	pt0.x = result.x;
	pt0.y = 0;
	pt0.z = float_to_fixed(INV_K, precision);
	result = generalized_cordic(pt0, LINEAR, ROTATION, precision);

	return result.y;
}

double CORDIC_sqrt_float(double x, double y, int precision)
{
	FIXED x_fix = float_to_fixed(x, precision);
	FIXED y_fix = float_to_fixed(y, precision);

	FIXED ret_value = CORDIC_sqrt(x_fix, y_fix, precision);

	return fixed_to_float(ret_value, precision);
}

double CORDIC_atan_float(double x, double y, int precision)
{
	FIXED x_fix = float_to_fixed(x, precision);
	FIXED y_fix = float_to_fixed(y, precision);

	FIXED ret_value = CORDIC_atan(x_fix, y_fix, precision);

	return fixed_to_float(ret_value, precision);
}
	
double CORDIC_tri_float(double theta, int precision, int sel)
{
	FIXED theta_fix = float_to_fixed(theta, precision);

	FIXED ret_value = CORDIC_cos_sin(theta_fix, precision, sel);

	return fixed_to_float(ret_value, precision);
}
