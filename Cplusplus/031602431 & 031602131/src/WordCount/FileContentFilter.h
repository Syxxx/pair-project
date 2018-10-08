#define _CRT_SECURE_NO_WARNINGS 

#ifndef FILECONTENTFILTER_H
#define FILECONTENTFILTER_H


#include <string>
#include "LexemeParser.h"
#include "Status.h"

using namespace std;



// This class will open the file and convert every character to LexemeParser
class FileContentFilter{
public:
	FileContentFilter() :status(NULL), file(NULL), processer(NULL),
						 contStart(0), contEnd(0), fileContent(string()){}
    FileContentFilter(Status* status, LexemeParser* lexemePareser);
	~FileContentFilter() {
		if (file != nullptr) {
			fclose(file);
		}
	}
	int scan();


public:

	int statusOfDFA[3];
	int dfaOfFirstTitle(char c);
	int dfaOfTitle(char c);
	int dfaOfAbstract(char c);

private:
	int inWhichContext;

	Status* status;
	FILE* file;
	LexemeParser* processer;
	int contStart;
	int contEnd;
	string fileContent;
	int contentP;
};

#endif