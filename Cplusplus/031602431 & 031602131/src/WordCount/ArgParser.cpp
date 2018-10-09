#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <cstdio>
#include <iostream>

#include "argParser.h"
#include "Tools.h"

using namespace std;

ArgParser::ArgParser(int argc, char* argv[]){
    if (argc != 2){
        perror("Too few or too many arguments");
        filename = string();
    }
    else{
        filename = string(argv[1]);
        FILE* file = fopen(filename.c_str(), "r");
        if (file == NULL) {
            perror("File error");
            filename = string();
        }
        else {
            ;
        }
    }
}

string ArgParser::getFileName() {
    if (filename.empty())
        return "";
    else return filename;
}

int ArgParser::helpDoc(){
    box_draw("The WordCount Program Help");
    cout<<"./WordCount.exe filepath"<<endl;
    return 0;
}
