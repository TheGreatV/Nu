#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Cleaner/Cleaner.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Cleaner
	{
		using namespace Nu;

		TEST_CLASS(LineComment)
		{
		public:
			TEST_METHOD(NoComments)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::AreEqual<String>(
					"abc",
					cleaner->Parse("abc")
				);
			}

			TEST_METHOD(Negative)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::ExpectException<Nu::Exception>([&](){
					cleaner->Parse("`\\abc");
				});
				Assert::ExpectException<Nu::Exception>([&](){
					cleaner->Parse("`\\a`\\b\\`c");
				});
			}

			TEST_METHOD(SingleLineComment)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::AreEqual<String>(
					"abc",
					cleaner->Parse("abc`/ololo")
				);
			}

			TEST_METHOD(SingleBlockComment)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::AreEqual<String>(
					"",
					cleaner->Parse("`\\abc\\`"),
					L"1"
				);
				Assert::AreEqual<String>(
					"ab",
					cleaner->Parse("ab`\\cd\\`"),
					L"2"
				);
				Assert::AreEqual<String>(
					"cd",
					cleaner->Parse("`\\ab\\`cd"),
					L"3"
				);
				Assert::AreEqual<String>(
					"ac",
					cleaner->Parse("a`\\b\\`c"),
					L"4"
				);
				Assert::AreEqual<String>(
					"a c",
					cleaner->Parse("a `\\b\\`c"),
					L"5"
				);
				Assert::AreEqual<String>(
					"a c",
					cleaner->Parse("a`\\b\\` c"),
					L"6"
				);
			}

			TEST_METHOD(NestedBlockComment)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::AreEqual<String>(
					"",
					cleaner->Parse("`\\a`\\b\\`c\\`"),
					L"1"
				);
			}

			TEST_METHOD(SeveralBlockComment)
			{
				auto cleaner = Make<Cleaning::Cleaner>();

				Assert::AreEqual<String>(
					"b",
					cleaner->Parse("`\\a\\`b`\\c\\`"),
					L"1"
				);

				Assert::AreEqual<String>(
					"d",
					cleaner->Parse("`\\a`\\b\\`c\\`d`\\e\\`"),
					L"2"
				);
			}
		};
	}
}