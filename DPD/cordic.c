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

struct rotation_info circular_table[TABLE_LENGTH] = {
	{0,	1.000000000000000,	45.000000000000000,	0.785398163397448},
	{1,	0.500000000000000,	26.565051177077990,	0.463647609000806},
	{2,	0.250000000000000,	14.036243467926477,	0.244978663126864},
	{3,	0.125000000000000,	7.125016348901798,	0.124354994546761},
	{4,	0.062500000000000,	3.576334374997352,	0.062418809995957},
	{5,	0.031250000000000,	1.789910608246069,	0.031239833430268},
	{6,	0.015625000000000,	0.895173710211074,	0.015623728620477},
	{7,	0.007812500000000,	0.447614170860553,	0.007812341060101},
	{8,	0.003906250000000,	0.223810500368538,	0.003906230131967},
	{9,	0.001953125000000,	0.111905677066207,	0.001953122516479},
	{10,	0.000976562500000,	0.055952891893804,	0.000976562189559},
	{11,	0.000488281250000,	0.027976452617004,	0.000488281211195},
	{12,	0.000244140625000,	0.013988227142265,	0.000244140620149},
	{13,	0.000122070312500,	0.006994113675353,	0.000122070311894},
	{14,	0.000061035156250,	0.003497056850704,	0.000061035156174},
	{15,	0.000030517578125,	0.001748528426980,	0.000030517578116},
	{16,	0.000015258789063,	0.000874264213694,	0.000015258789061},
	{17,	0.000007629394531,	0.000437132106872,	0.000007629394531},
	{18,	0.000003814697266,	0.000218566053439,	0.000003814697266},
	{19,	0.000001907348633,	0.000109283026720,	0.000001907348633},
	{20,	0.000000953674316,	0.000054641513360,	0.000000953674316},
	{21,	0.000000476837158,	0.000027320756680,	0.000000476837158},
	{22,	0.000000238418579,	0.000013660378340,	0.000000238418579},
	{23,	0.000000119209290,	0.000006830189170,	0.000000119209290},
	{24,	0.000000059604645,	0.000003415094585,	0.000000059604645},
	{25,	0.000000029802322,	0.000001707547293,	0.000000029802322},
	{26,	0.000000014901161,	0.000000853773646,	0.000000014901161},
	{27,	0.000000007450581,	0.000000426886823,	0.000000007450581},
	{28,	0.000000003725290,	0.000000213443412,	0.000000003725290},
	{29,	0.000000001862645,	0.000000106721706,	0.000000001862645},
	{30,	0.000000000931323,	0.000000053360853,	0.000000000931323}
};

struct rotation_info linear_table[TABLE_LENGTH] = {
	{0,	1.000000000000000,	45.000000000000000,	0.785398163397448},
	{1,	0.500000000000000,	26.565051177077990,	0.463647609000806},
	{2,	0.250000000000000,	14.036243467926477,	0.244978663126864},
	{3,	0.125000000000000,	7.125016348901798,	0.124354994546761},
	{4,	0.062500000000000,	3.576334374997352,	0.062418809995957},
	{5,	0.031250000000000,	1.789910608246069,	0.031239833430268},
	{6,	0.015625000000000,	0.895173710211074,	0.015623728620477},
	{7,	0.007812500000000,	0.447614170860553,	0.007812341060101},
	{8,	0.003906250000000,	0.223810500368538,	0.003906230131967},
	{9,	0.001953125000000,	0.111905677066207,	0.001953122516479},
	{10,	0.000976562500000,	0.055952891893804,	0.000976562189559},
	{11,	0.000488281250000,	0.027976452617004,	0.000488281211195},
	{12,	0.000244140625000,	0.013988227142265,	0.000244140620149},
	{13,	0.000122070312500,	0.006994113675353,	0.000122070311894},
	{14,	0.000061035156250,	0.003497056850704,	0.000061035156174},
	{15,	0.000030517578125,	0.001748528426980,	0.000030517578116},
	{16,	0.000015258789063,	0.000874264213694,	0.000015258789061},
	{17,	0.000007629394531,	0.000437132106872,	0.000007629394531},
	{18,	0.000003814697266,	0.000218566053439,	0.000003814697266},
	{19,	0.000001907348633,	0.000109283026720,	0.000001907348633},
	{20,	0.000000953674316,	0.000054641513360,	0.000000953674316},
	{21,	0.000000476837158,	0.000027320756680,	0.000000476837158},
	{22,	0.000000238418579,	0.000013660378340,	0.000000238418579},
	{23,	0.000000119209290,	0.000006830189170,	0.000000119209290},
	{24,	0.000000059604645,	0.000003415094585,	0.000000059604645},
	{25,	0.000000029802322,	0.000001707547293,	0.000000029802322},
	{26,	0.000000014901161,	0.000000853773646,	0.000000014901161},
	{27,	0.000000007450581,	0.000000426886823,	0.000000007450581},
	{28,	0.000000003725290,	0.000000213443412,	0.000000003725290},
	{29,	0.000000001862645,	0.000000106721706,	0.000000001862645},
	{30,	0.000000000931323,	0.000000053360853,	0.000000000931323}
};

struct rotation_info hyperbolic_table[TABLE_LENGTH] = {
	{0,	1.000000000000000,	45.000000000000000,	0.785398163397448},
	{1,	0.500000000000000,	26.565051177077990,	0.463647609000806},
	{2,	0.250000000000000,	14.036243467926477,	0.244978663126864},
	{3,	0.125000000000000,	7.125016348901798,	0.124354994546761},
	{4,	0.062500000000000,	3.576334374997352,	0.062418809995957},
	{5,	0.031250000000000,	1.789910608246069,	0.031239833430268},
	{6,	0.015625000000000,	0.895173710211074,	0.015623728620477},
	{7,	0.007812500000000,	0.447614170860553,	0.007812341060101},
	{8,	0.003906250000000,	0.223810500368538,	0.003906230131967},
	{9,	0.001953125000000,	0.111905677066207,	0.001953122516479},
	{10,	0.000976562500000,	0.055952891893804,	0.000976562189559},
	{11,	0.000488281250000,	0.027976452617004,	0.000488281211195},
	{12,	0.000244140625000,	0.013988227142265,	0.000244140620149},
	{13,	0.000122070312500,	0.006994113675353,	0.000122070311894},
	{14,	0.000061035156250,	0.003497056850704,	0.000061035156174},
	{15,	0.000030517578125,	0.001748528426980,	0.000030517578116},
	{16,	0.000015258789063,	0.000874264213694,	0.000015258789061},
	{17,	0.000007629394531,	0.000437132106872,	0.000007629394531},
	{18,	0.000003814697266,	0.000218566053439,	0.000003814697266},
	{19,	0.000001907348633,	0.000109283026720,	0.000001907348633},
	{20,	0.000000953674316,	0.000054641513360,	0.000000953674316},
	{21,	0.000000476837158,	0.000027320756680,	0.000000476837158},
	{22,	0.000000238418579,	0.000013660378340,	0.000000238418579},
	{23,	0.000000119209290,	0.000006830189170,	0.000000119209290},
	{24,	0.000000059604645,	0.000003415094585,	0.000000059604645},
	{25,	0.000000029802322,	0.000001707547293,	0.000000029802322},
	{26,	0.000000014901161,	0.000000853773646,	0.000000014901161},
	{27,	0.000000007450581,	0.000000426886823,	0.000000007450581},
	{28,	0.000000003725290,	0.000000213443412,	0.000000003725290},
	{29,	0.000000001862645,	0.000000106721706,	0.000000001862645},
	{30,	0.000000000931323,	0.000000053360853,	0.000000000931323}
};


struct lookup_info_fixed circular_table_fixed[TABLE_LENGTH];
struct lookup_info_fixed linear_table_fixed[TABLE_LENGTH];
struct lookup_info_fixed hyperbolic_table_fixed[TABLE_LENGTH];

FIXED K_FIXED;
FIXED INV_K_FIXED;
FIXED PRI_K_FIXED;
FIXED INV_PRI_K_FIXED;

FIXED A1_FIXED;	
FIXED A2_FIXED;	
FIXED A3_FIXED;	
FIXED A4_FIXED;	
FIXED A5_FIXED;	

FIXED P1_FIXED;	
FIXED P2_FIXED;	
FIXED P3_FIXED;	
FIXED P4_FIXED;	
FIXED P5_FIXED;	

FIXED PI_FIXED;
FIXED HALF_PI_FIXED;

extern int PRECISION;

void make_fixed_table(void)
{
	int i;
	for(i = 0; i < TABLE_LENGTH; i++) {
		circular_table_fixed[i].index = circular_table[i].index;
		circular_table_fixed[i].tangent = float_to_fixed(circular_table[i].tangent);
		circular_table_fixed[i].angle = float_to_fixed(circular_table[i].angle);
		circular_table_fixed[i].radian = float_to_fixed(circular_table[i].radian);

		linear_table_fixed[i].index = linear_table[i].index;
		linear_table_fixed[i].tangent =	float_to_fixed(linear_table[i].tangent);
		linear_table_fixed[i].angle = float_to_fixed(linear_table[i].angle);
		linear_table_fixed[i].radian = float_to_fixed(linear_table[i].radian);
		
		hyperbolic_table_fixed[i].index = hyperbolic_table[i].index;
		hyperbolic_table_fixed[i].tangent = float_to_fixed(hyperbolic_table[i].tangent);
		hyperbolic_table_fixed[i].angle = float_to_fixed(hyperbolic_table[i].angle);
		hyperbolic_table_fixed[i].radian = float_to_fixed(hyperbolic_table[i].radian);
	}
}

void make_fixed_const(void)
{
	K_FIXED = float_to_fixed(K);
	INV_K_FIXED = float_to_fixed(INV_K);
	PRI_K_FIXED = float_to_fixed(PRI_K);
	INV_PRI_K_FIXED = float_to_fixed(INV_PRI_K);

	A1_FIXED = float_to_fixed(A1);
	A2_FIXED = float_to_fixed(A2);
	A3_FIXED = float_to_fixed(A3);
	A4_FIXED = float_to_fixed(A4);
	A5_FIXED = float_to_fixed(A5);

	P1_FIXED = float_to_fixed(P1);
	P2_FIXED = float_to_fixed(P2);
	P3_FIXED = float_to_fixed(P3);
	P4_FIXED = float_to_fixed(P4);
	P5_FIXED = float_to_fixed(P5);
	
	PI_FIXED = float_to_fixed(PI);
	HALF_PI_FIXED = float_to_fixed(HALF_PI);
}

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


struct point cal_circular(struct point p0, mode cal_mode)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;
	for(i = 0; i < PRECISION; i++) {
		
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
	
struct point cal_linear(struct point p0, mode cal_mode)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;
	
	for(i = 0; i < PRECISION; i++) {

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
	
struct point cal_hyperbolic(struct point p0, mode cal_mode)
{
	struct point pt0;
	struct point pt1 = p0;
	int i;
	int d;

	for(i = 0; i < PRECISION; i++) {
		
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
	
struct point generalized_cordic(struct point p0, type cal_type, mode cal_mode)
{	
	struct point result;

	switch(cal_type) {
		case CIRCULAR:
			result = cal_circular(p0, cal_mode);
			break;
		case LINEAR:
			result = cal_linear(p0, cal_mode);
			break;
		case HYPERBOLIC:
			result = cal_hyperbolic(p0, cal_mode);
			break;
	}

	return result;
}

FIXED CORDIC_cos_sin(FIXED theta, int sel)
{
	struct point pt0;
	struct point result;
	int quadrant;

	if(theta <= HALF_PI_FIXED && theta >= -1 * HALF_PI_FIXED) {
		quadrant = 1;
		pt0.z = theta;
	}
	else if(theta > HALF_PI_FIXED) {
		quadrant = 2;
		pt0.z = PI_FIXED - theta;
	}
	else {
		quadrant = 3;
		pt0.z = PI_FIXED + theta;
	}

	pt0.x = INV_K_FIXED;
	pt0.y = 0;

	result = generalized_cordic(pt0, CIRCULAR, ROTATION);

	if(sel == 0 && quadrant == 1)
		return result.x;
	else if(sel == 0 && quadrant != 1)
		return -1 * result.x;
	else if(sel != 0 && quadrant == 3)
		return -1 * result.y;
	else
		return result.y;
}

FIXED CORDIC_atan(FIXED x, FIXED y)
{
	struct point pt0;
	struct point result;

	pt0.x = x;
	pt0.y = y;
	pt0.z = 0;
	result = generalized_cordic(pt0, CIRCULAR, VECTORING);

	return result.z;
}


FIXED CORDIC_sqrt(FIXED x, FIXED y)
{
	struct point pt0;
	struct point result;

	if(x > 0)
		pt0.x = x;
	else
		pt0.x = -1 * x;

	if(y > 0)
		pt0.y = y;
	else
		pt0.y = -1 * y;
	pt0.z = 0;

	result = generalized_cordic(pt0, CIRCULAR, VECTORING);

	return fixed_mul(INV_K_FIXED, result.x);
}
