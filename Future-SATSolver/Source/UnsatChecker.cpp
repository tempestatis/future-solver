#include <vector>

#include "../Headers/UnsatChecker.h"

bool checkUnsatisfiability(SolvObject* solvObj){
	
	
	unsigned int flips = 1;
	unsigned int numberOfVariables = solvObj->getListOfVariables()->size();
	unsigned int cycle = 0;
	
	// brute force check 
	while (1){
		
		while (solvObj->createNeighbour(flips) > 0){
			
			
			flips++;
			solvObj->resetFlipper();
					  
			if (flips > numberOfVariables){
				// unsat
				return 0;
			}
						  
		}
		
		cycle ++;
		
		solvObj->flipVariablesByFlipperVector();
		
		if (solvObj->getNumberOfSatisfiedClauses() == solvObj->getNumberOfClauses()){
			// sat
			
			return 1;
		}
		
		solvObj->flipVariablesByFlipperVector();
		
		
	}
	
	return 0;
}
