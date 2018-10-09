#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <iostream>
#include <string>

#include "Tools.h"

using namespace std;

class ArgParser{
public:
    ArgParser(int argc, char* argv[]);
    ~ArgParser() {};
    string getFileName();

    int helpDoc();

private:
    string filename;

};

#endif