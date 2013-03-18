/* 
 * File:   main.cpp
 * Author: tobias
 *
 * Created on 19. Januar 2013, 16:50
 */

#include <cstdlib>

#include "Parser.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    printf("test");
    FILE* file = fopen( argv[1], "rb" );	
    Parser* parser = new Parser();
    parser->parse(file);
    return 0;
}

