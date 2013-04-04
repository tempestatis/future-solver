/* 
 * File:   SimulatedAnnealingAlgorithm.h
 * Author: tobias
 *
 * Created on 22. März 2013, 15:49
 */

#ifndef SIMULATEDANNEALINGALGORITHM_H
#define	SIMULATEDANNEALINGALGORITHM_H

#include "../Headers/SolvObject.hpp"
#include <vector>
#include <bitset>
#include <time.h>

int simulatedAnnealingOriginal(SolvObject* initState, double initTemp, unsigned int neighbourBound);

int simulatedAnnealingLessFlips(SolvObject* initState, double initTemp, unsigned int neighbourBound);

#endif	/* SIMULATEDANNEALINGALGORITHM_H */

