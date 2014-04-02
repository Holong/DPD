#include "fixed.h"

extern int PRECISION;

FIXED float_to_fixed(double float_num)
{
	int int_part = (int)float_num;
	double frac_part = float_num - (double)int_part;
	int frac_part_conv;

	FIXED result;
		
	int_part = int_part << PRECISION;
	frac_part_conv = (int)(frac_part * (1 << PRECISION));
	result = int_part + frac_part_conv;

	return result;
}
