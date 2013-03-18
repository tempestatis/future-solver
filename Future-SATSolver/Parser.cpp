/* 
 * File:   Parser.cpp
 * Author: tobias
 * 
 * Created on 19. Januar 2013, 17:06
 */

#include "Parser.hpp"







Parser::Parser(){
    
};

void Parser::parse(FILE* file){
    
	char byte = 1;
	int j,i = 0;
	
	int variable_index = 0;
	int clausesIndex = 0;
	
	int numberOfClauses = 0;
	int numberOfVariables = 0;
	
	variable var;
	

	//FILE* file = fopen( argv[1], "rb" ); 
	
	
	
	// skip all bytes which aren't numbers	
	skipComment(byte, file);
	byte = skip(byte,file);


	// parse number of variables
	numberOfVariables = parseNumber(byte, file);
	
	
	printf( "%d variables have been found.\n",numberOfVariables);

	byte = skip(byte,file);
	// parse number of clauses
	numberOfClauses = parseNumber(byte, file);		

	printf( "%d clauses have been found.\n",numberOfClauses);

	// alloc memory for variables
	for (i = 0; i <= numberOfVariables; i++)
		this->variables.push_back(0);
	printf("test: %d\n",variables[0]);
	printf("test: %d\n",variables[1]);
	printf("test: %d\n",variables[2]);
	
	
	
	// alloc memory for clauses
	for (i = 0; i <= numberOfClauses; i++)
		this->clauses.push_back(clause());
	
	
	



	

	
	// parse variables
	// loop over all clauses
	clausesIndex = numberOfClauses-1;

	while (byte > 0 && clausesIndex >= 0){
		byte = skip(byte,file);
		variable_index = parseNumber(byte, file);

		// loop over all chars in clause
		
		
		i = 0;
		while(variable_index != 0) {
			// number of variables
			
			//printf( "variable_index: %d\n", variable_index );						

			

			if (variable_index > 0){
			
				// map clause variable to assignments of the used variables
			    
				// add variable to clause
				this->clauses[clausesIndex].push_back(variable());
				
				
				clauses[clausesIndex][i].varPointer = &(variables[variable_index-1]);
				printf("test2: %d,  i:%d,  index:%d\n",*(clauses[clausesIndex][i].varPointer),i,variable_index);
				clauses[clausesIndex][i].isNegative = 0;
				

			}else{
				// map clause variable to assignments of the used variables w.r.t. to negation
				//printf( "neg variable_index: %d\n", variable_index );						
				clauses[clausesIndex][i].varPointer = &variables[(variable_index*(-1))-1];
				printf("test2 neg: %d,  i:%d,  index:%d\n",*(clauses[clausesIndex][i].varPointer),i,variable_index);
				
				clauses[clausesIndex][i].isNegative = 1;
			
			}
			
			i++;
		

			//printf( "variables: %d\n", *clauses[clausesIndex].variable );

			
			// else
			
			byte = skip(byte,file);
			
			variable_index = parseNumber(byte, file);
			
	
	
		}
		// go to next line (clause)
		clausesIndex--;
	}

	/*
	cout << "start output: " << endl;
	for (i = 0; i < numberOfClauses; i++){
	    cout << "clause: " << i << endl;
	    
	    for (j = 0; j <= clauses[i].size();j++){
		
		printf("Wert der Variable: %d\n",*(clauses[i][j].varPointer));
		printf("Variable ist negativ in Clausel: %d\n",clauses[i][j].isNegative);
	    }
	}
	
	*/
		
	

 
	/*
	  printf( "hex: %x\t", byte ); 
	  printf( "oktal: %o\t", byte ); 
	  printf( "ascii-code: %d\t", byte );						
	  printf( "char: %c\n", byte );						
	*/	
	
	
	fclose( file );
    
}


// skip to number of clauses and variables
void Parser::skipComment(char byte, FILE* file){



	while( ( byte = fgetc( file ) ) > 0 && byte == 'c'){
		while( ( byte = fgetc( file ) ) > 0 && byte != 0x0A){

			//printf( "Skipped this char: %c\n", byte );

		}
	}

	
	return;

}

// skip to next number
char Parser::skip(char byte, FILE* file){

	while( ( byte = fgetc( file ) ) > 0 && !(byte < 58 && byte > 46) && !(byte == 0x2D)){

		//printf( "Skipped this char: %c\n", byte );

	}
	return byte;

}

int Parser::parseNumber(char byte, FILE* file){
	int number = 0;
	short neg = 1;


	do {
		// * 10
		
		number = (number << 3) + (number << 1);
		// if byte == '-' then 
		if (byte == 0x2D)
			neg = -1;
		number += atoi(&byte);


	}while (( byte = fgetc( file ) ) > 0 && (byte < 58 && byte > 46));



	return number*neg;
}

