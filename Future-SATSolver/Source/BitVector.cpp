

#include <string.h>

#include "../Headers/BitVector.hpp"

BitVector::BitVector() {
}

BitVector::BitVector(unsigned int numberOfVariables){
	
	vec = new bool[numberOfVariables];
	size = numberOfVariables;
	
}

BitVector::BitVector(const BitVector& rhs){
	
	size = rhs.size;
	vec = new bool[size];
	memcpy(vec, rhs.vec, rhs.size);
	
}



BitVector::~BitVector() {
	
}

void BitVector::reset(){
	
	for (unsigned int i = 0; i < this->size; i++)
		vec[i] = 0;
}

bool BitVector::getElement(unsigned int index){
	return vec[index];
}

bool BitVector::flip(unsigned int index){
	vec[index] = !vec[index];
	return vec[index];
}

void BitVector::flip(unsigned int index, bool value){
	vec[index] = value;
	
}

