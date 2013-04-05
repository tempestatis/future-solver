/* 
 * File:   VND.hpp
 * Author: juliushofler
 *
 * Created on 20. März 2013, 21:23
 */

#include "../Headers/VND.hpp"

VND::VND() {

};

VND::VND(SolvObject* solvObject) {

    this->solvObject = solvObject;
};

int VND::search(){
    
    vector <int>::size_type numberOfVariables;
    flippercopy flipperCopy;
    unsigned int newNumberOfSatisfiedClauses;
    
    // number of variables
    numberOfVariables = solvObject->getListOfVariables()->size();
    
    // number of clauses
    unsigned int numberOfClauses = solvObject->getNumberOfClauses();
    
    // initial number of satisfied clauses
    unsigned int startNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
    unsigned int bestNumberOfSatisfiedClauses = startNumberOfSatisfiedClauses;
    
    // copy initial state in flipper
    solvObject->initializeCopyFlipper(flipperCopy);
    
    // check initial state whether it is a solution
    if (startNumberOfSatisfiedClauses == numberOfClauses) {
        printf("s SATISFIABLE\n");
        return 1;
    }
    
    unsigned int numberOfNeighbourhoods = 100;
    unsigned int initalNumberOfNeighbourhoods = 100;
    unsigned int currentNeighbourhood = 1;
    unsigned int indexOfNeighbourhoods = 0;
    unsigned int flips = 1;
    unsigned int maxFlips = 100;
    unsigned int rest = 0;
    unsigned int numberOfTriesInOneFlip = 0;
    
    // maximal number of flips
    if (numberOfVariables < maxFlips) {
        maxFlips = (int) numberOfVariables;
    }
    
    cout << "First SAT Clauses: " << startNumberOfSatisfiedClauses << endl;
    
    // ends if there is a solution
    while(true) {
    
        //+++++++++++++
        // TODO: wenn er in einem flip abbricht und noch nicht fertig mit
        //       dem flip ist, dann flip nicht erhöhen
        //      Note: Anzahl der Nachbarn gleich halten und nur in diesem Bereich springen
        //      --> creatNeighbour solange aufrufen bis Grenze erreicht ist und dann Grenze erhöhen (Ausschnitt)
        //+++++++++++++
        
        // runs until all variables were flipped in this level or number of neighbourhoods were reached    
        while( currentNeighbourhood <= numberOfNeighbourhoods ) {

            rest = solvObject->createNeighbour(flips);
            //numberOfTriesInOneFlip += 1;
            
            if (rest == 1) {
                flips += 1;
                //cout << "Number: " << numberOfTriesInOneFlip << endl;
                //numberOfTriesInOneFlip = 0;
                //cout << "flips: " << flips << endl;
                solvObject->resetFlipper();
                solvObject->createNeighbour(flips);
            } 
            
            // shift the index if maxFlip is reached
            if (maxFlips < flips) {

                    //flips = 1;
                    //indexOfNeighbourhoods += numberOfNeighbourhoods;
                    //solvObject->resetFlipper();

                    // automaticly unsat if index is higher than number of variables
                    //if ( (indexOfNeighbourhoods + 1) > numberOfVariables) {
                            printf("s UNSATISFIABLE\n");
                            return 0;
                    //}
            }

            // flip values
            solvObject->flipVariablesByFlipperVector();

            // get new number of satisfied clauses
            newNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
            
            //cout << "Test: " << newNumberOfSatisfiedClauses << endl;

            // check whether it is better than the old
            if (newNumberOfSatisfiedClauses > bestNumberOfSatisfiedClauses) {
                solvObject->copyFlipper(flipperCopy);
                bestNumberOfSatisfiedClauses = newNumberOfSatisfiedClauses;
            }
            
            // check whether there is a solution
            if (newNumberOfSatisfiedClauses == numberOfClauses) {
                printf("s SATISFIABLE\n");
                return 1;
            }

            // inc number of sawn neighbours
            currentNeighbourhood += 1; 
            
            
            //cout << "current SAT clauses: " << newNumberOfSatisfiedClauses << endl;
            //solvObject->printVariablesAssignment();
            
            // revert flip
            solvObject->flipVariablesByFlipperVector();
            
            // just a try
            //if (numberOfNeighbourhoods > 20000) {
            //    flips += 1;
            //    numberOfNeighbourhoods = initalNumberOfNeighbourhoods;
            //    solvObject->resetFlipper();
            //}
            
            // new random list
            if (numberOfNeighbourhoods > 2000) {   
                return 0;
             
            }    
               
                
        }
    
        cout << "Next best SAT Clauses: " << bestNumberOfSatisfiedClauses << endl;
        
        // no improvements with this flip
        if (startNumberOfSatisfiedClauses >= bestNumberOfSatisfiedClauses) {
            
            // gets the best variable combination back
            //solvObject->useFlipperCopy(flipperCopy);
            //solvObject->flipVariablesByFlipperVector();
            
            //flips += 1;
            //solvObject->resetFlipper();
            //cout << "next flip: " << flips << endl;
            
            // inc neighbourhood
            numberOfNeighbourhoods += 50;
        }
    
        // get the best neighbour and continue
        else {
            solvObject->useFlipperCopy(flipperCopy);
            solvObject->flipVariablesByFlipperVector();
            
            flips = 1;
            numberOfTriesInOneFlip = 0;
            numberOfNeighbourhoods = initalNumberOfNeighbourhoods;
            startNumberOfSatisfiedClauses = bestNumberOfSatisfiedClauses;
            solvObject->resetFlipper();
        }
    
        // set back for a new run
        currentNeighbourhood = 1;
        
        cout << "Number of Neighbourhoods: " << numberOfNeighbourhoods << endl;
        //solvObject->printVariablesAssignment();
        
    
    }
 
    return 0;
}  
    
    




    // inc only flips, not neighbours
    int VND::search_secondTry(){
    
    vector <int>::size_type numberOfVariables;
    flippercopy flipperCopy;
    unsigned int newNumberOfSatisfiedClauses;
    
    // number of variables
    numberOfVariables = solvObject->getListOfVariables()->size();
    
    // number of clauses
    unsigned int numberOfClauses = solvObject->getNumberOfClauses();
    
    // initial number of satisfied clauses
    unsigned int startNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
    unsigned int bestNumberOfSatisfiedClauses = startNumberOfSatisfiedClauses;
    
    // copy initial state in flipper
    solvObject->initializeCopyFlipper(flipperCopy);
    
    // check initial state whether it is a solution
    if (startNumberOfSatisfiedClauses == numberOfClauses) {
        printf("s SATISFIABLE\n");
        return 1;
    }
    
    unsigned int numberOfNeighbourhoods = 100;
    unsigned int currentNeighbourhood = 1;
    unsigned int indexOfNeighbourhoods = 0;
    unsigned int flips = 1;
    unsigned int maxFlips = 100;
    unsigned int rest = 0;
    
    // maximal number of flips
    if (numberOfVariables < maxFlips) {
        maxFlips = (int) numberOfVariables;
    }
    
    cout << "First SAT Clauses: " << startNumberOfSatisfiedClauses << endl;
    
    // ends if there is a solution
    while(true) {
    
        //+++++++++++++
        // TODO: wenn er in einem flip abbricht und noch nicht fertig mit
        //       dem flip ist, dann flip nicht erhöhen
        //      Note: Anzahl der Nachbarn gleich halten und nur in diesem Bereich springen
        //      --> creatNeighbour solange aufrufen bis Grenze erreicht ist und dann Grenze erhöhen (Ausschnitt)
        //+++++++++++++
        
        // runs until all variables were flipped in this level or number of neighbourhoods were reached    
        while( (currentNeighbourhood <= numberOfNeighbourhoods) ) {

            rest = solvObject->createNeighbour(flips);
            
            if (rest == 1) {
                flips += 1;
                cout << "Flips: " << flips << endl;
                solvObject->resetFlipper();
                solvObject->createNeighbour(flips);
            } 
            
            // shift the index if maxFlip is reached
            if (maxFlips < flips) {

                    flips = 1;
                    indexOfNeighbourhoods += numberOfNeighbourhoods;
                    solvObject->resetFlipper();

                    // automaticly unsat if index is higher than number of variables
                    if ( (indexOfNeighbourhoods + 1) > numberOfVariables) {
                            printf("s UNSATISFIABLE\n");
                            return 0;
                    }
            }

            // flip values
            solvObject->flipVariablesByFlipperVector();

            // get new number of satisfied clauses
            newNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
            
            //cout << "Test: " << newNumberOfSatisfiedClauses << endl;

            // check whether it is better than the old
            if (newNumberOfSatisfiedClauses > bestNumberOfSatisfiedClauses) {
                solvObject->copyFlipper(flipperCopy);
                bestNumberOfSatisfiedClauses = newNumberOfSatisfiedClauses;
            }
            
            // check whether there is a solution
            if (newNumberOfSatisfiedClauses == numberOfClauses) {
                printf("s SATISFIABLE\n");
                return 1;
            }

            // inc number of sawn neighbours
            currentNeighbourhood += 1; 
            
            
            //cout << "current SAT clauses: " << newNumberOfSatisfiedClauses << endl;
            //solvObject->printVariablesAssignment();
            
            // revert flip
            solvObject->flipVariablesByFlipperVector();
        }
    
        cout << "Next best SAT Clauses: " << bestNumberOfSatisfiedClauses << endl;
        
        while(solvObject->createNeighbour(flips) < 1) {
        }
        
        // no improvements with this flip
        if (startNumberOfSatisfiedClauses >= bestNumberOfSatisfiedClauses) {
            
            // gets the best variable combination back
            //solvObject->useFlipperCopy(flipperCopy);
            //solvObject->flipVariablesByFlipperVector();
            
            flips += 1;
            solvObject->resetFlipper();
            //cout << "next flip: " << flips << endl;
        }
    
        // get the best neighbour and continue
        else {
            solvObject->useFlipperCopy(flipperCopy);
            solvObject->flipVariablesByFlipperVector();
            
            flips = 1;
            startNumberOfSatisfiedClauses = bestNumberOfSatisfiedClauses;
            solvObject->resetFlipper();
        }
    
        // set back for a new run
        currentNeighbourhood = 1;
        
        solvObject->printVariablesAssignment();
        
    }
    
 return 0;  
    
}   
    
    
    
    /*
    
    // TODO: wenn er schiftet dann brauch man wieder alles Nullen
    
    vector <int>::size_type numberOfVariables;
    vector <vector<int> > neighbourhoods(1);
    
    // number of variables
    numberOfVariables = solvObject->getListOfVariables()->size();
    
    // number of clauses
    unsigned int numberOfClauses = solvObject->getNumberOfClauses();
    
    // check initial state whether it is a solution
    unsigned int startNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
    if (startNumberOfSatisfiedClauses == numberOfClauses) {
        printf("s SATISFIABLE\n");
        return 1;
    }
    
    cout << startNumberOfSatisfiedClauses << endl;
    
    unsigned int numberOfNeighbourhoods = 20;
    unsigned int indexOfNeighbourhoods = 0;
    unsigned int flips = 1;
    unsigned int maxFlips = 20;
    unsigned int rest = 0;
    //unsigned int saveLeftNeighbours;
    
    // maximal number of flips
    if (numberOfVariables < maxFlips) {
        maxFlips = (int) numberOfVariables;
    }
    
    // until solver gets a solution
    while (true) {
    
    cout << "flips: " << flips << endl;   
        
    // get the best fliped neighbour
    if (maxFlips >= flips && numberOfNeighbourhoods!=0) {
        rest = solvObject->checkNeighbours(numberOfNeighbourhoods,flips,indexOfNeighbourhoods);
        cout << rest << endl;
    }
    
    // maxFlips is reached --> shift indexOfNeighbours
    else {
        flips = 1;
        indexOfNeighbourhoods += numberOfNeighbourhoods;
        
        // only checkNeighbours if enough variables are there
        if ( (indexOfNeighbourhoods + 1) <= numberOfVariables) {
                rest = solvObject->checkNeighbours(numberOfNeighbourhoods,flips,indexOfNeighbourhoods);
        }
        
        else {
            printf("s UNSATISFIABLE\n");
            return 0;
        }
    }
    
    // end of one flip, but neighbourhoods aren't full
    while (rest != 0) {
        
        // end of solving, no solution
        if (flips == numberOfVariables) {
            printf("s UNSATISFIABLE\n");
            return 0;
        }
        
        flips += 1;
        rest = solvObject->checkNeighbours(rest,flips,0);
        
    }
    
    // flip values from the best neighbour
    solvObject->flipVariablesByMostImprovedNeighbour();
    
    // check whether new state is better than the start state
    unsigned int newNumberOfSatisfiedClauses = solvObject->getNumberOfSatisfiedClauses();
    if (newNumberOfSatisfiedClauses <= startNumberOfSatisfiedClauses) {
        solvObject->flipVariablesByMostImprovedNeighbour();     // reset
        flips += 1;
    }
    
    else {
        // check whether new state is SAT
        if (newNumberOfSatisfiedClauses == numberOfClauses) {
                printf("s SATISFIABLE\n");
                return 1;
        }
        
        flips = 1;
        startNumberOfSatisfiedClauses = newNumberOfSatisfiedClauses;
    }
    
    cout << newNumberOfSatisfiedClauses << endl;
    
    solvObject->resetFlipper();
    
    }
   
   */
   

