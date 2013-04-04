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
	
	//cout << "start with: "<< lastState << endl;		  
	
	
	
	
	do {
		//cout << "cycle: " << cycle << endl;
		do{
			
			
			
			//state->printFlipper();
			
			
		
			// create neighbour , if no neighbour have been created then increment flips 
			while(state->createNeighbour(flips) > 0){
				
				if (flips < numberOfVariables){
					
					flips++;
					state->resetFlipper();
					//cout << "must increase flips to: " << flips << endl;
					
					
				}
			}
			
			// increment number of created neighbours
			nNeighbour++;
			
			
			
			
			//cout << "neighbourhood" << neighbourBound << endl;
			
			// flip variables by flipper
			state->flipVariablesByFlipperVector();
			
			currentState = state->getNumberOfSatisfiedClauses();
			
			funcResult = exp(((-lastState - currentState)/ temp));
			
			
		   
			random = (double)(rand() % 100000 + 1) / 100000;
			
			//if ((currentState > lastState)){
			if ((currentState > lastState) || ((currentState < lastState) &&(funcResult > random ))){
				
				// update to neighbour
				
				
				//cout << "number of clauses in current state: " << currentState << "\t temp: " << temp << endl;
				lastState = currentState;
				
				lastChange = cycle;
				
				
				
				
				
				
				//state->printVariablesAssignment();
				
				
				state->resetFlipper();
				
				flips = 1;
				
				
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses()){
					cout << endl;
					cout << endl;
					cout << endl;
					return 0;
				}
					
				
				
				
			} else
				// reset variables
				state->flipVariablesByFlipperVector();
						
		
		} while (nNeighbour < neighbourBound);
		
		state->resetFlipper();
		cycle++;
		
		// restart
		if (cycle - lastChange > 500){
			
			cout << endl;
			cout << endl;
			cout << endl;
			
			return 1;
		}
			
		
		//neighbourBound += k;
		neighbourBound  = neighbourBound + 5*cycle;
		//nNeighbour = 0;
		
		//cout << "current cycle: " << cycle << " and neighbourhood: " << neighbourBound << endl;
		
		if (temp > 1)
			temp--;
		
		
		
		



	//} while(k < 40);
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	
	
	
	return 0;	
	
}



int simulatedAnnealingLessFlips(SolvObject* state, double initTemp, unsigned int neighbourBound){
	
	// define cycle variable
	unsigned int lastChange = 1, cycle = 1;
	
	
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
	bool foundBetterNeighbour = 0;
	flippercopy worseFlipper, bestFlipper;
	state->initializeCopyFlipper(bestFlipper);
	state->initializeCopyFlipper(worseFlipper);
	
	
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
			
			
		   
			random = (double)(rand() % 100000 + 1) / 100000;
			
			
			if ((currentState > lastState)){
				
				
				// save better candidate
				state->copyFlipper(bestFlipper);
				
				foundBetterNeighbour = 1;
				
				lastState = currentState;
				
				// if sat then stop
				if (currentState == state->getNumberOfClauses())
					return 0;
				
				
				
				
				
			} else if ((currentState < lastState) && (funcResult > random )){
				
				
				
				// save worse candidate
				state->copyFlipper(worseFlipper);
				
				
				
			} 
				
				// reset variables
			state->flipVariablesByFlipperVector();
			
						
				
				
				
				
		} while (nNeighbour < neighbourBound);
		
		// if all neighbours checked and no better candidate was found then leave plateau with worse candidate
		if (foundBetterNeighbour){

			
			state->useFlipperCopy(bestFlipper);
			
			
			// flip with best candidate
			state->flipVariablesByFlipperVector();
			
			cout << "satisfied clauses with best neighbour: " << state->getNumberOfSatisfiedClauses() << endl;
			
			foundBetterNeighbour = 0;
			
			lastChange = cycle;
			
			// if temp > 1 then it was possible to find a worse candidate 
		} else if (temp > 1){
			
			state->useFlipperCopy(worseFlipper);
			
			
			// flip with worse candidate
			state->flipVariablesByFlipperVector();
			
			int satisfiedClauses = state->getNumberOfSatisfiedClauses();
			
			cout << "satisfied clauses with worse neighbour: " << satisfiedClauses << endl;
			
			lastState = satisfiedClauses;
			
			lastChange = cycle;
			
		}
			
			
		
		state->resetFlipper();
		cycle++;
		
		// restart after 10 cycles with no new neighbour
		if (cycle - lastChange > 10){
			
			return 1;
		}
			
		
		//neighbourBound += k;
		neighbourBound  = neighbourBound + 2*cycle;
		nNeighbour = 0;
		
		//cout << "current cycle: " << cycle << " and neighbourhood: " << neighbourBound << endl;
		
		if (temp > 1)
			temp--;
		cout << "current temp: " << temp << endl;
		
		
		



	//} while(k < 40);
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	
	
	
	return 0;	
	
}