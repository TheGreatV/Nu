#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Parser2/Parser.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Parser2
	{
		using namespace Nu;
		using namespace Parsing2;

		TEST_CLASS(Smoke)
		{
		public:
			TEST_METHOD(TestMethod1)
			{
				auto lexer = Make<Lexing2::Lexer>();

				// auto lexerOutput = lexer->Parse("a: space {};");
				auto lexerOutput = lexer->Parse("space {};");

				auto parser = Make<Parser>();

				auto parserOutput = parser->Parse(lexerOutput);

				/*auto names = parserOutput->GetNames();

				Assert::IsTrue(
					names.size() == 1,
					L"Exactly 1 name"
				);

				auto name1 = *names.begin();
				
				Assert::IsTrue(
					name1->GetValue() == "a",
					L"Name is \"a\""
				);*/
			}
		};
	}
}