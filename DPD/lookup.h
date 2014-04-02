#ifndef __LOOKUP_H__
#define __LOOKUP_H__

#include "fixed.h"

#define	TABLE_LENGTH		31
#define K			1.646760258121
#define INV_K			0.607252935008
#define PRI_K			0.828159360960
#define INV_PRI_K		1.207497067763

#define A1			1
#define A2			1
#define A3			1
#define A4			1
#define A5			1

#define P1			1
#define P2			1
#define P3			1
#define P4			1
#define P5			1


struct rotation_info {
	int index;
	double tangent;
	double angle;
	double radian;
};

struct lookup_info_fixed {
	int index;
	FIXED tangent;
	FIXED angle;
	FIXED radian;
};
#endif
