#include <stdio.h>

#include "lookup.h"

int main(void) {
	int i;

	for(i = 0; i < TABLE_LENGTH; i++)
	{
		printf("%d, %lf, %lf\n", rotation_table[i].index, rotation_table[i].tangent, rotation_table[i].angle);
	}
	return 0;
}
