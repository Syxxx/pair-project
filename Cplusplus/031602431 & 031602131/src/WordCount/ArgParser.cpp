#define _CRT_SECURE_NO_WARNINGS

#include "argParser.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include "Tools.h"

using namespace std;


ArgParser::ArgParser(int argc, char* argv[]){
	inPhraseLength = -1;
	inTopNum = -1;
	int i = 1;
	while (i < argc) {
		if (i % 2 == 1) {
			if (strcmp(argv[i], "-i") == 0) {
				inputName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-o") == 0) {
				outputName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-w") == 0) {
				if (strcmp(argv[i+1], "0") == 0) {
					titleWeight = 1;
				}
				else if (strcmp(argv[i + 1], "1") == 0) {
					titleWeight = 10;
				}
			}
			else if (strcmp(argv[i], "-m") == 0) {
				inPhraseLength = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-n") == 0) {
				inTopNum = atoi(argv[i + 1]);
			}
		}
		i= i+ 2;
	}
}

int ArgParser::helpDoc(){
    box_draw("The WordCount Program Help");
    cout<<"./WordCount.exe filepath"<<endl;
	return 0;
}
