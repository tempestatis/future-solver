/* 
 * File:   main.cpp
 * Author: tobias
 *
 * Created on 19. Januar 2013, 16:50
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <climits>
#include <cfloat>
#include <cstring>



#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>



#include "../Headers/Parser.hpp"
#include "../Headers/BitVector.hpp"
#include "../Headers/SimulatedAnnealingOriginal.h"
#include "../Headers/SimulatedAnnealingLessFlips.h"
#include "../Headers/UnsatChecker.h"
#include "../Headers/ILS.h"
#include "../Headers/anyoption.h"


using namespace std;


/*
 * 
 */

bool startSAO(SolvObject* solvObj, unsigned int initialTemperature, unsigned int initialNeighbourhoodBound, unsigned short nifsao, float trfsao, int seed){
	
	 unsigned int temp = initialTemperature;
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 
	 do {
		 
		 result = simulatedAnnealingOriginal(solvObj, temp, neighbourhoodBound, nifsao, trfsao, seed);
		 
		 if (result == 0){
			 cout << "Solution was found by SAO!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
			 
			 if (temp == 600){
				
				 // if temperature 600 was reached then restart with random variable assignment
				 solvObj->flipRandomVariables();
				 temp = initialTemperature;
				 neighbourhoodBound = initialNeighbourhoodBound;
				 
			 } else
			 {
				temp = temp + 100;
				neighbourhoodBound = neighbourhoodBound + 100;
				
			 }
		 }
		 
	 } while (result == 1);
	 return 0;
}


bool startSALF(SolvObject* solvObj, unsigned int initialTemperature, unsigned int initialNeighbourhoodBound, unsigned short nifsao, float trfsao, int seed){
	
	 unsigned int temp = initialTemperature;
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 
	 do {
		 
		 result = simulatedAnnealingLessFlips(solvObj, temp, neighbourhoodBound, nifsao, trfsao, seed);
		 
		 if (result == 0){
			 cout << "Solution was found by SALF!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
			 
			 if (temp == 600){
				
				 /* if temperature 600 was reached then restart 
				  * with new random variable assignment
				 */
				 solvObj->flipRandomVariables();
				 temp = initialTemperature;
				 neighbourhoodBound = initialNeighbourhoodBound;
				 
			 } else
			 {
				temp = temp + 100;
				neighbourhoodBound = neighbourhoodBound + 100;
				
			 }
		 }
		 // while no result was found
	 } while (result == 1);
	 return 0;
}


	
int main(int argc, char* argv[]) {
	
	// default paramters:
	// number of processes (algorithm)
	short numberOfProcesses = 1;
	
	// initial temperatures
	unsigned short tsao = 200, tsalf = 200;
	
	// initial neighbourhood bound
	unsigned int nsao = 300, nsalf = 300, nvndo = 300, nvndf = 300, nils = 300;
	
	// reducing factor for temperature
	float trfsao = 1.0f, trfsalf = 1.0f;
	
	// increasing factor for neighbourhood bound
	unsigned short nifsao = 100, nifsalf = 100, nifvndo = 100, nifvndf = 100;
	
	/* initial random factor 
	 * random generator has a range of 1000 numbers
	 * evaluation in ILS:
	 * if (randomNumber < rfils) then ...
	 * 10 representate the randomness of 10/1000
	 */
	unsigned short rfils = 10;
	
	// increasing factor for random factor
	unsigned short ifrfils = 1;
	
	// random seeds
	int seedsao = 0, seedsalf = 0, seedils = 0;
	
	// benchmark algorithm number
	char benchmark = -1;
	
	
	
	// parse command line
	AnyOption *opt = new AnyOption();
	
	opt->addUsage("Start the SAT-Solver with following arguments:\n\n");
	opt->addUsage("[required]:\n\n");
	opt->addUsage("\t-n <number of algorithm (1-7 should be equal to number of cpu's)> \n");
	opt->addUsage("\t--file <instance_file.dimacs> \n\n\n");
	
	 
	opt->addUsage("[optionally]:\n\n");
	opt->addUsage("[Simulated-Annealing-Original-Arguments]:\n");
	opt->addUsage("\t--tsao <intial temperature>\n");
	opt->addUsage("\t--nsao <initial size of neighbourhood>\n");
	opt->addUsage("\t--trfsao <reducing factor for temperature>\n");
	opt->addUsage("\t--nifsao <increasing factor for neighbourhood size>\n");
	opt->addUsage("\t--seedsao <seed for randomness>\n\n");
	
	opt->addUsage("[Simulated-Annealing-Less-Flips arguments]:\n");
	opt->addUsage("\t--tsalf <intial temperature>\n");
	opt->addUsage("\t--nsalf <initial size of neighbourhood>\n");
	opt->addUsage("\t--trfsalf <reducing factor for temperature>\n");
	opt->addUsage("\t--nifsalf <increasing factor for neighbourhood size>\n");
	opt->addUsage("\t--seedsalf <seed for randomness>\n\n");
	
	opt->addUsage("[Variable-Neighborhood-Search-Original arguments]:\n"); 
	opt->addUsage("\t--nvndo <initial size of neighbourhood>\n");
	opt->addUsage("\t--nifvndo <increasing factor for neighbourhood size>\n\n");
	
	opt->addUsage("[Variable-Neighborhood-Search-Flips arguments]:\n");
	opt->addUsage("\t--nvndf <initial size of neighbourhood>\n");
	opt->addUsage("\t--nifvndf <increasing factor for neighbourhood size>\n\n");
	
	opt->addUsage("[Iterated-Local-Search arguments]:\n");
	opt->addUsage("\t--nils <initial size of neighbourhood>\n");
	opt->addUsage("\t--rfils <initial random factor [0..999]>\n");
	opt->addUsage("\t--ifrfils <increasing factor for random factor>\n\n\n");
	opt->addUsage("\t--seedils <seed for randomness>\n\n");
	
	opt->addUsage("[Example]: ./future-solver -n 6 --tsao 100 --nsao 300 --nils 100 --ifrfils 10\n\n\n");
	
	opt->addUsage("Start SAT-Solver to benchmark certain algorithm use the following command:\n");
	opt->addUsage("./furture-solver -b <number of algorithm do you want to use> [optionally arguments see above]\n\n");
	opt->addUsage("[Algorithm numbers]:\n");
	
	opt->addUsage("\tSimulated-Annealing-Originial:\t 0\n");
	opt->addUsage("\tUNSAT-checker:\t 1\n");
	opt->addUsage("\tSimulated-Annealing-Less-Flips:\t 2\n");
	opt->addUsage("\tIterated-Local-Search:\t 3\n");
	opt->addUsage("\tVariable-Neighbourhood-Descent-Original:\t 4\n");
	opt->addUsage("\tVariable-Neighbourhood-Descent-Flips:\t 5\n");
	
	
	opt->addUsage("[Example]:\n");
	opt->addUsage("Following commandline will start ILS algorithm with changed value of increasing random factor.\n");
	opt->addUsage("./future-solver -b 5 -ifrfils 0.1:\n");
	
	opt->setCommandFlag(  "help", 'h' );   /* a flag (takes no argument), supporting long and short form */ 
	opt->setCommandOption('n');
	opt->setCommandOption("tsao");
	opt->setCommandOption("nsao");
	opt->setCommandOption("trfsao");
	opt->setCommandOption("nifsao");
	opt->setCommandOption("seedsao");
	opt->setCommandOption("tsalf");
	opt->setCommandOption("nsalf");
	opt->setCommandOption("trfsalf");
	opt->setCommandOption("nifsalf");
	opt->setCommandOption("seedsalf");
	opt->setCommandOption("nvndo");
	opt->setCommandOption("nifvndo");
	opt->setCommandOption("nvndf");
	opt->setCommandOption("nifvndf");
	opt->setCommandOption("nils");
	opt->setCommandOption("rfils");
	opt->setCommandOption("ifrfils");
	opt->setCommandOption("seedils");
	opt->setCommandOption("file");
	opt->setCommandOption('b');
	
	
	/* go through the command line and get the options  */
	opt->processCommandArgs( argc, argv );
	
	if( ! opt->hasOptions()) { /* print usage if no options */
		opt->printUsage();
		delete opt;
		return 0;
	}
	
	if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) ) {
		opt->printUsage();
		delete opt;
		return 0;
	}
	
	
	// get number of processes
	if( opt->getValue( 'n' ) != NULL){
		numberOfProcesses = atoi(opt->getValue('n'));
		
		// exception handling
		if (numberOfProcesses < 1 || numberOfProcesses > 7){
			cout << "Only 1..7 parallel processes available!" << endl;
			return 1;
		}
	}
	
	// get initial temperature for SAO
	if( opt->getValue( "tsao" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("tsao")) > USHRT_MAX  || atoi(opt->getValue("tsao")) < 1){
			cout << "The value for tsao must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			tsao = atoi(opt->getValue("tsao"));
	}
	
	// get initial temperature for SALF
	if( opt->getValue( "tsalf" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("tsalf")) > USHRT_MAX  || atoi(opt->getValue("tsalf")) < 1){
			cout << "The value for tsalf must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			tsalf = atoi(opt->getValue("tsalf"));
	}
	
	// get initial neighbourhood bound for SAO
	if( opt->getValue( "nsao" ) != NULL){
		
		
		// exception handling
		if ((unsigned int)strtoul(opt->getValue("nsao"),NULL,0) > UINT_MAX  || (unsigned int)strtoul(opt->getValue("nsao"),NULL,0) < 1 ){
			cout << "The value for nsao must be between 1 .. " << UINT_MAX << endl;
			return 1;
		}else
			nsao = (unsigned int)strtoul(opt->getValue("nsao"),NULL,0);
			
	}
	
	// get initial neighbourhood bound for SALF
	if( opt->getValue( "nsalf" ) != NULL){
		
		
		// exception handling
		if ((unsigned int)strtoul(opt->getValue("nsalf"),NULL,0) > UINT_MAX  || (unsigned int)strtoul(opt->getValue("nsalf"),NULL,0) < 1 ){
			cout << "The value for nsalf must be between 1 .. " << UINT_MAX << endl;
			return 1;
		}else
			nsalf = (unsigned int)strtoul(opt->getValue("nsalf"),NULL,0);
	}
	
	// get initial neighbourhood bound for ILS
	if( opt->getValue( "nils" ) != NULL){
		
		
		// exception handling
		if ((unsigned int)strtoul(opt->getValue("nils"),NULL,0) > UINT_MAX  || (unsigned int)strtoul(opt->getValue("nils"),NULL,0) < 1 ){
			cout << "The value for nsao must be between 1 .. " << UINT_MAX << endl;
			return 1;
		}else
			nils = (unsigned int)strtoul(opt->getValue("nils"),NULL,0);
			
	}
	
	// get initial neighbourhood bound for VNDO
	if( opt->getValue( "nvndo" ) != NULL){
		
		
		// exception handling
		if ((unsigned int)strtoul(opt->getValue("nvndo"),NULL,0) > UINT_MAX  || (unsigned int)strtoul(opt->getValue("nvndo"),NULL,0) < 1 ){
			cout << "The value for nvndo must be between 1 .. " << UINT_MAX << endl;
			return 1;
		}else
			nvndo = (unsigned int)strtoul(opt->getValue("nvndo"),NULL,0);
			
	}
	
	// get initial neighbourhood bound for VNDF
	if( opt->getValue( "nvndf" ) != NULL){
		
		
		// exception handling
		if ((unsigned int)strtoul(opt->getValue("nvndf"),NULL,0) > UINT_MAX  || (unsigned int)strtoul(opt->getValue("nvndf"),NULL,0) < 1 ){
			cout << "The value for nvndf must be between 1 .. " << UINT_MAX << endl;
			return 1;
		}else
			nvndf = (unsigned int)strtoul(opt->getValue("nvndf"),NULL,0);
			
	}
	
		// get reducing factor for temperature (SAO)
	if( opt->getValue( "trfsao" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("trfsao")) > FLT_MAX  || atoi(opt->getValue("trfsao")) < 0.001 ){
			cout << "The value for trfsao must be between 0.001 .. " << FLT_MAX << endl;
			return 1;
		}else
			trfsao = atoi(opt->getValue("trfsao"));
	}
	
	// get reducing factor for temperature (SALF)
	if( opt->getValue( "trfsalf" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("trfsalf")) > FLT_MAX  || atoi(opt->getValue("trfsalf")) < 0.001 ){
			cout << "The value for trfsalf must be between 0.001 .. " << FLT_MAX << endl;
			return 1;
		}else
			trfsalf = atoi(opt->getValue("trfsalf"));
	}
	
	
	// get initial increasing factor for neighbourhood bound (SAO)
	if( opt->getValue( "nifsao" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("nifsao")) > USHRT_MAX  || atoi(opt->getValue("nifsao")) < 1 ){
			cout << "The value for nifsao must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			nifsao = atoi(opt->getValue("nifsao"));
	}
	
	// get initial increasing factor for neighbourhood bound (SALF)
	if( opt->getValue( "nifsalf" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("nifsalf")) > USHRT_MAX  || atoi(opt->getValue("nifsalf")) < 1 ){
			cout << "The value for nifsalf must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			nifsalf = atoi(opt->getValue("nifsalf"));
	}
	
	
	// get initial increasing factor for neighbourhood bound (VNDO)
	if( opt->getValue( "nifvndo" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("nifvndo")) > USHRT_MAX  || atoi(opt->getValue("nifvndo")) < 1 ){
			cout << "The value for nifvndo must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			nifvndo = atoi(opt->getValue("nifvndo"));
	}
	
	
	// get initial increasing factor for neighbourhood bound (VNDF)
	if( opt->getValue( "nifvndf" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("nifvndf")) > USHRT_MAX  || atoi(opt->getValue("nifvndf")) < 1 ){
			cout << "The value for nifvndf must be between 1 .. " << USHRT_MAX << endl;
			return 1;
		}else
			nifvndf = atoi(opt->getValue("nifvndf"));
	}
	
   // get initial random factor (ILS)
	if( opt->getValue( "rfils" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("rfils")) < 0  || atoi(opt->getValue("rfils")) > 999 ){
			cout << "The value for rfils must be between 0 .. 999" << endl;
			return 1;
		}else
			rfils = atoi(opt->getValue("rfils"));
	}	
	
	// get random reducing factor (ILS)
	if( opt->getValue( "ifrfils" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("ifrfils")) > USHRT_MAX  || atoi(opt->getValue("ifrfils")) < 0 ){
			cout << "The value for ifrfils should be [0..999]"  << endl;
			return 1;
		}else
			ifrfils = atoi(opt->getValue("ifrfils"));
	}	
	
	// get seed (SOA)
	if( opt->getValue( "seedsao" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("seedsao")) < INT_MIN  || atoi(opt->getValue("seedsao")) > INT_MAX ){
			cout << "The value for seedsao must be between " << INT_MIN << " .. " << INT_MAX << endl;
			return 1;
		}else
			seedsao = atof(opt->getValue("seedsao"));
	}	
	
	// get seed (SOLF)
	if( opt->getValue( "seedsalf" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("seedsalf")) < INT_MIN  || atoi(opt->getValue("seedsalf")) > INT_MAX ){
			cout << "The value for seedsalf must be between " << INT_MIN << " .. " << INT_MAX << endl;
			return 1;
		}else
		  seedsalf = atof(opt->getValue("seedsalf"));
	}	
	
	// get seed (ILS)
	if( opt->getValue( "seedils" ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue("seedils")) < INT_MIN  || atoi(opt->getValue("seedils")) > INT_MAX ){
			cout << "The value for seedils must be between " << INT_MIN << " .. " << INT_MAX << endl;
			return 1;
		}else
		  seedils = atof(opt->getValue("seedils"));
	}	
	
	
	// get benchmark option
	if( opt->getValue( 'b' ) != NULL){
		
		
		// exception handling
		if (atoi(opt->getValue('b')) < 0  || atoi(opt->getValue('b')) > 5 ){
			cout << "You choose a invalid number for algorithm, pls check the help page!" << endl;
			return 1;
		}else{
			benchmark = atoi(opt->getValue('b'));
		}
		  
	}	
	
	if (opt->getValue("file") == NULL){
		cout << "Which instance file shall I use? O_o" << endl;
			return 1;
	} 
	/*
	//debug:
	cout << "number of processes: " << numberOfProcesses << endl;
	
	cout << "initial temperature sao: " << tsao << endl;
	
	cout << "initial temperature salf: " << tsalf << endl;
	
	cout << "initial neighbourhood bound sao: " << nsao << endl;
	
	cout << "initial neighbourhood bound salf: " << nsalf << endl;
	
	cout << "initial neighbourhood bound vndo: " << nvndo << endl;
	
	cout << "initial neighbourhood bound vndf: " << nvndf << endl;
	
	cout << "reducing factor for temperature sao: " << trfsao << endl;
	
	cout << "reducing factor for temperature salf: " << trfsalf << endl;
	
	cout << "increasing factor for neighbourhood bound sao: " << nifsao << endl;
	
	cout << "increasing factor for neighbourhood bound salf: " << nifsalf << endl;
	
	cout << "increasing factor for neighbourhood bound vndo: " << nifvndo << endl;
	
	cout << "increasing factor for neighbourhood bound vndf: " << nifvndf << endl;
	
	cout << "initial random factor ils: " << rfils << endl;
	
	cout << "increasing random factor ils: " << ifrfils << endl;
	
	
	
	
	*/
	
	
	
	//no benchmark use all available processes
	if (benchmark == -1){
	
		//################################################
		// REGULAR MODE SECTION:
		//################################################
	
		// fork processes

		pid_t pids[numberOfProcesses];
		unsigned char i;
		unsigned char algorithmId = numberOfProcesses;



		// Start children. 
		for (i = 0; i < numberOfProcesses; ++i) {

			algorithmId--;

		  if ((pids[i] = fork()) < 0) {
			 perror("fork");
			 abort();
		  } else if (pids[i] == 0) {

			  FILE* file = fopen( opt->getValue("file"), "rb" );

				// check whether file exists
				if (file == NULL){
					perror("Error while opening given instance file!");
					abort();
				}


				SolvObject* solvObj = parse(file);


			 // start algorithms: 
			  switch (algorithmId){
				  case 5: 
					  // start julius 2
					  printf("start julius2\n");
					  break;
				  case 4:
					  // start julius 1
					  printf("start julius1\n");
					  break;
				  case 3:
					  // start flo
					  printf("start ILS\n");
					  if (iteratedLocalSearchAlgorithm(solvObj, nils, rfils, ifrfils, seedils) == 0){
						  cout << "s SATISFIABLE" << endl;
						  solvObj->printVariablesAssignment();
					  }
					  break;
				  case 2:

					  // start simulated annealing less flips
					  printf("start SALF\n");
					  startSALF(solvObj, tsao, nsao, nifsao, trfsao, seedsao);

					  break;
				  case 1:

					  // start Unsat checker
					  printf("start UNSATCHECKER\n");
					  if (checkUnsatisfiability(solvObj) == 0){
							cout << "s UNSATISFIABLE" << endl;
						} else
					 {
						cout << "s SATISFIABLE" << endl;
						solvObj->printVariablesAssignment();

						}

					  break;
				  case 0:
						// start simulated annealing original  
					  printf("start SAO\n");
					  startSAO(solvObj, tsao, nsao, nifsao, trfsao, seedsao);
					  break;

			  }




			 exit(0);
		  }
	}

		//Wait for children to exit. 
		int status;
		pid_t pid;

		pid = wait(&status);
		printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		return 0;
		
	} else { 
		
		//################################################
		// BENCHMARK SECTION:
		//################################################
		
		FILE* file = fopen( opt->getValue("file"), "rb" );

		// check whether file exists
		if (file == NULL){
			perror("Error while opening given instance file!");
			abort();
		}


		SolvObject* solvObj = parse(file);

		// start main process with choosen algorithm
		
		  switch (benchmark){
			  case 5: 
				  // start julius 2
				  printf("start julius2\n");
				  break;
			  case 4:
				  // start julius 1
				  printf("start julius1\n");
				  break;
			  case 3:
				  // start flo
				  printf("start ILS\n");
				  if (iteratedLocalSearchAlgorithm(solvObj, nils, rfils, ifrfils, seedils) == 0){
					  cout << "s SATISFIABLE" << endl;
					  solvObj->printVariablesAssignment();
				  }
				  break;
			  case 2:
				  
				  // start simulated annealing less flips
				  printf("start SALF\n");
				  startSALF(solvObj, tsao, nsao, nifsao, trfsao, seedsao);
				  
				  break;
			  case 1:
				  
				  // start Unsat checker
				  printf("start UNSATCHECKER\n");
				  if (checkUnsatisfiability(solvObj) == 0){
						cout << "s UNSATISFIABLE" << endl;
					} else
				 {
					cout << "s SATISFIABLE" << endl;
					solvObj->printVariablesAssignment();
					
					}
				  
				  break;
			  case 0:
					// start simulated annealing original  
				  printf("start SAO\n");
				  startSAO(solvObj, tsao, nsao, nifsao, trfsao, seedsao);
				  break;
								  
		  }
	}

}
	
	
	
    
	// stur:							// SAO:								// SALS
	// 3 secs ksat8				1 sec by 100,100				200 secs 200,1000
	// 12 secs ksat6        0,5 sec by 100,100			242 secs by 200,1000

	// ksat 10						1m 23
	// ksat 11						13 sec 500, 200 relativ verlässlich 400,200 geht auch
	
	
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 

    






/* for testing in main
    printf("Size: %d\n",solvObj->getListOfVariables()->size());
    
    a = solvObj->getListOfVariables();
    
    for (int i = 0; i < solvObj->getListOfVariables()->size(); i++)
	 
    
	printf("VAR: %d   Adress: %p\n",(*a)[i], &((*a)[i]));
    
    solvObj->changeStateOfVar(50,1);
	 //solvObj->changeStateOfVar(1,1);
    
    for (int i = 0; i < solvObj->getListOfVariables()->size(); i++)
	 
    
	printf("VAR: %d   Adress: %p\n",(*a)[i], &((*a)[i]));
    
   // printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(0).varPointer,*(solvObj->getClause(0)->at(0).varPointer),solvObj->getClause(0)->at(0).isNegative);
   // printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(1).varPointer,*(solvObj->getClause(0)->at(1).varPointer),solvObj->getClause(0)->at(1).isNegative);
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(0)->at(2).varPointer,*(solvObj->getClause(0)->at(2).varPointer),solvObj->getClause(0)->at(2).isNegative);
    
    
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(1)->at(0).varPointer,*(solvObj->getClause(1)->at(0).varPointer),solvObj->getClause(1)->at(0).isNegative);
    //printf("Clausevar: %p %d %d\n",solvObj->getClause(1)->at(1).varPointer,*(solvObj->getClause(1)->at(1).varPointer),solvObj->getClause(1)->at(1).isNegative);
    
    printf("number of satisfied clauses: %d\n",solvObj->getNumberOfSatisfiedClauses());
	 
    */


	
