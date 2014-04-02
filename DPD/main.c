#include <stdio.h>
#include <stdlib.h>

#include "fixed.h"
#include "cordic.h"

#define INPUT_LEN		100
#define OUTPUT_LEN		INPUT_LEN
#define PRECISION		13

extern double I_phase[INPUT_LEN];
extern double Q_phase[INPUT_LEN];

void cal_dpd(double amp, double phase, double *ret_amp, double *ret_phase)
{
}

void dpd(double I, double Q, double* ret_I, double* ret_Q)
{
	double before_DPD_amp;
	double before_DPD_phase;

	double after_DPD_amp;
	double after_DPD_phase;

	FIXED I_fixed = float_to_fixed(I, PRECISION);

	before_DPD_amp = CORDIC_sqrt_float(I, Q, PRECISION);
	before_DPD_phase = CORDIC_atan_float(I, Q, PRECISION);

	cal_dpd(before_DPD_amp, before_DPD_phase, &after_DPD_amp, &after_DPD_phase);

	*ret_I = before_DPD_amp * CORDIC_cos_float(before_DPD_phase, PRECISION);
	*ret_Q = before_DPD_amp * CORDIC_sin_float(before_DPD_phase, PRECISION);
}

int main(void)
{
	double ret_I_phase[OUTPUT_LEN];
	double ret_Q_phase[OUTPUT_LNE];

	for(i = 0; i < INPUT_LEN; i++) {
		dpd(I_phase[i], Q_phase[i], &ret_I_phase[i], &ret_Q_phase[i]);
	}
	
	return 0;
}
