/* 
 * File:   Parser.hpp
 * Author: tobias
 *
 * Created on 19. Januar 2013, 16:51
 */

#ifndef PARSER_HPP
#define	PARSER_HPP

#include  <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <vector>


using namespace std;

struct variable{
    
    char* varPointer;
    bool isNegative;
    
};


typedef std::vector<variable> clause;


class Parser {
    
    

	public:
	    Parser();
	    ~Parser();
	    void parse (FILE* file);
		
	    
	
	

	// list of clauses
	//list <variable> clause;
	vector<clause> clauses;
	
	// array of variables:
	vector<char> variables;
	

	// methods	
	void skipComment(char byte, FILE* file);
	char skip(char byte, FILE* file);
	int parseNumber(char byte, FILE* file);

	
};







#endif	/* PARSER_HPP */

