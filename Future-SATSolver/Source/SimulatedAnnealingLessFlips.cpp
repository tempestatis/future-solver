
#include "../Headers/SimulatedAnnealingLessFlips.h"

/*
 * implementation of simulated annealing algorithm with only 1 update per cycle
 */
int simulatedAnnealingLessFlips(SolvObject* state, float initTemp, unsigned int neighbourBound, unsigned short nifsalf, float trfsalf, int seed){
	
	// define cycle variable
	unsigned int lastChange = 1, cycle = 1;
	
	
	// variables for number of satisfied clauses
	int lastState = state->getNumberOfSatisfiedClauses();
	int currentState = 0;
	
	// number of variables
	unsigned int numberOfVariables = state->getListOfVariables()->size();
	
	double temp = initTemp;
	
	// start with 1 flip
	unsigned int flips = 1;
	
	long double funcResult = 0;
	double random = 0;
	
	unsigned int nNeighbour = 0;
	
	bool foundBetterNeighbour = 0;
	
	// copies of flipper for save state
	flippercopy worseFlipper, bestFlipper;
	
	// initialize structs
	state->initializeCopyFlipper(bestFlipper);
	state->initializeCopyFlipper(worseFlipper);
	
	// initialize random generator
	srand( seed ) ; 
	
	
	// get current state and save it as "last-state"
	lastState = state->getNumberOfSatisfiedClauses();
	
	// if solution was already found return successfully
	if (lastState == state->getNumberOfClauses())
		return 0;
	
	// loop until solution was found or it archieved restart criterion
	do {
		// check neighbours in given bound
		do{
			
			// create neighbour , if no neighbour have been created then increment flips 
			while(state->createNeighbour(flips) > 0){
				
				/* do not increasing flips 
				 * if number of flips are the same as number of variables
				*/
				if (flips < numberOfVariables){
					
					flips++;
					
					// after increasing flips flipper have to restart
					state->resetFlipper();
			
					
					
				}
			}
			
			// increment number of created neighbours
			nNeighbour++;
			
			
			// flip variables by flipper
			state->flipVariablesByFlipperVector();
			
			// get number of satisfied clauses by calculated neighbour
			currentState = state->getNumberOfSatisfiedClauses();
			
			// simulated annealing function
			funcResult = exp(((-lastState - currentState)/ temp));
			
			// random function
			random = (double)(rand() % 100000 + 1) / 100000;
			
			// if current assignment is better than last one save it
			if ((currentState > lastState)){
				
				
				// save better candidate
				state->copyFlipper(bestFlipper);
				
				// assign flag
				foundBetterNeighbour = 1;
				
				// update last state with current state
				lastState = currentState;
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses())
					return 0;
				
				
				
				
				
			} else if ((currentState < lastState) && (funcResult > random )){
				/* if current state is worse than last state
				 * , but SA function is satisfied then save worse neighbour
				*/
				
				
				// save worse candidate
				state->copyFlipper(worseFlipper);
				
				
				
			} 
				
			// reset variables to further state
			state->flipVariablesByFlipperVector();
			
				
				
		} while (nNeighbour < neighbourBound);
		
		// flip variables to best neighbour
		if (foundBetterNeighbour){

			// use best flipper ...
			state->useFlipperCopy(bestFlipper);
			
			// to flip variables
			state->flipVariablesByFlipperVector();
			
			foundBetterNeighbour = 0;
			
			lastChange = cycle;
			
			
			
			/* if all neighbours checked and no better candidate was found 
			* then leave plateau with worse candidate
			 * 
			 * if temp > 1 then it was possible to find a worse candidate 
			*/
		} else if (temp > 1){
			
			// use worse flipper ...
			state->useFlipperCopy(worseFlipper);
			
			
			// ... to flip variables
			state->flipVariablesByFlipperVector();
			
			
			
			lastState = state->getNumberOfSatisfiedClauses();
			
			lastChange = cycle;
			
		}
			
			
		// reset flipper in solv object
		state->resetFlipper();
		
		// begin new cycle
		cycle++;
		
		// restart after 10 cycles with no new neighbour
		if (cycle - lastChange > 10){
			
			return 1;
		}
			
		
		// increase neighbourhood bound
		neighbourBound  = neighbourBound + nifsalf*cycle;
		
		// begin at 0
		nNeighbour = 0;
		
		// calculate new temperature
		if (temp > 1)
			temp = temp - trfsalf;
		
		
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	
	
	
	return 0;	
	
}
