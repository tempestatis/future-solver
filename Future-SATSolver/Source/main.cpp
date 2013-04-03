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
#include "../Headers/SimulatedAnnealingAlgorithm.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	
	// generall: improvements
	
	// initial variable state -> 0000 or 1111 dependent on number of negative variables
	
	// 
	
    
	// stur:							// SAO:								// SALS
	// 3 secs ksat8				1 sec by 100,100				200 secs 200,1000
	// 12 secs ksat6        0,5 sec by 100,100			242 secs by 200,1000

	// ksat 10						1m 23
	// ksat 11						13 sec 500, 200 relativ verlässlich 400,200 geht auch
	
	
	
	
	
    FILE* file = fopen( argv[1], "rb" );	
    
    
    Parser* parser = new Parser();
    SolvObject* solvObj = parser->parse(file);
	 
	 
	 
	 // We don't need parser any more
    delete parser;
    parser = 0;
	 
	 
	 // baue den zu traversierenden Baum
	 
	 
	/*
	 if (simulatedAnnealingLessFlips(solvObj, 100, 1000) == 0)
		cout << "gefunden !" << endl;
	 
	 else{
			cout << "nicht gefunden !" << endl;
			
			
	 }
	 * */
	 
	 
	 unsigned int temp = 200;
	 unsigned int neighbourBound = 300;
	 bool result = 1;
	 
	 solvObj->flipRandomVariables();
	 
	 

	 do {
		 
		 result = simulatedAnnealingOriginal(solvObj, temp, neighbourBound);
		 
		 if (result == 0){
			 cout << "gefunden !" << endl;
			 return 0;
		 }
		 else{
			 cout << "nicht gefunden !" << endl;
			 
			 if (temp == 600){
				
				 solvObj->flipRandomVariables();
				 temp = 200;
				 neighbourBound = 300;
				 
			 } else
			 {
				temp = temp + 100;
				neighbourBound = neighbourBound + 100;
				cout << "erhöhe auf temp: " << temp << endl;
			 }
		 }
		 
	 } while (result == 1);
	 
	 
	 
	 
	 
	 
	  
    
    
    
	 
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
