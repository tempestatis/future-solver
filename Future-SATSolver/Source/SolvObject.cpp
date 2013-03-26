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
	 
	 // set number of variables
	 this->numberOfVariables = variables->size();
	 
	 mostImprovingFlipper = new BitVector(numberOfVariables);
	 localFlipper = new BitVector(numberOfVariables);
	 
	 satisfiedClausesByMostImprovedNeighbour = 0;
	 
	 
    
 
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

void SolvObject::changeStateOfVar(int index){
	 // invert bit
	 (*variables)[index] = !(*variables)[index];
    
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



void SolvObject::updateMostImprovedNeighbour(){
	
	
	for (int i = 0; i < numberOfVariables; i++){
		mostImprovingFlipper->flip(i,localFlipper->getElement(i));
		
		
	}
	
	
}

void SolvObject::flipVariablesByBitVector(BitVector* vector){
	// flip variables by given vector
	for (int i = 0; i < this->numberOfVariables; i++){

		// if flipper has 1
		if (vector->getElement(i))
			this->changeStateOfVar(i);

	}
}

void SolvObject::flipVariablesByMostImprovedNeighbour(){
	flipVariablesByBitVector(mostImprovingFlipper);
}



unsigned int SolvObject::checkNeighbours(unsigned int numberOfNeighbours, unsigned int flips, unsigned int currentIndex){
	
	// you have to check yourself wether flips <= this->numberOfVariables and numberOfNeighbours != 0
	
	unsigned int returnNumber = numberOfNeighbours;
	
	if (flips == 0){
		
			/*
			cout << "flip following indizes: ";
		
			// write bit vector to stdout
			for (int i = 0; i < numberOfVariables; i++){
				
				 cout << localFlipper->getElement(i);
				
			}
			cout << endl;
			 * 
			 */
			
			// flip variables
			flipVariablesByBitVector(localFlipper);
			
			// check how many clauses are satisfied by actual variable assignment
			unsigned int s = this->getNumberOfSatisfiedClauses();
			//cout << "satisfied clauses: " << s << endl;
			
			// update number of satisfied clauses variable
			if (s > this->satisfiedClausesByMostImprovedNeighbour){
				
				// save new one in mostImprovingFlipper vector and update satisfiedClauses
				updateMostImprovedNeighbour();
				this->satisfiedClausesByMostImprovedNeighbour = s;
			} 
			
			// flip variables back to old state
			flipVariablesByBitVector(localFlipper);
			
			
			
			
			
		return --returnNumber;
	}
	
	for (int i = currentIndex; i < numberOfVariables; i++){
		
		// flip i
		localFlipper->flip(i);
		
		
		returnNumber = checkNeighbours(returnNumber, flips-1, i+1);
		
		// reset i
		localFlipper->flip(i);
		
		// all neighbours checked
		if (returnNumber==0){
			return 0;
		}
		
		
		
	}
	
	
	return returnNumber;
	
}

void SolvObject::resetFlipper(){
	
	localFlipper->reset();
	mostImprovingFlipper->reset();
	
}

unsigned int SolvObject::getSatisfiedClausesFromLastCheck(){
	return this->satisfiedClausesByMostImprovedNeighbour;
}