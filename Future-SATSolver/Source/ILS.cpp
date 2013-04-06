#include "../Headers/ILS.h"




bool localSearch(SolvObject* state, unsigned int neighbours, unsigned int satisfieldClausesFromFurtherState){
	
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


bool iteratedLocalSearchAlgorithm(SolvObject* solvO, int maxNeighbours, unsigned short rfils, unsigned short ifrfils, int seed){
    
	// initialize random generator
	srand( seed ) ;
    unsigned int satClauses = solvO->getNumberOfSatisfiedClauses();
    unsigned int Clauses = solvO->getNumberOfClauses();
    
	 
	 
	 
	 
	 // temporaly flipper for saving last local minima state
    flippercopy tempFlipper;
    solvO->initializeCopyFlipper(tempFlipper);
    
    unsigned int tempSatClauses = satClauses;
    
    
    while (satClauses < Clauses){
        
		 
        //use local search for find best solution candidate
        while (localSearch(solvO, maxNeighbours, satClauses) == 0){
			  satClauses = solvO->getNumberOfSatisfiedClauses();
			  
			  if (satClauses == Clauses)
				  // Sat
				  return 0;
			  
			  // add calculated best flipper to temp flipper
			  solvO->addFlippers(tempFlipper);
			  
			  
		  }
		  // at this point local search have reached a local minimum
		  
		  
        // check whether current local minimum is better than old one
		  if (satClauses < tempSatClauses){
			  // it's not better
			 // jump back to old state
			  solvO->useFlipperCopy(tempFlipper);
			  solvO->flipVariablesByFlipperVector();
			  
			  // increment chance of random flip
			  if (rfils + ifrfils < 1000)
				rfils = rfils + ifrfils;
			  
			  
			  
		   } else{
				// update current satisfied clauses
				tempSatClauses = satClauses;  
			}
        
		  
		  // do a random jump from current local minima
        
		  unsigned int numberFlips = 0;
		  solvO->resetFlipper();
		  solvO->resetFlipperCopy(tempFlipper);
		  
        do{
            
				
			  // go through all variables and flip randomly
			  for (unsigned int i = 0; i < solvO->getListOfVariables()->size(); i++){
				  
					if (rand()% 1000 < rfils){
						numberFlips++;
						solvO->flipBitInFlipper(i);
					}  
			  }
			  
			  
			  
        }while(numberFlips == 0);
		  
		  // save random flips to temp flipper for jumping back
        solvO->copyFlipper(tempFlipper);
		  
		  // flip variables by random flip
        solvO->flipVariablesByFlipperVector();
		  
		  satClauses = solvO->getNumberOfSatisfiedClauses();
        
		  
        
    }
    
	 return 0;
}
	