

#ifndef ILS_H
#define	ILS_H

#include <iostream>
#include <climits>
#include "SolvObject.hpp"

//int doILS(SolvObject* state);

//bool localSearch(unsigned int neighbours, unsigned int satisfiedClauses, SolvObject* state);

bool localSearch(SolvObject* solvO, unsigned int neighbours, unsigned int satisfieldClausesFromFurtherState);

bool iteratedLocalSearchAlgorithm(SolvObject* solvO, int nils, unsigned short rfils, unsigned short ifrfils, int seed);

#endif	/* ILS_H */

