#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "lookup.h"
#include "input.h"

int main(void) {
	int i;
	
	printf("Print CORDIC angle table\n");
	printf("[index   tangent      radian ]\n");
	for(i = 0; i < TABLE_LENGTH; i++)
	{
		printf("[%2d : %10lf, %10lf]\n", rotation_table[i].index, rotation_table[i].tangent, rotation_table[i].radian);
	}

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
		int angle_int = rand()%360;
		double angle_deci = rand()%100 * 0.01;

		double angle = (double)angle_int + angle_deci;

		test_vector_for_tri[i] = angle * PI / 180 ;
	}

	printf("========= Make ans_vectors for comparison ============\n");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)
	{
		double xx = pow(test_vector_for_sqrt[i].x, 2);
		double yy = pow(test_vector_for_sqrt[i].y, 2);

		float_answer_vector_for_sqrt[i] = sqrt(xx + yy);
		float_answer_vector_for_cos[i] = cos(test_vector_for_tri[i]);
		float_answer_vector_for_sin[i] = sin(test_vector_for_tri[i]);
	}
/*	
	printf("========= Test square root ===========\n");
	for(i = 0; i < TEST_VECTOR_LENGTH; i++)
	{
		CORDIC_answer_vector_for_sqrt[i] = CORDIC_sqrt(test_vector_for_sqrt[i].x, test_vector_for_sqrt[i].y);
		CORDIC_answer_vector_for_cos[i] = CORDIC_cos(test_vector_for_tri[i]);
		CORDIC_answer_vector_for_sin[i] = CORDIC_sin(test_vector_for_tri[i]);
	}

*/
	
	return 0;
}
