/* 
 * File:   ILS.cpp
 * Author: d
 * 
 * Created on 24. März 2013, 11:00
 */

#include "../Headers/SolvObject.hpp"
#include "../Headers/ILS.hpp"

Ils::Ils(){    
}

Ils::Ils(SolvObject* solvO){    
    this->solvO = solvO;
}

Ils::~Ils(){   
}

/*int Ils:: localSearch(){
    int var = solvO->getListOfVariables()->size();
    int sClauseln = solvO->getNumberOfSatisfiedClauses();
    int temp;
    do{
        temp = sClauseln; 
        for(int i = 0;i<var;i++){
             solvO->changeStateOfVar(i);
             if(solvO->getNumberOfSatisfiedClauses() <= sClauseln){
             solvO->changeStateOfVar(i);
             }else{
             sClauseln = solvO->getNumberOfSatisfiedClauses();
                     cout<< sClauseln << endl;
             } 
        }   
    }while(temp != solvO->getNumberOfSatisfiedClauses() );

    return sClauseln;
 }

int Ils:: localSearch(int flips, int sClauseln){
    int temp;
    int loop = 1;
    if (flips >0){
        cout <<"flips in localSerch(flips): "<< flips<<endl;
    }
    while(loop <= flips){
        while(solvO->createNeighbour(loop) != 1){
            solvO->flipVariablesByFlipperVector();
            solvO->printFlipper();
            temp = solvO->getNumberOfSatisfiedClauses();
            cout <<"temp, aktuelle satClauseln: "<< temp <<endl;
            
            if (temp > sClauseln){
                return temp;
            }else{
                solvO->flipVariablesByFlipperVector();
                solvO->printFlipper();
            }         
        }
        loop +=1;
        cout << "out localSearch, increse flip"<<endl;
        solvO->resetFlipper();
    }
 }

int Ils:: localSearch2(){
    int var = solvO->getListOfVariables()->size();
    int sClauseln = solvO->getNumberOfSatisfiedClauses();
    int index;
    int temp=sClauseln;
    do{
        for(int i = 0;i<var;i++){
         solvO->changeStateOfVar(i);
         if(solvO->getNumberOfSatisfiedClauses() > temp){
             temp = solvO->getNumberOfSatisfiedClauses();
             index = i;
         }
         solvO->changeStateOfVar(i);
        }
        if(temp != sClauseln){
            solvO->changeStateOfVar(index);
            sClauseln = solvO->getNumberOfSatisfiedClauses();
            cout <<solvO->getNumberOfSatisfiedClauses()<<endl;
        }else
            break;
    }while(true);
    return sClauseln;
 }
*/
unsigned int Ils::localSearch(unsigned int flips, unsigned int neighbours, unsigned int satisfieldClausesFromFurtherState, flippercopy &bestFlipper){

    unsigned int startFlips = 1;
    unsigned int tempSClauses = 0;
    bool foundBetterCandidate = 0;

    // reset flippers, for right functionality of this function
    solvO->resetFlipper();

    if (neighbours == 0)
        neighbours = 4294967295;
        
    for (unsigned int cycle = 0; cycle < neighbours; cycle++){
        // find a new flipper (neighbour)
        while(solvO->createNeighbour(startFlips) > 0){
            if (startFlips < solvO->getListOfVariables()->size()){
                startFlips++;
                solvO->resetFlipper();
                cout << startFlips<<endl;
                    if (startFlips>flips){
                        if (foundBetterCandidate == 1)
                            return satisfieldClausesFromFurtherState;
                        else
                            return 0;
                    }
            }
        }

        // flip variables by founded flipper vector
       // solvO->printFlipper();
        solvO->flipVariablesByFlipperVector();

        // check whether candidate is better than further candidate
        tempSClauses = solvO->getNumberOfSatisfiedClauses();

        if (tempSClauses > satisfieldClausesFromFurtherState){
            // set flag
            cout<<"founnd betterCandidate "<<tempSClauses<<endl;
            
            foundBetterCandidate = 1;
            // set as new measure
            satisfieldClausesFromFurtherState = tempSClauses;
            startFlips = 1;
            cycle = 0;
            solvO->resetFlipper();
            if (satisfieldClausesFromFurtherState==solvO->getNumberOfClauses())
                return satisfieldClausesFromFurtherState;
            // save flipper for using it after local search
            //solvO->copyFlipper(bestFlipper);
        }else
            // flip back to look for next candidate
            solvO->flipVariablesByFlipperVector();
        
    }

    // end of local search
    // if a better solution candidate was found flip variables to this state and return founded solution for success or 0 for fail
    if (foundBetterCandidate == 1)
        return solvO->getNumberOfSatisfiedClauses();
    else
        return 0;
    

}

void Ils::IteratedLocalSearchAlgorithm(int randomParam, int maxFlips, int maxNeighbours){
    
    unsigned int SatClauseln = solvO->getNumberOfSatisfiedClauses();
    unsigned int Clauseln = solvO->getNumberOfClauses();
    unsigned int var = solvO->getListOfVariables()->size();
    flippercopy tempFlipper;
    solvO->initializeCopyFlipper(tempFlipper);
    
    unsigned int tempSatClauseln;
    unsigned int tempJump;
    
    if (maxFlips>var){
        cout<<"Es gibt nur "<<var<<" Variablen, maximale Flipanzahl wird auf "<< var<<"gesetzt."<<endl;
        maxFlips = var;
    }
    if( randomParam < 1){
    cout << "random parameter failed > 0"<< endl;
    exit(1);
    }
    
    
    
    while (SatClauseln != Clauseln){
        
        solvO->resetFlipper();
        solvO->resetCopyFlipper(tempFlipper);
        
        //find local min
        tempSatClauseln = localSearch(maxFlips, maxNeighbours, SatClauseln, tempFlipper);
       
        //Verbesseung
        if (tempSatClauseln > SatClauseln){
            
            //found Solution --> break
            if(tempSatClauseln == Clauseln){
                cout <<"found Solution"<<endl;
                break;
            }
        //keine Verbesserung    
        }else{
            solvO->useFlipperCopy(tempFlipper);
            solvO->flipVariablesByFlipperVector();
            cout<< solvO->getNumberOfSatisfiedClauses()<<endl;
              
        }
        
        do{
            tempJump = solvO->random_jump(randomParam);
        }while(tempJump == 0);
        cout<< solvO->getNumberOfSatisfiedClauses()<<endl;
        solvO->copyFlipper(tempFlipper);
        solvO->flipVariablesByFlipperVector();
        cout<< solvO->getNumberOfSatisfiedClauses()<<endl;
        
    }
    cout <<"Solution"<<endl;
}

void Ils::search(){
    /*
     Ils* ils  = new Ils(solvObj);
     ils->search();
    */
    
    
 /*      
    int eingabe =10;
    int jump_var = eingabe;
    int jump_flips;
    int flips = 1;
    flippercopy jumpFlipper, bestFlipper;
    solvO->initializeCopyFlipper(bestFlipper);
    solvO->initializeCopyFlipper(jumpFlipper);
    unsigned int clauseln = solvO->getNumberOfClauses();
    unsigned int var = solvO->getListOfVariables()->size();
    unsigned int sClauseln = solvO->getNumberOfSatisfiedClauses();
    unsigned int tempClauseln;
    
    cout << "Number of Vars: " << var << ", nummer of clauseln: " << clauseln  
         << ", nummer of erfüllte clauseln: " << sClauseln<< endl;
//    sClauseln = localSearch();
    cout <<"localSearch, start position:  " << sClauseln <<endl;
    cout <<"solvO->getNumberOfSatisfiedClauses() "<< solvO->getNumberOfSatisfiedClauses()<<endl;
  */  
    /*
     // example Tobi
     
     	flippercopy flipCop;
        solvObj->initializeCopyFlipper(flipCop);
        solvObj->printFlipper();
        solvObj->printVariablesAssignment();


        solvObj->createNeighbour(1);
        solvObj->printFlipper();
        solvObj->flipVariablesByFlipperVector();
        solvObj->printVariablesAssignment();
        solvObj->addFlippers(flipCop);


        solvObj->createNeighbour(1);
        solvObj->printFlipper();
        solvObj->flipVariablesByFlipperVector();
        solvObj->printVariablesAssignment();
        solvObj->addFlippers(flipCop);

        // now use the added flipper (jump back)
        solvObj->useFlipperCopy(flipCop);
        solvObj->printFlipper();
        solvObj->flipVariablesByFlipperVector();
        solvObj->printVariablesAssignment();


     */
    
/*   
    //found solution
    while(sClauseln != clauseln){
        //random jump != not pertubation
        do{
            jump_flips= solvO->random_jump(jump_var);
        }while(jump_flips == 0);
        //use jump
        solvO->flipVariablesByFlipperVector();
        solvO->copyFlipper(jumpFlipper);
        solvO->resetFlipper();
        //local Search
//        tempClauseln = localSearch(1000000,sClauseln);
        //test Ausgabe
        cout<<"localSearch  " << tempClauseln <<endl;
        //found new min
        if (tempClauseln > sClauseln){
            sClauseln = tempClauseln;
            cout << "tempCl =sClauseln" << sClauseln <<endl;
            jump_var = eingabe;
            flips = 1;
            cout << "localSerch"<< endl;
//            sClauseln = localSearch();
            cout <<"found "<< sClauseln <<endl;
        //not found, jump too
        }else{
            jump_var += eingabe;
            if (jump_var > var){
                cout<< "Unsat"<<endl;
                exit(0);
            }
            //reset jump
        }
    }
*/    
    /* 1.generiere startlösung
     2.störe aktuelle Lösung
     3.berechne neue Lösung mit local Search
     4.enscheide ob neue Lösunng als aktuelle lösung übernommen werden soll
     5.gehe zu 2.*/
    
    
     /* 
procedureIterated Local Search
     *  s0 = generateInitialSoluution
     * s* = LocalSearch
repeat
     * S' = Pertubation(s*, history)
     * S*'= localSearch(S')
     * S* = AceptanceCriterium(S*, S*'  , History)      
until termination condition met
end
     * 
     */
              
}