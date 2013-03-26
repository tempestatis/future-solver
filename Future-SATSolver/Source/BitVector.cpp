/* 
 * File:   BitVector.cpp
 * Author: tobias
 * 
 * Created on 25. März 2013, 18:47
 */

#include "../Headers/BitVector.hpp"

BitVector::BitVector() {
}

BitVector::BitVector(unsigned int numberOfVariables){
	
	vec = new bool[numberOfVariables];
	size = numberOfVariables;
	
}



BitVector::~BitVector() {
	
}

void BitVector::reset(){
	
	for (int i = 0; i < this->size; i++)
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

