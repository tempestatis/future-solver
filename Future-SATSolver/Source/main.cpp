/* 
 * File:   main.cpp
 * Author: tobias
 *
 * Created on 19. Januar 2013, 16:50
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>


#include "../Headers/Parser.hpp"
#include "../Headers/BitVector.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	
	
    
	
	

	
	
	
	
	
	

    FILE* file = fopen( argv[1], "rb" );	
    
    
    Parser* parser = new Parser();
    SolvObject* solvObj = parser->parse(file);
	 
	 cout << "Satisfied Clauses: " << solvObj->getNumberOfSatisfiedClauses() << endl;
	 
	 cout << "Rest: " << solvObj->checkNeighbours(5,1,0) << endl;
	 
	 cout << "bester Wert: " << solvObj->getSatisfiedClausesFromLastCheck() << endl;
	 
	 cout << "Rest: " << solvObj->checkNeighbours(5,1,5) << endl;
	 
	 cout << "bester Wert: " << solvObj->getSatisfiedClausesFromLastCheck() << endl;
	 
	 cout << "Rest: " << solvObj->checkNeighbours(10,2,0) << endl;
	 
	 cout << "bester Wert: " << solvObj->getSatisfiedClausesFromLastCheck() << endl;
	 
	 cout << "Rest: " << solvObj->checkNeighbours(10,3,0) << endl;
	 
	 cout << "bester Wert: " << solvObj->getSatisfiedClausesFromLastCheck() << endl;
	 
	 
	 solvObj->flipVariablesByMostImprovedNeighbour();
	 
	 
	 
	 
	 
	 cout << "Satisfied Clauses: " << solvObj->getNumberOfSatisfiedClauses() << endl;
	 
	 solvObj->resetFlipper();
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 

    // We don't need parser any more
    delete parser;
    parser = 0;
    
    
    
	 
    return 0;
}





/* for testing in main
    printf("Size: %d\n",solvObj->getListOfVariables()->size());
    
    a = solvObj->getListOfVariables();
    
    for (int i = 0; i < solvObj->getListOfVariables()->size(); i++)
	 
    
	printf("VAR: %d   Adress: %p\n",(*a)[i], &((*a)[i]));
    
    solvObj->changeStateOfVar(50,1);
	 //solvObj->changeStateOfVar(1,1);
    
    for (int i = 0; i < solvObj->getListOfVariables()->size(); i++)
	 
    
	printf("VAR: %d   Adress: %p\n",(*a)[i], &((*a)[i]));
    
   // printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(0).varPointer,*(solvObj->getClause(0)->at(0).varPointer),solvObj->getClause(0)->at(0).isNegative);
   // printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(1).varPointer,*(solvObj->getClause(0)->at(1).varPointer),solvObj->getClause(0)->at(1).isNegative);
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(2).varPointer,*(solvObj->getClause(0)->at(2).varPointer),solvObj->getClause(0)->at(2).isNegative);
    
    
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(1)->at(0).varPointer,*(solvObj->getClause(1)->at(0).varPointer),solvObj->getClause(1)->at(0).isNegative);
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(1)->at(1).varPointer,*(solvObj->getClause(1)->at(1).varPointer),solvObj->getClause(1)->at(1).isNegative);
    
    printf("number of satisfied clauses: %d\n",solvObj->getNumberOfSatisfiedClauses());
	 
    */
