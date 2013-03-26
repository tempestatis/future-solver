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


void Ils::search(){

    /*
     Ils* ils  = new Ils(solvObj);
     ils->search();
    */
    cout << "NNNNumber of Vars: " << solvO->getListOfVariables()->size() << endl;
    
        //Ils* ils  = new Ils(solvObj);
    //ils->search();
    //me start
    printf("So Start\n");
    /*1.generiere startlösung
     2.störe aktuelle Lösung
     3.berechne neue Lösung mit local Search
     4.enscheide ob neue Lösunng als aktuelle lösung übernommen werden soll
     5.gehe zu 2.*/
    int cl = solvO->getNumberOfClauses();
    int erfCl = solvO->getNumberOfSatisfiedClauses();
    int var = solvO->getListOfVariables()->size();
    bool solution = false;
    //lokales min
    for (int i = 0; i < var; i++){
        solvO->changeStateOfVar(i,1);
        if (solvO->getNumberOfSatisfiedClauses() >= erfCl)
            solvO->changeStateOfVar(i,0);
        else{
            if(cl == solvO->getNumberOfSatisfiedClauses()){
                solution = true;
                break;
            }
               
            erfCl = solvO->getNumberOfSatisfiedClauses();
        }
            
    }
        
    
    while(solvO->getNumberOfSatisfiedClauses() != solvO->getNumberOfClauses()){
        printf("Number Clauseln: %d\nNumber erfüllter Clauseln: %d\n",solvO->getNumberOfClauses(),
                solvO->getNumberOfSatisfiedClauses());
        break;
    }
    //solvObj->getClause(2)->
    
    
    //me end
}