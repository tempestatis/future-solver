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
	
	// generall: improvements
	
	// initial variable state -> 0000 or 1111 dependent on number of negative variables
	
	// 
	
    
	// stur:							// SA:
	// 3 secs ksat8				1 sec by 100,100
	// 12 secs ksat6        0,5 sec by 100,100

	
	
	
	
	
	
	
    FILE* file = fopen( argv[1], "rb" );	
    
    
    Parser* parser = new Parser();
    SolvObject* solvObj = parser->parse(file);
	 
	 
	 
	 
	 
	 
	 
	 
	
	 
	 
	 
	 
	 
	  // We don't need parser any more
    delete parser;
    parser = 0;
	 
	  /*
	
	 if (simulatedAnnealingLessFlips(solvObj, 300, 100) == 0)
		cout << "gefunden !" << endl;
	 
	 else{
			cout << "nicht gefunden !" << endl;
			
			
	 }
	 */
    
    
    
	 
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
