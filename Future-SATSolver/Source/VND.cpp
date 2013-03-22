/* 
 * File:   VND.hpp
 * Author: juliushofler
 *
 * Created on 20. März 2013, 21:23
 */

#include "../Headers/VND.hpp"
#include "../Headers/SolvObject.hpp"


VND::VND() {

};

VND::VND(SolvObject solvObject) {

    this->solvObject = solvObject;
};

void VND::search(){

    int i = 1;
    vector <int>::size_type numberOfVariables;
    
    // number of variables
    numberOfVariables = solvObject.getListOfVariables()->size();
    cout << "Number of Vars: " << numberOfVariables << endl;
    
    // check initial state whether it is a solution
    if (solvObject.getNumberOfSatisfiedClauses() == solvObject.getNumberOfClauses()) {
        printf("s SATISFIABLE\n");
    }
    
    // number of neighbourhoods
    vector<int>* neighbourhoods = new vector<int>(3);   // NOTE: change 3 to numberofVariables
    
    
    int sizeOfNeighbourhoods = sizeof(neighbourhoods) / sizeof(neighbourhoods[0]);
    cout << sizeOfNeighbourhoods << endl;
    
    //cout << *(solvObject.getListOfVariables()) << endl;
    
    //for (int j=0;j<sizeOfNeighbourhoods;j++) {
    //    neighbourhoods[j] = *(solvObject.getListOfVariables());
        //cout << "N" << j << ": " << neighbourhoods[j] << endl;
    //    cout << neighbourhoods << endl;;
    //}
    
    
    /*
    int i = 1;
    bool result;
    int trueClauses = 0;
    
    // check all clauses whether they are true
    for (int j=0;j<sizeof(SolvObject.getNumberOfClauses());j++) {
        for (int m=0;m<sizeof(Parser.clauses[j]);m++) {
        
            if ( (m+1) < sizeof(Parser.clauses[j]) ) {
                result = &atoi(Parser.clauses[j][m] || Parser.clauses[j][m+1]);
            }
            
            if (result == 1) {
                break;
            }
        }
        
        trueClauses = trueClauses + result;
    
    }
    
    // check whether all clauses are true
    if ( trueClauses == sizeof(Parser.clauses) ) {
        cout << "s Satisfiable"
        printf("v %d\n", Parser.variables[0]);
    }
    
    // k neighbourhoods
    string neighbourhoods[sizeof(Parser.variables)];
    
    for (int p=0;p<sizeof(Parser.variables);p++) {
        
    }
    
    // k 1-flips
    for (int n=0;n<sizeof(neighbourhoods);n++) {
    
        Parser.variables[n] = '1';
    
    }
    
    
    //while() {
    
    
    //}
*/    
}
