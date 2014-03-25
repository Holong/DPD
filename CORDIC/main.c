#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "lookup.h"
#include "input.h"
#include "cordic.h"
#include "fixed.h"

struct rotation_info circular_table[TABLE_LENGTH] = {
	{0, 	1, 		45,		0.78539816},
	{1, 	0.5, 		26.56505118,	0.46364760},
	{2, 	0.25,		14.03624347,	0.24497866},
	{3,	0.125,		7.125016349,	0.12435499},
	{4,	0.0625,		3.576334375,	0.06241880},
	{5,	0.03125,	1.789910608,	0.03123983},
	{6,	0.015625,	0.89517371,	0.01562372},
	{7,	0.0078125,	0.447614171,	0.00781234},
	{8,	0.00390625,	0.2238105,	0.00390623},
	{9,	0.001953125,	0.111905677,	0.00195312}
};

struct rotation_info linear_table[TABLE_LENGTH] = {
	{0, 	1, 		45,		0.78539816},
	{1, 	0.5, 		26.56505118,	0.46364760},
	{2, 	0.25,		14.03624347,	0.24497866},
	{3,	0.125,		7.125016349,	0.12435499},
	{4,	0.0625,		3.576334375,	0.06241880},
	{5,	0.03125,	1.789910608,	0.03123983},
	{6,	0.015625,	0.89517371,	0.01562372},
	{7,	0.0078125,	0.447614171,	0.00781234},
	{8,	0.00390625,	0.2238105,	0.00390623},
	{9,	0.001953125,	0.111905677,	0.00195312}
};

struct rotation_info hyperbolic_table[TABLE_LENGTH] = {
	{0, 	1, 		45,		0.78539816},
	{1, 	0.5, 		26.56505118,	0.46364760},
	{2, 	0.25,		14.03624347,	0.24497866},
	{3,	0.125,		7.125016349,	0.12435499},
	{4,	0.0625,		3.576334375,	0.06241880},
	{5,	0.03125,	1.789910608,	0.03123983},
	{6,	0.015625,	0.89517371,	0.01562372},
	{7,	0.0078125,	0.447614171,	0.00781234},
	{8,	0.00390625,	0.2238105,	0.00390623},
	{9,	0.001953125,	0.111905677,	0.00195312}
};

struct lookup_info_fixed circular_table_fixed[TABLE_LENGTH];
struct lookup_info_fixed linear_table_fixed[TABLE_LENGTH];
struct lookup_info_fixed hyperbolic_table_fixed[TABLE_LENGTH];

int main(void) {
	int i;
	int precision;

	printf("========= Make Input Vectors ==========\n");
	srand((int)time(NULL));
	for(i = 0; i < TEST_VECTOR_LENGTH*2; i++)
	{
		double num = rand()%100 + 1;
		double denom = rand()%10 + 1;
		double value = num/denom;
		
		if(i%2)
			test_vector_for_sqrt[i/2].x = value;
		else
			test_vector_for_sqrt[i/2].y = value;
	}

	for(i = 0; i < TEST_VECTOR_LENGTH; i++)
	{
		int angle_int = rand()%90;
		double angle_deci = rand()%100 * 0.01;

		double angle = (double)angle_int + angle_deci;

		test_vector_for_tri[i] = angle * PI / 180 ;
	}

	printf("========= Make ans_vectors for comparison ============\n");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)
	{
		double xx = pow(test_vector_for_sqrt[i].x, 2);
		double yy = pow(test_vector_for_sqrt[i].y, 2);

		answer_vector_for_sqrt[i] = sqrt(xx + yy);
		answer_vector_for_cos[i] = cos(test_vector_for_tri[i]);
		answer_vector_for_sin[i] = sin(test_vector_for_tri[i]);
	}

	printf("========== Set a precision for cal & translate LUT ================\n");
	printf("Wanted precision : ");
	scanf("%d", &precision);

	for(i = 0; i < TABLE_LENGTH; i++) {
		circular_table_fixed[i].index = circular_table[i].index;
		circular_table_fixed[i].tangent =
			float_to_fixed(circular_table[i].tangent, precision);
		circular_table_fixed[i].angle =
			float_to_fixed(circular_table[i].angle, precision);
		circular_table_fixed[i].radian =
			float_to_fixed(circular_table[i].radian, precision);

		linear_table_fixed[i].index = linear_table[i].index;
		linear_table_fixed[i].tangent =
			float_to_fixed(linear_table[i].tangent, precision);
		linear_table_fixed[i].angle =
			float_to_fixed(linear_table[i].angle, precision);
		linear_table_fixed[i].radian =
			float_to_fixed(linear_table[i].radian, precision);
		
		hyperbolic_table_fixed[i].index = hyperbolic_table[i].index;
		hyperbolic_table_fixed[i].tangent =
			float_to_fixed(hyperbolic_table[i].tangent, precision);
		hyperbolic_table_fixed[i].angle =
			float_to_fixed(hyperbolic_table[i].angle, precision);
		hyperbolic_table_fixed[i].radian =
			float_to_fixed(hyperbolic_table[i].radian, precision);
	}
		

	printf("========= Test square root ===========\n");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)
	{
	//	CORDIC_answer_vector_for_sqrt[i] = CORDIC_sqrt_float(test_vector_for_sqrt[i].x, test_vector_for_sqrt[i].y, precision);
		CORDIC_answer_vector_for_cos[i] = CORDIC_cos_float(test_vector_for_tri[i], precision);
		CORDIC_answer_vector_for_sin[i] = CORDIC_sin_float(test_vector_for_tri[i], precision);
	}

	printf("========= Verify test_vectors ====================\n");
	{
		/*
		double sum_for_sqrt = 0;
		double sum_for_cos = 0;
		double sum_for_sin = 0;

		double std_sqrt = 0;
		double std_cos = 0;
		double std_sin = 0;

		for(i = 0; i < TEST_VECTOR_LENGTH; i++)
		{
			sum_for_sqrt += pow(answer_vector_for_sqrt[i] - CORDIC_answer_vector_for_sqrt[i], 2);
			sum_for_cos += pow(answer_vector_for_cos[i] - CORDIC_answer_vector_for_cos[i], 2);
			sum_for_sin += pow(answer_vector_for_sin[i] - CORDIC_answer_vector_for_sin[i], 2);
		}

		std_sqrt = sqrt(sum_for_sqrt/TEST_VECTOR_LENGTH);
		std_cos = sqrt(sum_for_cos/TEST_VECTOR_LENGTH);
		std_sin = sqrt(sum_for_sin/TEST_VECTOR_LENGTH);

		printf("Standard deviation of sqrt : %lf \n", std_sqrt);
		printf("Standard deviation of cos : %lf \n", std_cos);
		printf("Standard deviation of sin : %lf \n", std_sin);
		*/

		for(i = 0; i < TEST_VECTOR_LENGTH; i++)
		{
			printf("[%d : %lf]\n", i, answer_vector_for_cos[i] - CORDIC_answer_vector_for_cos[i]);
		}
	}
	
	return 0;
}
