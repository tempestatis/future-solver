/* 
 * File:   VND.hpp
 * Author: juliushofler
 *
 * Created on 20. März 2013, 21:23
 */

#ifndef VND_HPP
#define	VND_HPP


#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include<vector>

#include "SolvObject.hpp"
#include "BitVector.hpp"

using namespace std;


class VND {
    
    public:
        VND();
	~VND();
        VND(SolvObject* solvObject);
	int search ();
            
    private:
        SolvObject* solvObject;
};


#endif	/* VND_HPP */

