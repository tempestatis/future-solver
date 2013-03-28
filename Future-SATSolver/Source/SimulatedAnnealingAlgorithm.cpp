#include "../Headers/SimulatedAnnealingAlgorithm.h"
#include <math.h>
#include <stdlib.h>


int simulatedAnnealing(SolvObject* state, double initTemp, short neighbourBound){
	
	// define cycle variable
	unsigned int cycle = 0;
	unsigned int k = 1;
	int satisfiedClauses = state->getNumberOfSatisfiedClauses();
	int lastCheck;
	double temp = initTemp;
	unsigned int flips = 1;
	double funcResult = 0;
	unsigned int nIndex = 0;
	


	 
	// define list of flips, sized by initial neighbourBound
	//vector<int> flipIndezes = new vector<int>(neighbourBound);
	
			  
	
	cout << "start with: "<< state->getNumberOfSatisfiedClauses() << endl;		  
	
	for (int i = 0 ; i < 1000000 ; i++){
		cycle = state->createNeighbour(flips);	
		//cout << "i: " << i << "result " << cycle << endl;
		if (cycle > 0 && flips < state->getListOfVariables()->size()){
			state->resetFlipper();
			state->createNeighbour(++flips);
			cout << "erhöhe flips: " << flips << endl;
		}
		
		state->flipVariablesByFlipperVector();
		if (state->getNumberOfSatisfiedClauses() == state->getNumberOfClauses()){
			cout << "habs" << endl;
			return 0;
		}
		//cout << "satisfied clauses: "<< state->getNumberOfSatisfiedClauses() << endl;		  
		state->flipVariablesByFlipperVector();
	}
	
	
	/*do {
		
		do{
			
		
					  
			cycle = state->checkNeighbours(83,1,0);
			if (flips <= state->getListOfVariables()->size()  && (cycle > 0)){
			
				// restart with more flips on index == 0
				flips++;
				cout << "flips: " << flips << endl;
				nIndex = 0;
				break;
			};
			
			
			
			// if neighbour state is better than current state then ...
			lastCheck = state->getSatisfiedClausesFromLastCheck();
			
			//cout << "last check" << lastCheck << endl;
			
			funcResult = (exp(-lastCheck - satisfiedClauses)/ temp); 
			
			if ((lastCheck > satisfiedClauses) || ((lastCheck < satisfiedClauses) &&(funcResult > ( rand() % 2) ))){
				
				// update to neighbour
				
				cout << "satisfied clauses: "<< state->getSatisfiedClausesFromLastCheck() << endl;
				
				
				
				
				state->flipVariablesByMostImprovedNeighbour();
				
				satisfiedClauses = state->getNumberOfSatisfiedClauses();
				
				state->printVariablesAssignment();
				
				
				state->resetFlipper();
				
				flips = 1;
				
				nIndex = 0;
				
				// if sat then stop
				if (state->getSatisfiedClausesFromLastCheck() >= state ->getNumberOfClauses())
					return;
				
				
				
			}
						
		nIndex++;				
		} while (nIndex < neighbourBound);
		k++;
		
		//neighbourBound += k;
		neighbourBound ++;
		
		cout << "current cycle: " << k << " and neighbourhood: " << neighbourBound << endl;
		
		temp--;



	//} while(k < 40);
	} while(state->getNumberOfSatisfiedClauses() < state ->getNumberOfClauses());

	
	*/
	
	
	return 1;	
	
}