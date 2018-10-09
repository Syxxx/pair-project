#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../WordCount/LexemeProcesser.h"
#include "../../WordCount/Status.h"
#include "../../WordCount/LexemeProcesser.cpp"
#include "../../WordCount/Status.cpp"
#include "../../WordCount/LexemeParser.h"
#include "../../WordCount/LexemeParser.cpp"
#include "../../WordCount/WordProcesser.h"
#include "../../WordCount/WordProcesser.cpp"
#include "../../WordCount/PhraseProcesser.h"
#include "../../WordCount/PhraseProcesser.cpp"
#include "../../WordCount/FileContentFilter.h"
#include "../../WordCount/FileContentFilter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace UnitTest_FileContentFilter
{        
    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(TestMethod_dfaOfFirstTitle)
        {
            Status* status = new Status();
            WordProcesser* lexProcesser = new WordProcesser(status);
            LexemeParser* lexer = new LexemeParser(status, lexProcesser);
            FileContentFilter* fileContFilter = new FileContentFilter(status, lexer);

            fileContFilter->dfaOfFirstTitle('0');
            fileContFilter->dfaOfFirstTitle('1');
            fileContFilter->dfaOfFirstTitle('\n');
            fileContFilter->dfaOfFirstTitle('T');
            fileContFilter->dfaOfFirstTitle('i');
            fileContFilter->dfaOfFirstTitle('t');
            fileContFilter->dfaOfFirstTitle('l');
            fileContFilter->dfaOfFirstTitle('e');
            fileContFilter->dfaOfFirstTitle(':');
            fileContFilter->dfaOfFirstTitle(' ');

            Assert::AreEqual<int>(10, fileContFilter->statusOfDFA[0]);

        }

        TEST_METHOD(TestMethod_dfaOfTitle)
        {
            Status* status = new Status();
            WordProcesser* lexProcesser = new WordProcesser(status);
            LexemeParser* lexer = new LexemeParser(status, lexProcesser);
            FileContentFilter* fileContFilter = new FileContentFilter(status, lexer);

            fileContFilter->statusOfDFA[1] = 1;

            fileContFilter->dfaOfTitle('0');
            fileContFilter->dfaOfTitle('1');
            fileContFilter->dfaOfTitle('\n');
            fileContFilter->dfaOfTitle('\n');
            fileContFilter->dfaOfTitle('\n');
            fileContFilter->dfaOfTitle('1');
            fileContFilter->dfaOfTitle('2');
            fileContFilter->dfaOfTitle('\n');
            fileContFilter->dfaOfTitle('T');
            fileContFilter->dfaOfTitle('i');
            fileContFilter->dfaOfTitle('t');
            fileContFilter->dfaOfTitle('l');
            fileContFilter->dfaOfTitle('e');
            fileContFilter->dfaOfTitle(':');
            fileContFilter->dfaOfTitle(' ');

            Assert::AreEqual<int>(13, fileContFilter->statusOfDFA[1]);

        }

        TEST_METHOD(TestMethod_dfaOfAbstract)
        {
            Status* status = new Status();
            WordProcesser* lexProcesser = new WordProcesser(status);
            LexemeParser* lexer = new LexemeParser(status, lexProcesser);
            FileContentFilter* fileContFilter = new FileContentFilter(status, lexer);

            fileContFilter->statusOfDFA[2] = 1;

            fileContFilter->dfaOfAbstract('0');
            fileContFilter->dfaOfAbstract('1');
            fileContFilter->dfaOfAbstract('\n');
            fileContFilter->dfaOfAbstract('\n');
            fileContFilter->dfaOfAbstract('A');
            fileContFilter->dfaOfAbstract('b');
            fileContFilter->dfaOfAbstract('s');
            fileContFilter->dfaOfAbstract('t');
            fileContFilter->dfaOfAbstract('r');
            fileContFilter->dfaOfAbstract('a');
            fileContFilter->dfaOfAbstract('c');
            fileContFilter->dfaOfAbstract('t');
            fileContFilter->dfaOfAbstract(':');
            fileContFilter->dfaOfAbstract(' ');
            Assert::AreEqual<int>(12, fileContFilter->statusOfDFA[2]);

        }

        
        TEST_METHOD(TestMethod_scan)
        {
            Status* status = new Status();
            status->setIOFile("../test/UnitTest_FileContentFilter/input.txt");
            status->setWeight(100, 1);
            status->setPharse(3);

            PhraseProcesser* lexProcesser = new PhraseProcesser(status);
            LexemeParser* lexer = new LexemeParser(status, lexProcesser);
            FileContentFilter* fileContFilter = new FileContentFilter(status, lexer);



            fileContFilter->scan();
            lexer->sendToStatus();
            lexProcesser->sendToStatus();

            Assert::AreEqual<int>(1755, status->charNum);
            Assert::AreEqual<int>(173, status->wordTotalNum);
            Assert::AreEqual<int>(4, status->lineNum);
        }


    };
}