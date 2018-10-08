#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../WordCount/LexemeProcesser.h"
#include "../../WordCount/PhraseProcesser.h"
#include "../../WordCount/WordProcesser.h"
#include "../../WordCount/Status.h"
#include "../../WordCount/LexemeProcesser.cpp"
#include "../../WordCount/PhraseProcesser.cpp"
#include "../../WordCount/WordProcesser.cpp"
#include "../../WordCount/Status.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTest_LexemeProcesser
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod_WordProcesser)
		{
			Status* status = new Status();
			status->setWeight(1, 1);

			WordProcesser wordProcesser(status);

			wordProcesser.processLexeme("ABCD", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(1, status->wordTotalNum);


			wordProcesser.processLexeme("ABCD123", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(2, status->wordTotalNum);



			wordProcesser.processLexeme("123ABCD", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(2, status->wordTotalNum);


			wordProcesser.processLexeme("AB123CD", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(2, status->wordTotalNum);

			wordProcesser.processLexeme("123", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(2, status->wordTotalNum);


			wordProcesser.processLexeme("abcd", "", Status::TITLE_CONTENT);
			wordProcesser.sendToStatus();
			Assert::AreEqual<int>(3, status->wordTotalNum);
		}

		TEST_METHOD(TestMethod_PhraseProcesser)
		{
			Status* status = new Status();
			status->setPharse(3);
			status->setWeight(1, 1);

			PhraseProcesser phraseProcesser(status);

			phraseProcesser.processLexeme("We", "", Status::TITLE_CONTENT);
			phraseProcesser.processLexeme("present", " ", Status::TITLE_CONTENT);
			phraseProcesser.processLexeme("a", " ", Status::TITLE_CONTENT);
			phraseProcesser.processLexeme("new", " ", Status::TITLE_CONTENT);
			phraseProcesser.processLexeme("AI", " ", Status::TITLE_CONTENT);
			phraseProcesser.processLexeme("task", " ", Status::TITLE_CONTENT);

			phraseProcesser.sendToStatus();

			int count = ((status->storeMap).strMap)->size();
			Assert::AreEqual<int>(0, count);

		}

		TEST_METHOD(TestMethod_PhraseProcesser2)
		{
			Status* status = new Status();
			status->setPharse(3);
			status->setWeight(1, 1);

			PhraseProcesser phraseProcesser(status);

			phraseProcesser.processLexeme("Weee", "", Status::ABSTRACT_CONTENT);
			phraseProcesser.processLexeme("present", "_*_*_", Status::ABSTRACT_CONTENT);
			phraseProcesser.processLexeme("aaaa", " ", Status::ABSTRACT_CONTENT);
			phraseProcesser.processLexeme("neww", "_*_*_", Status::ABSTRACT_CONTENT);
			phraseProcesser.processLexeme("AI", " ", Status::ABSTRACT_CONTENT);
			phraseProcesser.processLexeme("task", " ", Status::ABSTRACT_CONTENT);

			phraseProcesser.sendToStatus();

			
			int count = ((status->storeMap).strMap)->size();
			Assert::AreEqual<int>(2, count);

			auto iter = ((status->storeMap).strMap)->begin();
			Assert::AreEqual<string>( "Weee_*_*_present aaaa", (*iter).first);
			Assert::AreEqual<int>(1, (*iter).second);
			iter++;
			Assert::AreEqual<string>("present aaaa_*_*_neww", (*iter).first);
			Assert::AreEqual<int>(1, (*iter).second);


		}
	};
}