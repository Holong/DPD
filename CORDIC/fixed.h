#ifndef __FIXED_H__
#define __FIXED_H__

typedef int	FIXED;

#define fixed_to_float(fixed_num, precision)	((fixed_num)/(double)(1 << (precision)))
FIXED float_to_fixed(double float_num, int precision)
{
	int int_part = (int)float_num;
	double frac_part = float_num - (double)int_part;
	int frac_part_conv;

	FIXED result;
		
	int_part = int_part << precision;
	frac_part_conv = (int)(frac_part * (1 << precision));
	result = int_part + frac_part_conv;

	return result;
}

#endif
