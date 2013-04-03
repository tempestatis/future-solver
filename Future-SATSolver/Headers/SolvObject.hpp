/* 
 * File:   SolvObject.hpp
 * Author: tobias
 *
 * Created on 20. März 2013, 13:57
 */

#ifndef SOLVOBJECT_HPP
#define	SOLVOBJECT_HPP

#include "BitVector.hpp"

#include <vector>
#include <stdio.h> 
#include <iostream>
#include <bitset>
#include <stdlib.h>


using namespace std;


struct variable{

	    unsigned char* varPointer;
	    bool isNegative;

	};
	
	typedef std::vector<variable> clause;
	
	struct flippercopy{
		
		vector<unsigned int> indexVec;
		BitVector* bitVector;
		
	};



class SolvObject{
    
	
    
	public:
		// copy constructor is not finished, use the Parser instead
		SolvObject(const SolvObject& rhs);
		SolvObject();
		SolvObject(int numberOfVariables, int numberOfClauses);
		~SolvObject();
		
		// get list of variables
		vector<unsigned char>* getListOfVariables();
		
		// get Clause
		clause* getClause(int index);
		
		// add variable to clause. clause is given by index.
		void addVaribaleToClause(int index);
		
		unsigned char* getAdressOfVariable(int index);
		
		// sets pointer of clause variable to an unsigned char adress
		void setClauseVariablePointer(int clauseIndex, int variableIndex, unsigned char* adress);
		
		// sets variable negative value
		void setNegation(int clauseIndex, int varIndex,bool b);
      
		// change state of variable with given new state
		void changeStateOfVar(int index, bool state);
		
		// change state of variable
		void changeStateOfVar(int index);
		
		
		
		// get number of clauses
		int getNumberOfClauses();
		
		// get number of satisfied clauses
		int getNumberOfSatisfiedClauses();
		
		// check neighbours
		unsigned int createNeighbour(unsigned int flips);
		
		void flipVariablesByBitVector(BitVector* vector);
		
		// flip variables by flipper
		void flipVariablesByFlipperVector();
		
		// reset data element flipper of solv object
		void resetFlipper();
		
		
		
		// value of satisfied clauses from last checkNeighbours
		unsigned int getSatisfiedClausesFromLastCheck();
		
		// prints a string representation of variables
		void printVariablesAssignment();
		
		// prints current flipper assignment
		void printFlipper();
		
		// initialize a copy of flipper and index vector by values from solver object
		void initializeCopyFlipper(flippercopy &flipperCopy);
		
		// copy flipper and index vector
		void copyFlipper(flippercopy &source);
		
		// use a flippercopy for create neighbour
		void useFlipperCopy(flippercopy &flipperCopy);
		
		// change random initial state of variables
		void flipRandomVariables();
			
		
		
		
			
		
		
		
		    
		
    
	protected:
	    
	    // list of clauses
	    vector<clause>* clauses;
		 
	    // array of variables:
	    vector<unsigned char>* variables;
	    
	    // number of clauses
	    unsigned int numberOfClauses;
		 
		 // number of variables
		 unsigned int numberOfVariables;
		 
		 unsigned int satisfiedClausesByMostImprovedNeighbour;
		 
		 
		 
		 // vector of changed bits
		 BitVector* flipper;
		 
	private:
		
		
		
		vector<unsigned int> indexVec;
		
		
		// check neighbours
		unsigned int createNeighbour(unsigned int flips, unsigned int currentIndex);
		
		
		
		
		
		
		
    
		
		
		
		
};


	



#endif	/* SOLVOBJECT_HPP */

