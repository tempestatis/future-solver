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
			cout << "flips: " << flips << endl;
			solvObj->resetFlipper();
					  
			if (flips > numberOfVariables){
				// unsat
				//cout << (cycle+1) << " combinations of variable assignments checked, no solution was found!" << endl;
				return 0;
			}
						  
		}
		
		cycle ++;
		if (cycle % 100000 == 0)
			cout << "cycle: " << cycle << endl;
		
		
		solvObj->flipVariablesByFlipperVector();
		//solvObj->printVariablesAssignment();
		//solvObj->printVariablesAssignment();
		
		if (solvObj->getNumberOfSatisfiedClauses() == solvObj->getNumberOfClauses()){
			// sat
			
			return 1;
		}
		
		solvObj->flipVariablesByFlipperVector();
		
		
	}
	
	return 0;
}
