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

int simulatedAnnealing(SolvObject* initState, double initTemp, short neighbourBound);

#endif	/* SIMULATEDANNEALINGALGORITHM_H */

