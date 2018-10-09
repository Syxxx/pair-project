#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../WordCount/tools.h"
#include "../../WordCount/tools.cpp"
#include "../../WordCount/ArgParser.h"
#include "../../WordCount/ArgParser.cpp"
#include "../../WordCount/FileContentFilter.h"
#include "../../WordCount/FileContentFilter.cpp"
#include "../../WordCount/LexemeParser.h"
#include "../../WordCount/LexemeParser.cpp"
#include "../../WordCount/LexemeProcesser.h"
#include "../../WordCount/LexemeProcesser.cpp"
#include "../../WordCount/WordProcesser.h"
#include "../../WordCount/WordProcesser.cpp"
#include "../../WordCount/PhraseProcesser.h"
#include "../../WordCount/PhraseProcesser.cpp"
#include "../../WordCount/WordCount.cpp"
#include "../../WordCount/Status.h"
#include "../../WordCount/Status.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTest_Main
{        
    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            Status* status = new Status();


            status->setIOFile("../test/UnitTest_Main/input1.txt");
            status->setPharse(3);
            status->setTopNum(5);
            status->setWeight(1, 1);

            LexemeProcesser* lexemeProcesser;
            if (status->phraseLength > 1) {
                lexemeProcesser = new PhraseProcesser(status);
            }
            else {
                lexemeProcesser = new WordProcesser(status);
            }

            LexemeParser* lexemeParser = new LexemeParser(status, lexemeProcesser);
            FileContentFilter* fileContentFilter = new FileContentFilter(status, lexemeParser);

            fileContentFilter->scan();
            lexemeParser->sendToStatus();
            lexemeProcesser->sendToStatus();

            Assert::AreEqual<int>(1197698, status->charNum);
            Assert::AreEqual<int>(120374, status->wordTotalNum);
            Assert::AreEqual<int>(1958, status->lineNum);


            map<string, int>::iterator iter;
            priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> que;
            iter = ((status->storeMap).strMap)->begin();

            while (iter != ((status->storeMap).strMap)->end())
            {
                que.push(make_pair(iter->second, iter->first));
                iter++;
            }

            string str[5] = { "convolutional neural network","convolutional neural networks"
                                ,"deep neural networks","results show that", "experiments show that" };
            int strInt[5] = { 96,88,65,56,45 };


            for (unsigned int i = 0; (i < (unsigned int)(((status->storeMap).strMap)->size())) 
                                        && (i < (unsigned int)(status->topNum)); i++) {
                pair<int, string> strPair = que.top();
                que.pop();
                //Assert::AreEqual(str[i], strPair.second);
                //Assert::AreEqual(strInt[i], strPair.first);
            }

        }


    };
}