/* 
 * Implementation of Variable Neighbourhood Descent algorithm
 * 
 */


#include "../Headers/VNDF.h"

bool VNDF(SolvObject* state, unsigned int nvndf, unsigned short fifvndf){
	

	// number of variables
    unsigned int numberOfVariables = state->getListOfVariables()->size();
    
    
    // number of clauses
    unsigned int numberOfClauses = state->getNumberOfClauses();
    
    // initial number of satisfied clauses
    unsigned int lastState = state->getNumberOfSatisfiedClauses();
	 
	 // current number of satisfied clauses
    unsigned int currentState = lastState;
	 
	 // number of satisfied clauses before do local search
    unsigned int nSatClauses = lastState;
    
    // counter for neighbours
    unsigned int currentN = 1;
    
    unsigned int flips = 1;
	 
	 // flipper copy for saving best neighbour flipper
	 flippercopy flipperCopy;
	 // copy initial state in flipper
    state->initializeCopyFlipper(flipperCopy);
	 
	 // cycle of local searchs
	 unsigned int cycle = 0;
	 
	 // last change of variables
    unsigned int lastChange = 0;
    
    
    // check initial state whether it is a solution
    if (lastState == numberOfClauses) {
        // sat at beginning
        return 0;
    }
    
    
    // ends if there is a solution
    while(true) {
		 
		 // runs until all variables were flipped in this level or number of neighbourhoods were reached    
        while( currentN <= nvndf ) {
		 
		 
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
			  currentN++;
			  
			  // flip variables by flipper
				state->flipVariablesByFlipperVector();
			
				// get number of satisfied clauses by calculated neighbour
				currentState = state->getNumberOfSatisfiedClauses();

				// check whether there is a solution
				if (currentState == numberOfClauses)
					// sat
					return 0;
        

            // check whether it is better than the old
            if (currentState > lastState) {
                state->copyFlipper(flipperCopy);
                lastState = currentState;
            }
            
            
            // revert flip
            state->flipVariablesByFlipperVector();
                
        }
		  
		  
		  
		  
    
        // no improvements with this flip
        if (nSatClauses >= lastState) {
            
            
            // inc neighbourhood by neighbourhood increasing factor
				if (flips + fifvndf < numberOfVariables)
					flips = flips + fifvndf;
				
				
        }
    
        // get the best neighbour and continue
        else {
			  
			  lastChange = cycle;
			  
			  // use the best founded neighbour for flipping variables
				state->useFlipperCopy(flipperCopy);
            
				// flip variables by better neighbour
            state->flipVariablesByFlipperVector();
            
				// reset flipper
				state->resetFlipper();
            flips = 1;
				
				
				
            nSatClauses = lastState;
				
				// begin with new local search
				currentN = 0;
				
				
            
        }
    
        
        if (cycle-lastChange > 300){
			  
			  // do a restart
			  return 1;
		  }
        
        cycle++;
        
    
    }
 
    return 0;
}  

