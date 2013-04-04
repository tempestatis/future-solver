/* 
 * File:   ILS.h
 * Author: tobias
 *
 * Created on 4. April 2013, 17:57
 */

#ifndef ILS_H
#define	ILS_H

#include <iostream>
#include "SolvObject.hpp"

int doILS(SolvObject* state);

bool localSearch(unsigned int neighbours, unsigned int satisfiedClauses, SolvObject* state);


#endif	/* ILS_H */

