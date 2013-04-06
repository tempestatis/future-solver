/* 
 * File:   SimulatedAnnealingLessFlips.h
 * Author: tobias
 *
 * Created on 4. April 2013, 17:47
 */

#ifndef SIMULATEDANNEALINGLESSFLIPS_H
#define	SIMULATEDANNEALINGLESSFLIPS_H

#include "../Headers/SolvObject.hpp"
#include <math.h>

int simulatedAnnealingLessFlips(SolvObject* state, float initTemp, unsigned int neighbourBound, unsigned short nifsalf, float trfsalf, int seed );



#endif	/* SIMULATEDANNEALINGLESSFLIPS_H */

