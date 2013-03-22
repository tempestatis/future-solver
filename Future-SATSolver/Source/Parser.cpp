/* 
 * File:   Parser.cpp
 * Author: tobias
 * 
 * Created on 19. Januar 2013, 17:06
 */


#include "../Headers/Parser.hpp"




Parser::Parser(){
    
}

Parser::~Parser(){
    
}
    




SolvObject* Parser::parse(FILE* file){
		
	char byte = 1;
	int i = 0;
	
	int variable_index = 0;
	int clausesIndex = 0;
	
	int numberOfClauses = 0;
	int numberOfVariables = 0;
	
	SolvObject* solvObject;
	
	
	

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
	
	
	solvObject = new SolvObject (numberOfVariables, numberOfClauses);
	
	

	
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

			
			// debug
			printf("var:%d\n",variable_index);
			if (variable_index > 0){
			
				// map clause variable to assignments of the used variables
			    
				// add variable to clause
			        solvObject->addVaribaleToClause(clausesIndex);
				//this->clauses[clausesIndex].push_back(variable());
				
				//clauses[clausesIndex][i].varPointer = &(variables[variable_index-1]);
				solvObject->setClauseVariablePointer(clausesIndex, i, solvObject->getAdressOfVariable(variable_index-1));
				solvObject->setClauseVariableIndex(clausesIndex, i, variable_index-1);
				
				
				//clauses[clausesIndex][i].isNegative = 0;
				solvObject->setNegation(clausesIndex, i, 0);
				

			}else{
			    
				// add variable to clause
			        solvObject->addVaribaleToClause(clausesIndex);
				
				// map clause variable to assignments of the used variables w.r.t. to negation
				
				//clauses[clausesIndex][i].varPointer = &variables[(variable_index*(-1))-1];
				solvObject->setClauseVariablePointer(clausesIndex, i, solvObject->getAdressOfVariable((variable_index*(-1))-1));
				solvObject->setClauseVariableIndex(clausesIndex, i, (variable_index*-1)-1);
				
				
				//clauses[clausesIndex][i].isNegative = 1;
				solvObject->setNegation(clausesIndex, i, 1);
			
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
	
	
	
	// return result
	return solvObject;
	
	
    
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




