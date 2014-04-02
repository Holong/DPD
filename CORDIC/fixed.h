#ifndef __FIXED_H__
#define __FIXED_H__

typedef int	FIXED;

#define fixed_to_float(fixed_num, precision)	((fixed_num)/(double)(1 << (precision)))
FIXED float_to_fixed(double float_num, int precision);

#endif
