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
    string getFileName(){
        if (filename.empty())
            return "";
        else return filename;
    }
	string getInputName() {
		if (inputName.empty())
			return "";
		else return inputName;
	}
	string getOutputName() {
		if (outputName.empty())
			return "";
		else return outputName;
	}
	int getPhraseLength() {
		return inPhraseLength;
	}
	int getTopNum() {
		return inTopNum;
	}
	int getTitleWeight() {
		return titleWeight;
	}
    int helpDoc();

private:
    string filename;
	int inPhraseLength, inTopNum, titleWeight;
	string inputName, outputName;
};

#endif