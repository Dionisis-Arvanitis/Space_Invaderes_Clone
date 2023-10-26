#include "util.h"

float rand0to1()
{
	return rand() / (float)RAND_MAX;
}

bool randomBool()
{
	return rand() > (RAND_MAX / 2);
}
