/* 
 * File:   SolvObject.cpp
 * Author: tobias
 * 
 * Created on 20. März 2013, 13:58
 */

#include "../Headers/SolvObject.hpp"

SolvObject::SolvObject(){
    
}

SolvObject::SolvObject(const SolvObject& rhs){
	
	/*
	this->variables = new vector<unsigned char>(*(rhs.variables));
	numberOfClauses = rhs.numberOfClauses;
	this->clauses = new vector<clause>(rhs.clauses->size());
	
	for (int clauseIndex = 0; clauseIndex < rhs.clauses->size(); clauseIndex++){
		
		for (int varIndex = 0; varIndex < rhs.clauses->at(clauseIndex)->size(); varIndex++){
			this->clauses->at(clauseIndex)->at(varIndex) = new variable();
			// and so on
			this->clauses->at(clauseIndex)->at(varIndex).index = rhs.clauses->at(clauseIndex)->at(varIndex).index;
			
		}
			
	}
	
	clauses = rhs.clauses->at(0).at(0).index
	*/
}

SolvObject::SolvObject(int numberOfVariables, int numberOfClauses) {
    
    
    // alloc memory for variables
    variables = new vector<unsigned char>(numberOfVariables);
    
    // alloc memory for clauses
    clauses = new vector<clause>(numberOfClauses);
    
    // set number of clauses
    this->numberOfClauses = numberOfClauses;
    
 
}



SolvObject::~SolvObject() {
}

void SolvObject::addVaribaleToClause(int index){
    (*clauses)[index].push_back(variable());
}

unsigned char* SolvObject::getAdressOfVariable(int index){
    unsigned char* result = &((*variables)[index]);
    return result;
}

void SolvObject::setClauseVariablePointer(int clauseIndex, int variableIndex, unsigned char* adress){
    (*clauses)[clauseIndex][variableIndex].varPointer = adress;
}

void SolvObject::setClauseVariableIndex(int clauseIndex, int variableIndex, int index){
	(*clauses)[clauseIndex][variableIndex].index = index;
}

void SolvObject::setNegation(int clauseIndex, int varIndex, bool b){
    (*clauses)[clauseIndex][varIndex].isNegative = b;
}

clause* SolvObject::getClause(int index){
    clause* result = &(*clauses)[index];
    return result;
}

vector<unsigned char>* SolvObject::getListOfVariables(){
    
    vector<unsigned char>* result = variables;   
    return result;
}

void SolvObject::changeStateOfVar(int index, bool state){
    (*variables)[index] = state;
}

int SolvObject::getNumberOfClauses(){
    return numberOfClauses;
}

int SolvObject::getNumberOfSatisfiedClauses(){
    
	int result = 0;
	int clauseIndex , varIndex;
	

	for (clauseIndex = 0; clauseIndex < numberOfClauses; clauseIndex++){
		
		for (varIndex = 0; varIndex < clauses->at(clauseIndex).size(); varIndex++){
			
			variable var = clauses->at(clauseIndex).at(varIndex);
			
			if (var.isNegative xor *(var.varPointer) == 1){
				result++;
				break;
			}
			
			
		}

	
	// 
	}
	return result;
}