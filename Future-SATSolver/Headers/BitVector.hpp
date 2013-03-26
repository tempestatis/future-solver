/* 
 * File:   BitVector.hpp
 * Author: tobias
 *
 * Created on 25. März 2013, 18:43
 */

#ifndef BITVECTOR_HPP
#define	BITVECTOR_HPP

#include <vector>

class BitVector{
	
public:
	BitVector();
	BitVector(unsigned int numberOfVariables);
	~BitVector();
	
	// reset bits to 0
	void reset();
	
	// get element
	bool getElement(unsigned int index);
	
	// flip the bit on index
	bool flip(unsigned int index);
	
	// flip the bit on index
	void flip(unsigned int index, bool value);
	
	
	
	
private:
	bool* vec;
	unsigned int size;
	
};


#endif	/* BITVECTOR_HPP */

