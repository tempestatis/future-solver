/* 
 * File:   SolvObject.cpp
 * Author: tobias
 * 
 * Created on 20. März 2013, 13:58
 */

#include "../Headers/SolvObject.hpp"
#include <stdlib.h>

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

bool SolvObject::createNeighbour(unsigned int flips){

if (flips > this->numberOfVariables)
return 1;


return createNeighbour(flips,0);




}

bool SolvObject::createNeighbour(unsigned int flips, unsigned int currentIndex){

// you have to check yourself wether flips <= this->numberOfVariables and numberOfNeighbours != 0

bool returnNumber = 1;
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
if ((flips == 1) && (loadIndex)){
flipper->flip(currentIndex);
currentIndex++;
}



for (unsigned int i = currentIndex; i < numberOfVariables; i++){

// flip i if no further state was loaded
if ((!loadIndex)||flips == 1)
flipper->flip(i);





returnNumber = createNeighbour(flips-1, i+1);






// reset i
//flipper->flip(i);

// all neighbours checked
if (returnNumber == 0){
indexVec.push_back(i);

return 0;
}
else{
loadIndex = 0;
flipper->flip(i);
}




}


return returnNumber;

}

void SolvObject::resetFlipper(){
	
	flipper->reset();
	indexVec.clear();
	
	
}

void SolvObject::resetCopyFlipper(flippercopy &flipCopy){
	
	flipCopy.bitVector->reset();
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
/* input is rand() % param; means param = 1 is rand() % 1 ==0
 *                                param = 2 is rand() % 2 ==0or 1 is 50%
 *                                param = 10 is rand() % 10 ==0 to 9 is 10%
 * input > 0 and return is count flips
 */
int SolvObject::random_jump(int param){
    int count =0;
    srand( (unsigned) time(NULL) ) ; 
    flipper->reset();
    indexVec.clear();
    
    for(int i= 0; i < this->numberOfVariables; i++){
        if (rand()% 100 < param){
            count+=1;
            flipper->flip(i);   
        }  
    }
    return count;
}

void SolvObject::flipRandomVariables(){

srand( (unsigned) time(NULL) ) ;


for (unsigned int i = 0; i < numberOfVariables; i++){
if ((rand() % 5) == 0 )
variables->at(i) = 1;
else
variables->at(i) = 0;

}


}
bool SolvObject::matchFlipper(flippercopy& source){
    for (unsigned int i = 0; i < numberOfVariables; i++){
        if(source.bitVector->getElement(i) != flipper->getElement(i))
            return false;
    }
    return true;
}

void SolvObject::addFlippers(flippercopy& source){

bool addResult;
source.indexVec.clear();


// add solv object flipper to source
for (unsigned int i = 0; i < numberOfVariables; i++){

addResult = source.bitVector->getElement(i) or flipper->getElement(i);
source.bitVector->flip(i,addResult);

// if result of addition equal to 1 then save index
if (addResult == 1){
source.indexVec.push_back(i);
}
}

}