/* 
 * File:   SolvObject.hpp
 * Author: tobias
 *
 * Created on 20. März 2013, 13:57
 */

#ifndef SOLVOBJECT_HPP
#define	SOLVOBJECT_HPP

#include <vector>
#include <stdio.h> 

using namespace std;


struct variable{

	    unsigned char* varPointer;
	    int index;
	    bool isNegative;

	};
	
	typedef std::vector<variable> clause;



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
      
		// sets index from var list to variable of clause (for better copy performance)
		void setClauseVariableIndex(int clauseIndex, int variableIndex, int index);
		
		// change state of variable with given new state
		void changeStateOfVar(int index, bool state);
		
		// change state of variable
		void changeStateOfVar(int index);
		
		
		
		// get number of clauses
		int getNumberOfClauses();
		
		// get number of satisfied clauses
		int getNumberOfSatisfiedClauses();
		    
		
    
	protected:
	    
	    // list of clauses
	    vector<clause>* clauses;

	    // array of variables:
	    vector<unsigned char>* variables;
	    
	    // number of clauses
	    int numberOfClauses;
    
};


	



#endif	/* SOLVOBJECT_HPP */

