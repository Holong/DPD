#ifndef __FIXED_H__
#define __FIXED_H__

typedef int	FIXED;

#define fixed_to_float(fixed_num)	((fixed_num)/(double)(1 << (PRECISION)))
FIXED float_to_fixed(double float_num);

#define fixed_mul(num1, num2)		(((num1) * (num2)) >> PRECISION)

#endif
