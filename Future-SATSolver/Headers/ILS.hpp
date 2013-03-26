/* 
 * File:   ILS.hpp
 * Author: d
 *
 * Created on 24. März 2013, 11:00
 */

#ifndef ILS_HPP
#define	ILS_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "../Headers/SolvObject.hpp"
using namespace std;

class Ils {

	public:
	    Ils();
	    ~Ils();
            Ils(SolvObject* solvObject);
            void search ();
	   
	private:
            SolvObject* solvO;
};

#endif	/* ILS_HPP */

