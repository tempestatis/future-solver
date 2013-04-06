#include "../Headers/SimulatedAnnealingOriginal.h"


/*
 * implementation of simulated annealing algorithm (several updates per cycle)
 */
int simulatedAnnealingOriginal(SolvObject* state, float initTemp, unsigned int neighbourBound, unsigned short nifsao, float trfsao, int seed){
	
	// define cycle variable
	unsigned int cycle = 1;
	
	
	// variables for number of satisfied clauses
	int lastState = state->getNumberOfSatisfiedClauses();
	
	int currentState = 0;
	
	// number of variables
	unsigned int numberOfVariables = state->getListOfVariables()->size();
	
	float temp = initTemp;
	
	// start with 1 flip
	unsigned int flips = 1;
	
	long double funcResult = 0;
	double random = 0;
	
	unsigned int nNeighbour = 0;
	
	unsigned int lastChange = 0;
	
	// initialize random generator
	srand(seed) ; 
	
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

			/* if current assignment is better or SA function is complied 
			 * then update variables to neighbour
			 */
			if ((currentState > lastState) || ((currentState < lastState) &&(funcResult > random ))){

				
				// update last state with current state
				lastState = currentState;
				
				lastChange = cycle;
				
				// reset flipper in solv object
				state->resetFlipper();
				
				// start new cycle with 1 flip
				flips = 1;
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses()){
					return 0;
				}
					
				
			} else
				// reset variables
				state->flipVariablesByFlipperVector();
						
		
		} while (nNeighbour < neighbourBound);
		
		// reset flipper in solv object
		state->resetFlipper();
		
		// begin new cycle
		cycle++;
		
		// if last change is 300 cycles behind then restart
		if (cycle - lastChange > 300){
			
			return 1;
		}

		// increase neighbourhood bound
		neighbourBound  = neighbourBound + nifsao*cycle;
		
		// calculate new temperature
		if (temp > 1)
			temp = temp - trfsao;
		
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	return 0;	
	
}


