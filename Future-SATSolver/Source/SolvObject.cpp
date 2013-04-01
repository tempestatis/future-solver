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
	 
	 flipper = new BitVector(numberOfVariables);
	 
	 
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





void SolvObject::flipVariablesByBitVector(BitVector* vector){
	// flip variables by given vector
	for (int i = 0; i < this->numberOfVariables; i++){

		// if flipper has 1
		if (vector->getElement(i))
			this->changeStateOfVar(i);

	}
}

void SolvObject::flipVariablesByFlipperVector(){
	flipVariablesByBitVector(flipper);
}

unsigned int SolvObject::createNeighbour(unsigned int flips){
	
	if (flips > this->numberOfVariables)
		return 1;
	
	
			return createNeighbour(flips,0);
			
	
			
	
}

unsigned int SolvObject::createNeighbour(unsigned int flips, unsigned int currentIndex){
	
	// you have to check yourself wether flips <= this->numberOfVariables and numberOfNeighbours != 0
	
	unsigned int returnNumber = 1;
	bool loadIndex = 0;
	
	if (flips == 0){
		
		return 0;
	}
	
		
		
	
	if (indexVec.size() > 0){
		
		currentIndex = indexVec.back();
		indexVec.pop_back();
		loadIndex = 1;
	}
	
	// flip old state back and increment currentIndex to next position
	if (flips == 1 && loadIndex)
		flipper->flip(currentIndex++);
	
	for (int i = currentIndex; i < numberOfVariables; i++){
		
		// flip i if no further state was loaded
		if (!(loadIndex && flips > 1))
			flipper->flip(i);
		
		
		
		returnNumber = createNeighbour(flips-1, i+1);
		
		// add 
		indexVec.push_back(i);
		
		// reset i
		//flipper->flip(i);
		
		// all neighbours checked
		if (returnNumber==0){
			return 0;
		}
		
		
		
	}
	
	
	return returnNumber;
	
}

void SolvObject::resetFlipper(){
	
	flipper->reset();
	indexVec.clear();
	
	
}

unsigned int SolvObject::getSatisfiedClausesFromLastCheck(){
	return this->satisfiedClausesByMostImprovedNeighbour;
}

void SolvObject::printVariablesAssignment(){
	
	cout << "Current assignment of variables: ";
	for (int i = 0; i < numberOfVariables; i++){
		printf("%d",variables->at(i));
	}
	cout << endl;
}

void SolvObject::printFlipper(){
	
	cout << "Current flipper assignment: ";
	for (int i = 0; i < numberOfVariables; i++){
		printf("%d",flipper->getElement(i));
	}
	cout << endl;
}

void SolvObject::initializeCopyFlipper(flippercopy &flipCopy){
	
	
	// create new one by copying existing flipper
	flipCopy.bitVector = new BitVector(*(this->flipper));
	
	// copy index vector
	flipCopy.indexVec = this->indexVec;
	
	
	
	
	
	
	
}

void SolvObject::copyFlipper(flippercopy &source){
	
	vector<unsigned int> copy = (this->indexVec);
	
	
	
	// create a copy of flipper 
	source.bitVector = new BitVector(*(this->flipper));
	
	// deallocate index vector
	source.indexVec.clear();
	
	// create a new one by copying
	source.indexVec = vector<unsigned int>(copy);
	
	
	

	
}

void SolvObject::useFlipperCopy(flippercopy &flipperCopy){
	
	
	// do a copy of indexVec
	vector<unsigned int> copy = (flipperCopy.indexVec);
	
	
	// set to new one
	this->flipper = flipperCopy.bitVector;
	
	
	
	// deallocate old index vector
	this->indexVec.clear();
	
	this->indexVec = vector<unsigned int>(copy);
	
}