#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "lookup.h"
#include "input.h"
#include "cordic.h"
#include "fixed.h"

#define PRECISION		13

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

int main(int argc, char* argv[]) {
	int i;
	int precision;

	printf(" Make Input Vectors ................................. ");
	srand((int)time(NULL));
	for(i = 0; i < TEST_VECTOR_LENGTH*2; i++) {
		double integer = rand()%10;
		double fraction = rand()%10000;
		double value = integer + fraction/10000;
		
		if(i%2)
			test_vector_for_sqrt[i/2].x = value;
		else
			test_vector_for_sqrt[i/2].y = value;
	}
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)	{
		int angle_int = rand()%90;
		double angle_deci = rand()%100 * 0.01;

		double angle = (double)angle_int + angle_deci;
		
		if(i % 2 == 0)
			test_vector_for_tri[i] = angle * PI / 180 ;
		else
			test_vector_for_tri[i] = -1 * angle * PI / 180;
	}
	printf("[Pass]\n");

	printf(" Make ans_vectors for comparison .................... ");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)	{
		double xx = pow(test_vector_for_sqrt[i].x, 2);
		double yy = pow(test_vector_for_sqrt[i].y, 2);

		answer_vector_for_sqrt[i] = sqrt(xx + yy);
		answer_vector_for_atan[i] = atan(test_vector_for_sqrt[i].y/test_vector_for_sqrt[i].x);
		answer_vector_for_cos[i] = cos(test_vector_for_tri[i]);
		answer_vector_for_sin[i] = sin(test_vector_for_tri[i]);
	}
	printf("[Pass]\n");

	printf(" Set a precision for cal & translate LUT ............ ");

	/*
	if(argc != 2) {
		printf("[Fail]\n");
		printf(" usage : test precision\n");
		return 0;
	}
	*/
//	else {
		precision = PRECISION;
		if(precision >= 25) {
			printf("[Fail]\n");
			printf(" 1 <= precision <= 25 \n");
			return 0;
		}

		printf("[Pass]\n");
		printf(" Precision : %d\n", precision);
//	}

	for(i = 0; i < TABLE_LENGTH; i++) {
		circular_table_fixed[i].index = circular_table[i].index;
		circular_table_fixed[i].tangent = float_to_fixed(circular_table[i].tangent, precision);
		circular_table_fixed[i].angle = float_to_fixed(circular_table[i].angle, precision);
		circular_table_fixed[i].radian = float_to_fixed(circular_table[i].radian, precision);

		linear_table_fixed[i].index = linear_table[i].index;
		linear_table_fixed[i].tangent =	float_to_fixed(linear_table[i].tangent, precision);
		linear_table_fixed[i].angle = float_to_fixed(linear_table[i].angle, precision);
		linear_table_fixed[i].radian = float_to_fixed(linear_table[i].radian, precision);
		
		hyperbolic_table_fixed[i].index = hyperbolic_table[i].index;
		hyperbolic_table_fixed[i].tangent = float_to_fixed(hyperbolic_table[i].tangent, precision);
		hyperbolic_table_fixed[i].angle = float_to_fixed(hyperbolic_table[i].angle, precision);
		hyperbolic_table_fixed[i].radian = float_to_fixed(hyperbolic_table[i].radian, precision);
	}

	printf(" Cal sol by CORDIC .................................. ");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)	{
		CORDIC_answer_vector_for_sqrt[i] = CORDIC_sqrt_float(test_vector_for_sqrt[i].x, test_vector_for_sqrt[i].y, precision);
		CORDIC_answer_vector_for_atan[i] = CORDIC_atan_float(test_vector_for_sqrt[i].x, test_vector_for_sqrt[i].y, precision);
		CORDIC_answer_vector_for_cos[i] = CORDIC_cos_float(test_vector_for_tri[i], precision);
		CORDIC_answer_vector_for_sin[i] = CORDIC_sin_float(test_vector_for_tri[i], precision);
	}
	printf("[Pass]\n");

	printf(" Verify test_vectors ................................\n");

	{
		double sum_for_sqrt = 0;
		double sum_for_atan = 0;
		double sum_for_cos = 0;
		double sum_for_sin = 0;

		double std_sqrt = 0;
		double std_atan = 0;
		double std_cos = 0;
		double std_sin = 0;

		for(i = 0; i < TEST_VECTOR_LENGTH; i++)
		{
			sum_for_sqrt += pow(answer_vector_for_sqrt[i] - CORDIC_answer_vector_for_sqrt[i], 2);
			sum_for_atan += pow(answer_vector_for_atan[i] - CORDIC_answer_vector_for_atan[i], 2);
			sum_for_cos += pow(answer_vector_for_cos[i] - CORDIC_answer_vector_for_cos[i], 2);
			sum_for_sin += pow(answer_vector_for_sin[i] - CORDIC_answer_vector_for_sin[i], 2);
		}

		std_sqrt = sqrt(sum_for_sqrt/TEST_VECTOR_LENGTH);
		std_atan = sqrt(sum_for_atan/TEST_VECTOR_LENGTH);
		std_cos = sqrt(sum_for_cos/TEST_VECTOR_LENGTH);
		std_sin = sqrt(sum_for_sin/TEST_VECTOR_LENGTH);

		printf(" Standard deviation of sqrt : %lf \n", std_sqrt);
		printf(" Standard deviation of atan : %lf \n", std_atan);
		printf(" Standard deviation of cos : %lf \n", std_cos);
		printf(" Standard deviation of sin : %lf \n", std_sin);
/*
		for(i = 0; i < TEST_VECTOR_LENGTH; i++)
		{
			printf("[%d : %lf]\n", i, answer_vector_for_sqrt[i] - CORDIC_answer_vector_for_sqrt[i]);
			printf("[%d : %lf]\n", i, answer_vector_for_atan[i] - CORDIC_answer_vector_for_atan[i]);
			printf("[%d : %lf]\n", i, answer_vector_for_cos[i] - CORDIC_answer_vector_for_cos[i]);
			printf("[%d : %lf]\n", i, answer_vector_for_sin[i] - CORDIC_answer_vector_for_sin[i]);
		}
*/
	}
	
	while(1);

	return 0;
}
