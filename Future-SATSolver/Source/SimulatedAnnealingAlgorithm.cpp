#include "../Headers/SimulatedAnnealingAlgorithm.h"
#include <math.h>
#include <stdlib.h>


int simulatedAnnealingOriginal(SolvObject* state, double initTemp, unsigned int neighbourBound){
	
	// define cycle variable
	unsigned int cycle = 1;
	
	
	// variables for number of satisfied clauses
	int lastState = state->getNumberOfSatisfiedClauses();
	int currentState = 0;
	
	// number of variables
	unsigned int numberOfVariables = state->getListOfVariables()->size();
	
	double temp = initTemp;
	unsigned int flips = 1;
	long double funcResult = 0;
	double random = 0;
	unsigned int nNeighbour = 0;
	unsigned int lastChange = 0;
	
	
	srand( (unsigned) time(NULL) ) ; 
	
	

	 
	
	
			  
	lastState = state->getNumberOfSatisfiedClauses();
	
	if (lastState == state->getNumberOfClauses())
		return 0;
	
	cout << "start with: "<< lastState << endl;		  
	
	
	
	
	do {
		//cout << "cycle: " << cycle << endl;
		do{
			
			
			
			//state->printFlipper();
			
			
		
			// create neighbour , if no neighbour have been created then increment flips 
			while(state->createNeighbour(flips) > 0){
				
				if (flips < numberOfVariables){
					
					flips++;
					state->resetFlipper();
					cout << "must increase flips to: " << flips << endl;
					
					
				}
			}
			
			// increment number of created neighbours
			nNeighbour++;
			
			
			
			
			//cout << "neighbourhood" << neighbourBound << endl;
			
			// flip variables by flipper
			state->flipVariablesByFlipperVector();
			
			currentState = state->getNumberOfSatisfiedClauses();
			
			funcResult = exp(((-lastState - currentState)/ temp));
			
			
		   
			random = (double)(rand() % 100000) / 100000;
			
			//if ((currentState > lastState)){
			if ((currentState > lastState) || ((currentState < lastState) &&(funcResult > random ))){
				
				// update to neighbour
				
				
				cout << "number of clauses in current state: " << currentState << endl;
				lastState = currentState;
				
				lastChange = cycle;
				
				
				
				
				
				
				state->printVariablesAssignment();
				
				
				state->resetFlipper();
				
				flips = 1;
				
				
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses())
					return 0;
				
				
				
			} else
				// reset variables
				state->flipVariablesByFlipperVector();
						
		
		} while (nNeighbour < neighbourBound);
		
		state->resetFlipper();
		cycle++;
		
		// restart
		if (cycle - lastChange > 500){
			
			return 1;
		}
			
		
		//neighbourBound += k;
		neighbourBound  = neighbourBound + 2*cycle;
		//nNeighbour = 0;
		
		//cout << "current cycle: " << cycle << " and neighbourhood: " << neighbourBound << endl;
		
		if (temp > 0)
			temp--;
		
		
		
		



	//} while(k < 40);
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	
	
	
	return 0;	
	
}



int simulatedAnnealingLessFlips(SolvObject* state, double initTemp, unsigned int neighbourBound){
	
	// define cycle variable
	unsigned int cycle = 1;
	
	
	// variables for number of satisfied clauses
	int lastState = state->getNumberOfSatisfiedClauses();
	int currentState = 0;
	
	// number of variables
	unsigned int numberOfVariables = state->getListOfVariables()->size();
	
	double temp = initTemp;
	unsigned int flips = 1;
	long double funcResult = 0;
	double random = 0;
	unsigned int nNeighbour = 0;
	unsigned int lastChange = 1;
	flippercopy flipperCopy;
	state->initializeCopyFlipper(flipperCopy);
	
	
	srand( (unsigned) time(NULL) ) ; 
	
	

	 
	
	
			  
	lastState = state->getNumberOfSatisfiedClauses();
	
	if (lastState == state->getNumberOfClauses())
		return 0;
	
	cout << "start with: "<< lastState << endl;		  
	
	
	
	
	do {
		//cout << "cycle: " << cycle << endl;
		do{
			
			
			
			//state->printFlipper();
			
			
		
			// create neighbour , if no neighbour have been created then increment flips 
			while(state->createNeighbour(flips) > 0){
				
				if (flips < numberOfVariables){
					
					flips++;
					state->resetFlipper();
					cout << "must increase flips to: " << flips << endl;
					
					
				}
			}
			
			// increment number of created neighbours
			nNeighbour++;
			
			
			
			
			//cout << "neighbourhood" << neighbourBound << endl;
			
			// flip variables by flipper
			state->flipVariablesByFlipperVector();
			
			
			currentState = state->getNumberOfSatisfiedClauses();
			
			
			funcResult = exp(((-lastState - currentState)/ temp));
			
			
		   
			random = (double)(rand() % 100000) / 100000;
			
			
			if ((currentState > lastState)){
				
				// update to best neighbour
				
				
				cout << "number of clauses in current state: " << currentState << endl;
				
				lastState = currentState;
				
				lastChange = cycle;
				
				state->printVariablesAssignment();
				
				
				state->resetFlipper();
				
				flips = 1;
				
				
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses())
					return 0;
				
				
				
			} else if ((currentState < lastState) && (funcResult > random )){
				
				// reset variables
				state->flipVariablesByFlipperVector();
				
				// save worse candidate
				state->copyFlipper(flipperCopy);
				
				
				state->resetFlipper();
				
				flips = 1;
				
				
				
			} else{
				// neighbour is not useful
				// reset variables
				state->flipVariablesByFlipperVector();
			}
						
				// print current assignment
				//state->printVariablesAssignment();
				
				
				
		} while (nNeighbour < neighbourBound);
		
		// if all neighbours checked and no better candidate was found then leave plateau with worse candidate
		if (lastChange < cycle){

			
			state->useFlipperCopy(flipperCopy);
			
			
			lastChange = cycle;
			
			// flip with worse candidate
			state->flipVariablesByFlipperVector();
			
			cout << "satisfied clauses with worse neighbour: " << state->getNumberOfSatisfiedClauses() << endl;
			
		}
			
			
		
		state->resetFlipper();
		cycle++;
		
		// restart
		if (cycle - lastChange > 500){
			
			return 1;
		}
			
		
		//neighbourBound += k;
		neighbourBound  = neighbourBound + 2*cycle;
		//nNeighbour = 0;
		
		//cout << "current cycle: " << cycle << " and neighbourhood: " << neighbourBound << endl;
		
		if (temp > 0)
			temp--;
		
		
		
		



	//} while(k < 40);
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	
	
	
	return 0;	
	
}