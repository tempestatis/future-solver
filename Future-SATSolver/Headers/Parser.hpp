/* 
 * File:   Parser.hpp
 * Author: tobias
 *
 * Created on 19. Januar 2013, 16:51
 */

#ifndef PARSER_HPP
#define	PARSER_HPP

#include "SolvObject.hpp"
#include  <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h>

 






SolvObject* parse (FILE* file);

void skipComment(char byte, FILE* file);
char skip(char byte, FILE* file);
int parseNumber(char byte, FILE* file);
	
	








#endif	/* PARSER_HPP */

