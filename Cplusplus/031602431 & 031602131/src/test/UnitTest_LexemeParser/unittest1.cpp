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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest_LexemeParser
{		
	TEST_CLASS(UnitTest1)
	{
	public:


		TEST_METHOD(TestMethod1)
		{
			Status* status = new Status();
			WordProcesser* lexProcesser = new WordProcesser(status);
			LexemeParser* lexer = new LexemeParser(status, lexProcesser);

			lexer->processStr("We present a new AI task -- Embodied Question Answering (E"
				"mbodiedQA) -- where an agent is spawned at a random location in a 3D envi"
				"ronment and asked a question", Status::TITLE_CONTENT);
			lexer->sendToStatus();
			lexProcesser->sendToStatus();

			Assert::AreEqual<int>(159, status->charNum);
			Assert::AreEqual<int>(1, status->lineNum);

		}

		TEST_METHOD(TestMethod2)
		{
			Status* status = new Status();
			status->setPharse(3);

			PhraseProcesser* lexProcesser = new PhraseProcesser(status);
			LexemeParser* lexer = new LexemeParser(status, lexProcesser);

			lexer->processStr("adbda \n afasdf asdfasdf aqsf", Status::TITLE_CONTENT);
			lexer->sendToStatus();
			lexProcesser->sendToStatus();

			Assert::AreEqual<int>(28, status->charNum);
			Assert::AreEqual<int>(2, status->lineNum);
			Assert::AreEqual<int>(1, ((status->storeMap).strMap->size()));
		}


	};
}