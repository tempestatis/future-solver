/* 
 * File:   main.cpp
 * Author: Tobias Jaeuthe
 *
 * Created on 19. Januar 2013, 16:50
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <climits>
#include <cfloat>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>



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
#include "../Headers/VNDO.h"
#include "../Headers/VNDF.h"


using namespace std;


bool startSAO(SolvObject* solvObj, unsigned int initialTemperature, unsigned int initialNeighbourhoodBound, unsigned short nifsao, float trfsao, int seed, int restartSeed){
	
	 unsigned int temp = initialTemperature;
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 // for restart
	 srand(restartSeed);
	 unsigned int numberOfVariables = solvObj->getListOfVariables()->size();
	 
	 
	 do {
		 
		 result = simulatedAnnealingOriginal(solvObj, temp, neighbourhoodBound, nifsao, trfsao, seed);
		 
		 if (result == 0){
			 cout << "Solution was found by SAO!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
			 
			 if (temp > 600){
				
				 // if temperature greater than 600 was reached then restart with random variable assignment
				 
				 //do a restart with random assignment
				for (unsigned int i = 0; i < numberOfVariables; i++)
					solvObj->flipRandomVariables((rand() % 5),i);
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


bool startSALF(SolvObject* solvObj, unsigned int initialTemperature, unsigned int initialNeighbourhoodBound, unsigned short nifsao, float trfsao, int seed, int restartSeed){
	
	 unsigned int temp = initialTemperature;
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 // for restart
	 srand(restartSeed);
	 unsigned int numberOfVariables = solvObj->getListOfVariables()->size();
	 
	 
	 do {
		 
		 result = simulatedAnnealingLessFlips(solvObj, temp, neighbourhoodBound, nifsao, trfsao, seed);
		 
		 if (result == 0){
			 cout << "Solution was found by SALF!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
			 
			 if (temp > 600){
				
				 /* if temperature greater than 600 was reached then restart 
				  * with new random variable assignment
				 */
				 
				 //do a restart with random assignment
				for (unsigned int i = 0; i < numberOfVariables; i++)
					solvObj->flipRandomVariables((rand() % 5),i);
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


bool startVNDO(SolvObject* solvObj, unsigned int initialNeighbourhoodBound, unsigned short nifvndo, int restartSeed){
	
	 
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 // for restart
	 srand(restartSeed);
	 unsigned int numberOfVariables = solvObj->getListOfVariables()->size();
	 
	 
	 
	 do {
		 result = VNDO(solvObj, neighbourhoodBound, nifvndo);
		 
		 
		 if (result == 0){
			 cout << "Solution was found by VNDO!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
				//do a restart with random assignment
				for (unsigned int i = 0; i < numberOfVariables; i++)
					solvObj->flipRandomVariables((rand() % 5),i);
		 }
		 
	 } while (result == 1);
	 return 0;
}


bool startVNDF(SolvObject* solvObj, unsigned int initialNeighbourhoodBound, unsigned short fifvndf, int restartSeed){
	
	 
	 unsigned int neighbourhoodBound = initialNeighbourhoodBound;
	 bool result = 1;
	 
	 // for restart
	 srand(restartSeed);
	 unsigned int numberOfVariables = solvObj->getListOfVariables()->size();
	 
	 
	 
	 do {
		 result = VNDF(solvObj, neighbourhoodBound, fifvndf);
		 
		 
		 if (result == 0){
			 cout << "Solution was found by VNDF!" << endl;
			 cout << "s Satisfiable" << endl;
			 solvObj->printVariablesAssignment();
			 return 0;
		 }
		 else{
			 
				//do a restart with random assignment
				for (unsigned int i = 0; i < numberOfVariables; i++)
					solvObj->flipRandomVariables((rand() % 5),i);
				 
		 }
		 
	 } while (result == 1);
	 return 0;
}

void printUsage(){
	
	
	printf("%s","Start the SAT-Solver with following arguments:\n\n"
	"[required]:\n\n"
	"\t-n <number of algorithm[1-6]> \n"
	"Number of algorithm which shall be used for solving.\n"
	"The number of available processor cores"
	"\nshould corresponding to the number of algorithm +1.\n"
	"Each algorithm use 1 core and the main process"
	"\nneeds 1 additional core.\n\n"
	
	"\t--file <instance_file.dimacs> \n\n\n"
	
	"\t-s <restart seed>\n"
	"Random generator for restarting algorithms will use this seed.\n"
	"Needed for: (SAO,SALF,VNDO,VNDF).\n"
	"default: 0\n\n\n"
	 
	"##########################################\n\n\n"
	"[optionally]:\n\n"
	"[Simulated-Annealing-Original-Arguments]:\n\n"
	"\t--tsao <intial temperature [1..10000]>\n"
	"default: 200\n\n"
			  
	"\t--nsao <initial size of neighbourhood [0..1000000]>\n"
	"default: 300\n\n"
			  
	"\t--trfsao <reducing factor for temperature [1..1000000]>\n"
	"Given argument will be divided by 1000>\n"
	"default: 1.0f\n\n"
			  
	"\t--nifsao <increasing factor for neighbourhood size [1..100000]>\n"
	"This factor will add to current neighbourhood size to increase it.\n"
	"default: 100\n\n"
			  
	"\t--seedsao <seed for randomness>\n"
	"If SAO have to be restarted then this seed will be used.\n"
	"default: 0\n\n\n"
			  
	"[Simulated-Annealing-Less-Flips arguments]:\n"
	"\t--tsalf <intial temperature [1..10000]>\n"
	"default: 200\n\n"		  
	
	"\t--nsalf <initial size of neighbourhood [0..1000000]>\n"
	"default: 300\n\n"
			  
	"\t--trfsalf <reducing factor for temperature [1..1000000]>\n"
	"Given argument will be divided by 1000>\n"
	"default: 1.0f\n\n"
			  
	"\t--nifsalf <increasing factor for neighbourhood size [1..100000]>\n"
	"This factor will add to current neighbourhood size to increase it.\n"
	"default: 100\n\n"
			  
	"\t--seedsalf <seed for randomness>\n"
	"If SAO have to be restarted then this seed will be used.\n"
	"default: 0\n\n\n"
	
	"[Variable-Neighborhood-Search-Original arguments]:\n" 
	"\t--nvndo <initial size of neighbourhood [0..1000000]>\n"
	"default: 300\n\n"
			  
	"\t--nifvndo <increasing factor for neighbourhood size [1..100000]>\n"
	"default: 500\n\n\n"
	
	"[Variable-Neighborhood-Search-Flips arguments]:\n"
	"\t--nvndf <initial size of neighbourhood [0..1000000]>\n"
	"default: 300\n\n"
			  
	"\t--fifvndf <increasing factor for flips[0..100]>\n"
	"default: 1\n\n\n"
	
	"[Iterated-Local-Search arguments]:\n"
	"\t--nils <initial size of neighbourhood> [0..1000000]\n"
	"default: 200\n\n"
			  
	"\t--rfils <initial random factor [0..999]>\n"
	"default: 20\n\n"
			  
	"\t--ifrfils <increasing factor for random factor[0..999]>\n"
	"default: 5\n\n"
			  
	"\t--seedils <seed for randomness>\n"
	"default: 0\n\n\n"
			  
	
	
	"[Example]: ./future-solver -n 6 --tsao 100 --nsao 300 --nils 100 --ifrfils 10\n\n\n"
			  
	"#############################\n\n\n"
	
	"Start SAT-Solver to benchmark certain algorithm use the following command:\n"
	"./furture-solver -b <number of algorithm do you want to use> [optionally arguments see above]\n\n"
	"[Algorithm numbers]:\n"
	
	"\tSimulated-Annealing-Originial:\t 0\n"
	"\tUNSAT-checker:\t 1\n"
	"\tSimulated-Annealing-Less-Flips:\t 2\n"
	"\tIterated-Local-Search:\t 3\n"
	"\tVariable-Neighbourhood-Descent-Original:\t 4\n"
	"\tVariable-Neighbourhood-Descent-Flips:\t 5\n"
	
	
	"[Example]:\n"
	"Following commandline will start ILS algorithm with changed value of increasing random factor.\n"
	"./future-solver -b 5 -ifrfils 0.1:\n\n\n\n");
	
}



	
int main(int argc, char* argv[]) {
	
	// default paramters:
	// number of processes (algorithm)
	short numberOfProcesses = 1;
	
	// initial temperatures
	unsigned short tsao = 200, tsalf = 200;
	
	// initial neighbourhood bound
	unsigned int nsao = 300, nsalf = 300, nvndo = 300, nvndf = 300, nils = 200;
	
	// reducing factor for temperature
	float trfsao = 1.0f, trfsalf = 1.0f;
	
	// increasing factor for neighbourhood bound
	unsigned short nifsao = 100, nifsalf = 100, nifvndo = 500;
	
	// increasing factor for flips
	unsigned short fifvndf = 1;
	
	/* initial random factor 
	 * random generator has a range of 1000 numbers
	 * evaluation in ILS:
	 * if (randomNumber < rfils) then ...
	 * 10 representate the randomness of 10/1000
	 */
	unsigned short rfils = 20;
	
	// increasing factor for random factor
	unsigned short ifrfils = 5;
	
	// random seeds
	int seedsao = 0, seedsalf = 0, seedils = 0, restartSeed = 0;
	
	// benchmark algorithm number
	char benchmark = -1;
	
	char* fileName = (char*)"";
	
	static struct option long_options[] =
             {
               /* These options set a flag. */
               //{"verbose", no_argument,       &verbose_flag, 1},
               //{"brief",   no_argument,       &verbose_flag, 0},
               /* These options don't set a flag.
                  We distinguish them by their indices. */
               {"help",     required_argument,       0, 1},
               {"file",  required_argument,       0, 2},
               {"tsao",  required_argument, 0, 3},
					{"nsao",  required_argument, 0, 5},
					{"trfsao",  required_argument, 0, 10},
					{"nifsao",  required_argument, 0, 12},
					{"seedsao",  required_argument, 0, 18},
					{"tsalf",  required_argument, 0, 6},
					{"nsalf",  required_argument, 0, 9},
					{"trfsalf",  required_argument, 0, 11},
					{"nifsalf",  required_argument, 0, 13},
					{"seedsalf",  required_argument, 0, 19},
					{"nvndo",  required_argument, 0, 8},
					{"nifvndo",  required_argument, 0, 14},
					{"nvndf",  required_argument, 0, 9},
					{"fifvndf",  required_argument, 0, 15},
					{"nils",  required_argument, 0, 7},
					{"rfils",  required_argument, 0, 16},
					{"ifrfils",  required_argument, 0, 17},
					{"seedils",  required_argument, 0, 20},
					
               {0, 0, 0, 0}
             };
	
	
	
	
	
	// parse command line
	// option flags:
	int optchar;
	
	
	
	while ((optchar = getopt_long (argc, argv, "b:n:s:h", long_options, &optchar)) != -1){
		
		switch(optchar){
			case 'n':
					if (atoi(optarg) < 1 || atoi(optarg) > 7){
						cout << "Only 1..7 parallel processes available!" << endl;
						return 1;
					}
					else
						numberOfProcesses = atoi(optarg);
					break;
				
				
				break;
				
			case 's':
				if (atoi(optarg) < INT_MIN || atoi(optarg) > INT_MAX){
					cout << "Restart Seed must be one of this [" << INT_MIN << " .. " << INT_MAX << "]"<< endl;
					return 1;
				} else
					restartSeed = atoi(optarg);
				
				
						  
				break;
			
			case 'b':
				// get benchmark option
				if (atoi(optarg) < 0  || atoi(optarg) > 5 ){
					cout << "You choose a invalid number for algorithm, pls check the help page!" << endl;
					return 1;
				}else
					benchmark = atoi(optarg);
		
				
				break;
			case 'h':
				// print help
				printUsage();
				return 0;
			case 1:
				// print help
				printUsage();
				return 0;
				
			case 2:
				fileName = optarg;
				break;
				
			case 3:
				// get initial temperature for SAO
				if (atoi(optarg) > 10000  || atoi(optarg) < 1){
					cout << "The value for tsao must be one of this [1 .. 10000]"  << endl;
					return 1;
				}else
					tsao = (unsigned short)atoi(optarg);
				break;
			case 4:
				// get initial temperature for SALF
				if (atoi(optarg) > 10000  || atoi(optarg) < 1){
					cout << "The value for tsalf must be one of this [1 .. 10000] " << endl;
					return 1;
				}else
					tsalf = (unsigned short)atoi(optarg);
				break;
			case 5:
				// get initial neighbourhood bound for SAO
				if (strtoul(optarg,NULL,0) > 1000000  || strtoul(optarg,NULL,0) < 0 ){
					cout << "The value for nsao must be one of this [0 .. 1000000]" << endl;
					return 1;
				}else
					nsao = (unsigned int)strtoul(optarg,NULL,0);
				break;
			case 6:
					// get initial neighbourhood bound for SALF
					if (strtoul(optarg,NULL,0) > 1000000  || strtoul(optarg,NULL,0) < 0 ){
						cout << "The value for nsalf must be one of this [0 .. 1000000]" << endl;
						return 1;
					}else
						nsalf = (unsigned int)strtoul(optarg,NULL,0);
					break;
			case 7:
					// get initial neighbourhood bound for ILS
					if ((unsigned int)strtoul(optarg,NULL,0) > 1000000  || (unsigned int)strtoul(optarg,NULL,0) < 0 ){
						cout << "The value for nsao must be one of this [0 .. 1000000]" << endl;
						return 1;
					}else
						nils = (unsigned int)strtoul(optarg,NULL,0);
					break;
			case 8:
					// get initial neighbourhood bound for VNDO
					if ((unsigned int)strtoul(optarg,NULL,0) > 1000000  || (unsigned int)strtoul(optarg,NULL,0) < 0 ){
						cout << "The value for nvndo must be one of this [0 .. 1000000]" << endl;
						return 1;
					}else
						nvndo = (unsigned int)strtoul(optarg,NULL,0);
					break;
			case 9:
					// get initial neighbourhood bound for VNDF
					if ((unsigned int)strtoul(optarg,NULL,0) > 1000000  || (unsigned int)strtoul(optarg,NULL,0) < 0 ){
						cout << "The value for nvndf must be one of this [0 .. 1000000]"  << endl;
						return 1;
					}else
						nvndf = (unsigned int)strtoul(optarg,NULL,0);
					break;
			case 10:
					// get reducing factor for temperature (SAO)
					if (atoi(optarg) > 1000000  || atoi(optarg) < 1 ){
						cout << "The value for trfsao must be one of this [1 .. 1000000]" << endl;
						return 1;
					}else
						trfsao = ((float)atoi(optarg)/1000);
					break;
			case 11:
					// get reducing factor for temperature (SALF)
					if (atoi(optarg) > 1000000  || atoi(optarg) < 1 ){
						cout << "The value for trfsalf must be one of this [1 .. 1000000]" << endl;
						return 1;
					}else
						trfsalf = ((float)atoi(optarg)/1000);
					break;
			case 12:
					// get increasing factor for neighbourhood bound (SAO)
					if (atoi(optarg) > 100000  || atoi(optarg) < 1 ){
						cout << "The value for nifsao must be one of this [1 .. 100000]" << endl;
						return 1;
					}else
						nifsao = atoi(optarg);
					break;
			case 13:
					// get increasing factor for neighbourhood bound (SALF)
					if (atoi(optarg) > 100000  || atoi(optarg) < 1 ){
						cout << "The value for nifsalf must be one of this [1 .. 100000]" << endl;
						return 1;
					}else
						nifsalf = atoi(optarg);
					break;
			case 14:
					// get initial increasing factor for neighbourhood bound (VNDO)
					if (atoi(optarg) > 100000  || atoi(optarg) < 1 ){
						cout << "The value for nifvndo must be one of this [1 .. 100000]" << endl;
						return 1;
					}else
							nifvndo = atoi(optarg);
					break;
			case 15:
					// get initial increasing factor for flips (VNDF)
					if (atoi(optarg) > 100  || atoi(optarg) < 0 ){
						cout << "The value for fifvndf must be one of this [0 .. 100] " << endl;
						return 1;
					}else
						fifvndf = atoi(optarg);
					break;
			case 16:
				   // get initial random factor (ILS)
					if (atoi(optarg) < 0  || atoi(optarg) > 999 ){
						cout << "The value for rfils must be between 0 .. 999" << endl;
						return 1;
					}else
						rfils = atoi(optarg);
					break;
			case 17:
					// get random reducing factor (ILS)
					if (atoi(optarg) > 999  || atoi(optarg) < 0 ){
						cout << "The value for ifrfils should be [0..999]"  << endl;
						return 1;
					}else
						ifrfils = atoi(optarg);
					break;
			case 18:
					// get seed (SOA)
					if (atoi(optarg) < INT_MIN  || atoi(optarg) > INT_MAX ){
						cout << "The value for seedsao must be between " << INT_MIN << " .. " << INT_MAX << endl;
						return 1;
					}else
						seedsao = atoi(optarg);
					break;
			case 19:
					// get seed (SOLF)
					if (atoi(optarg) < INT_MIN  || atoi(optarg) > INT_MAX ){
						cout << "The value for seedsalf must be between " << INT_MIN << " .. " << INT_MAX << endl;
						return 1;
					}else
						seedsalf = atoi(optarg);
			case 20:
					// get seed (ILS)
					if (atoi(optarg) < INT_MIN  || atoi(optarg) > INT_MAX ){
						cout << "The value for seedils must be between " << INT_MIN << " .. " << INT_MAX << endl;
						return 1;
					}else
						seedils = atoi(optarg);

					break;
			}
			
		}
		if (strcmp(fileName, "")==0){
			cout << "Which instance file shall I use? O_o" << endl;
				return 1;
		}
	/*debug
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
	
	cout << "increasing factor for neighbourhood bound vndf: " << fifvndf << endl;
	
	cout << "initial random factor ils: " << rfils << endl;
	
	cout << "increasing random factor ils: " << ifrfils << endl;
	
	cout << "seedils: " << seedils << endl;
	
	cout << "seedsao: " << seedsao << endl;
	
	cout << "seedsalf: " << seedils << endl;
	
	cout << "fileName: " << fileName << endl;
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

			  FILE* file = fopen( fileName, "rb" );

				// check whether file exists
				if (file == NULL){
					perror("Error while opening given instance file!");
					abort();
				}


				SolvObject* solvObj = parse(file);

			printf("agorithmId: %d",algorithmId);
		  switch (algorithmId){
			  
			  case 5: 
				  // start julius 2
				  printf("start VNDF\n");
				  startVNDF(solvObj, nvndf, fifvndf, restartSeed);
				  break;
			  case 4:
				  // start julius 1
				  printf("start VNDO\n");
				  startVNDO(solvObj, nvndo, nifvndo, restartSeed);
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
				  startSALF(solvObj, tsalf, nsalf, nifsalf, trfsalf, seedsalf, restartSeed);
				  
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
				  startSAO(solvObj, tsao, nsao, nifsao, trfsao, seedsao, restartSeed);
				  break;
								  
		  }





			 exit(0);
		  }
	}
		
		//Wait for children to exit. 
		int status;
		pid_t pid;

		pid = wait(&status);
		//printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		
		// kill other children
		for (int i = 0; i < numberOfProcesses; i++){
			kill(pids[i], 9);
		}
		
		return 0;
		
	} else { 
		
		//################################################
		// BENCHMARK SECTION:
		//################################################
		
		FILE* file = fopen( fileName, "rb" );

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
				  printf("start VNDF\n");
				  startVNDF(solvObj, nvndf, fifvndf, restartSeed);
				  break;
			  case 4:
				  // start julius 1
				  printf("start VNDO\n");
				  startVNDO(solvObj, nvndo, nifvndo, restartSeed);
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
				  startSALF(solvObj, tsalf, nsalf, nifsalf, trfsalf, seedsalf, restartSeed);
				  
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
				  startSAO(solvObj, tsao, nsao, nifsao, trfsao, seedsao, restartSeed);
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


	
