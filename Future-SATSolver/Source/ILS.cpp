#include "../Headers/ILS.h"

int doILS(SolvObject* state, unsigned int neighbours){
	
	
	
	
	if (localSearch(neighbours,state->getNumberOfSatisfiedClauses(),state) == 1){
		// kein besserer Nachbar wurde gefunden
		
		
	} else {
		// es wurde ein besserer Nachbar gefunden
		
		
	}
	
	return 0;
	
}






bool localSearch(unsigned int neighbours, unsigned int satisfieldClausesFromFurtherState, SolvObject* state){
	
	unsigned int flips = 1;
	unsigned int tempSClauses;
	bool foundBetterCandidate = 0;
	
	
	// flipper copy for save the best flipper (neighbour) in local search
	flippercopy bestFlipper;
	
	// initial flipper copy
	state->initializeCopyFlipper(bestFlipper);
	
	// reset flippers, for right functionality of this function
	state->resetFlipper();
	
	for (unsigned int cycle = 0; cycle < neighbours; cycle++){
		
		
		// find a new flipper (neighbour)
		while(state->createNeighbour(flips) > 0){
			
			if (flips < state->getListOfVariables()->size()){
				
				flips++;
				state->resetFlipper();
				
			}
			
		}
		
		// flip variables by founded flipper vector
		state->flipVariablesByFlipperVector();
		
		// check whether candidate is better than further candidate
		tempSClauses = state->getNumberOfSatisfiedClauses();
		
		
		
		if (tempSClauses > satisfieldClausesFromFurtherState){
			
			// set flag
			foundBetterCandidate = 1;
			
			// set as new measure
			satisfieldClausesFromFurtherState = tempSClauses;
			
			// save flipper for using it after local search
			state->copyFlipper(bestFlipper);
			
		}
		
		// flip back to look for next candidate
		state->flipVariablesByFlipperVector();
		
		
		
		
		
	}
	
	// end of local search
	
	// if a better solution candidate was found flip variables to this state and return 0 for success or 1 for fail
	if (foundBetterCandidate == 1){
		
		// use  best flipper ...
		state->useFlipperCopy(bestFlipper);
		
		// for flipping variables
		state->flipVariablesByFlipperVector();
		
		return 0;
		
	} else{
		
		// eventually you have to do a random jump
		return 1;
		
	}
}
	