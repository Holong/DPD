#ifndef __CORDIC_H__
#define __CORDIC_H__

#define CORDIC_cos(theta)			CORDIC_cos_sin(theta, 0)
#define CORDIC_sin(theta)			CORDIC_cos_sin(theta, 1)

FIXED CORDIC_cos_sin(FIXED theta, int sel);
FIXED CORDIC_sqrt(FIXED x, FIXED y);
FIXED CORDIC_atan(FIXED x, FIXED y);

void make_fixed_table(void);
void make_fixed_const(void);

#endif
