

#ifndef SIMULATEDANNEALINGALGORITHM_H
#define	SIMULATEDANNEALINGALGORITHM_H

#include "../Headers/SolvObject.hpp"
#include <vector>
#include <bitset>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int simulatedAnnealingOriginal(SolvObject* initState, float initTemp, unsigned int neighbourBound, unsigned short nifsao, float trfsao, int seed);



#endif	/* SIMULATEDANNEALINGALGORITHM_H */

