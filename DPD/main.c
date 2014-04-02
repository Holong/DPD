#include <stdio.h>
#include <stdlib.h>

#include "fixed.h"
#include "cordic.h"
#include "lookup.h"

#define INPUT_LEN		100
#define OUTPUT_LEN		INPUT_LEN

extern double I_phase[INPUT_LEN];
extern double Q_phase[INPUT_LEN];

extern FIXED K_FIXED;
extern FIXED INV_K_FIXED;
extern FIXED PRI_K_FIXED;
extern FIXED INV_PRI_K_FIXED;

extern FIXED A1_FIXED;	
extern FIXED A2_FIXED;	
extern FIXED A3_FIXED;	
extern FIXED A4_FIXED;	
extern FIXED A5_FIXED;	

extern FIXED P1_FIXED;	
extern FIXED P2_FIXED;	
extern FIXED P3_FIXED;	
extern FIXED P4_FIXED;	
extern FIXED P5_FIXED;	

int PRECISION;

void cal_dpd(FIXED amp, FIXED phase, FIXED *ret_amp, FIXED *ret_phase)
{
	FIXED amp_pow1 = amp;
	FIXED amp_pow2 = fixed_mul(amp, amp);
	FIXED amp_pow3 = fixed_mul(amp, amp_pow2);
	FIXED amp_pow4 = fixed_mul(amp, amp_pow3);
	FIXED amp_pow5 = fixed_mul(amp, amp_pow4);

	FIXED amp_unit5 = fixed_mul(A5_FIXED, amp_pow5);
	FIXED amp_unit4 = fixed_mul(A4_FIXED, amp_pow4);
	FIXED amp_unit3 = fixed_mul(A3_FIXED, amp_pow3);
	FIXED amp_unit2 = fixed_mul(A2_FIXED, amp_pow2);
	FIXED amp_unit1 = fixed_mul(A1_FIXED, amp_pow1);

	FIXED phase_unit5 = fixed_mul(P5_FIXED, amp_pow5);
	FIXED phase_unit4 = fixed_mul(P4_FIXED, amp_pow4);
	FIXED phase_unit3 = fixed_mul(P3_FIXED, amp_pow3);
	FIXED phase_unit2 = fixed_mul(P2_FIXED, amp_pow2);
	FIXED phase_unit1 = fixed_mul(P1_FIXED, amp_pow1);
	FIXED phase_unit0 = phase;

	*ret_amp = amp_unit5 + amp_unit4 + amp_unit3 + amp_unit2 + amp_unit1;
	*ret_phase = phase_unit5 + phase_unit4 + phase_unit3 + phase_unit2 + phase_unit1 + phase_unit0;
}

void dpd(double I, double Q, double* ret_I, double* ret_Q)
{
	FIXED before_DPD_amp;
	FIXED before_DPD_phase;

	FIXED after_DPD_amp;
	FIXED after_DPD_phase;

	FIXED I_fixed = float_to_fixed(I);
	FIXED Q_fixed = float_to_fixed(Q);

	before_DPD_amp = CORDIC_sqrt(I_fixed, Q_fixed);
	before_DPD_phase = CORDIC_atan(I_fixed, Q_fixed);

	cal_dpd(before_DPD_amp, before_DPD_phase, &after_DPD_amp, &after_DPD_phase);

	*ret_I = fixed_mul(before_DPD_amp, CORDIC_cos(before_DPD_phase));
	*ret_Q = fixed_mul(before_DPD_amp, CORDIC_sin(before_DPD_phase));
}

int main(void)
{
	double ret_I_phase[OUTPUT_LEN];
	double ret_Q_phase[OUTPUT_LEN];
	int i;

	PRECISION = 13;

	make_fixed_table();
	make_fixed_const();

	for(i = 0; i < INPUT_LEN; i++) {
		dpd(I_phase[i], Q_phase[i], &ret_I_phase[i], &ret_Q_phase[i]);
	}
	
	return 0;
}
