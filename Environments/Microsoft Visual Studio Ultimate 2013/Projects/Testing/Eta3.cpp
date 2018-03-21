#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Eta3/Eta.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Eta3T
	{
		using namespace Nu;
		using namespace Eta3;

		TEST_CLASS(EtaParser)
		{
		public:
			TEST_METHOD(SkipUntilDoubleQuotes)
			{
				String source = "x\"ab\\\"cd\"y";
				
				auto i = source.begin(); ++i; ++i;
				auto j = Parser::SkipUntilDoubleQuotes(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
			TEST_METHOD(SkipUntilSingleQuotes)
			{
				String source = "x'ab\\'cd'y";

				auto i = source.begin(); ++i; ++i;
				auto j = Parser::SkipUntilSingleQuotes(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
			TEST_METHOD(SkipUntilPageBreak)
			{
				String source = "x#ab\ny";

				auto i = source.begin(); ++i; ++i;
				auto j = Parser::SkipUntilPageBreak(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
			TEST_METHOD(SkipWhitespaces)
			{
				String source = "x \t\n\ry";

				auto i = source.begin(); ++i;
				auto j = Parser::SkipWhitespaces(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
		public:
			TEST_METHOD(Clean)
			{
				auto source = "abc #xyz\n\"12\\\"34#56\" 'ik\\'jf#gh' #q'w\"e\nrty";
				auto output = Parser::Clean(source);

				Assert::IsTrue(output == "abc \"12\\\"34#56\" 'ik\\'jf#gh' rty");
			}
		public:
			TEST_METHOD(ParseTypeDeclaration)
			{
				String source = "type 'abc';";
				auto i = source.begin();

				auto r = Parser::ParseTypeDeclaration(source, i);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);
				Assert::IsTrue((*r).first == "'abc'");
				Assert::IsTrue((*r).second != nullptr);
			}
			TEST_METHOD(ParseTypeDeclaration_Missing)
			{
				String source = "instruction 'abc';";
				auto i = source.begin();

				auto r = Parser::ParseTypeDeclaration(source, i);

				Assert::IsTrue(i == source.begin());
				Assert::IsTrue(r == nullptr);
			}
			TEST_METHOD(ParseTypeDefinition_Empty)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({ "'abc'", Make<Parser::Type>() });
				}

				String source = "'abc': {};";
				auto i = source.begin();

				auto r = Parser::ParseTypeDefinition(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r == lookup["'abc'"]);
			}
			TEST_METHOD(ParseTypeDefinition_Internal)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'abc'", Make<Parser::Type>()});
				}

				String source = "'abc': internal;";
				auto i = source.begin();

				auto r = Parser::ParseTypeDefinition(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r == lookup["'abc'"]);
			}
			TEST_METHOD(ParseTypeDefinition_Missing)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'abc'", Make<Parser::Type>()});
				}

				String source = "'xyz': {};";
				auto i = source.begin();

				auto r = Parser::ParseTypeDefinition(source, i, lookup);

				Assert::IsTrue(i == source.begin());
				Assert::IsTrue(r == nullptr);
			}
		public:
			TEST_METHOD(ParseInstanceDeclaration)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'abc'", Make<Parser::Type>()});
				}

				String source = "instance '$0' 'abc';";
				auto i = source.begin();

				auto r = Parser::ParseInstanceDeclaration(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);
				Assert::IsTrue((*r).first == "'$0'");

				auto &instance = (*r).second;

				Assert::IsTrue(instance != nullptr);
				Assert::IsTrue(instance->GetType2() == lookup["'abc'"]);
			}
			TEST_METHOD(ParseInstanceDeclaration_Missing)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'abc'", Make<Parser::Type>()});
				}

				String source = "type 'abc';";
				auto i = source.begin();

				auto r = Parser::ParseInstanceDeclaration(source, i, lookup);

				Assert::IsTrue(i == source.begin());
				Assert::IsTrue(r == nullptr);
			}
		public:
			TEST_METHOD(ParseInstructionDeclaration)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'abc'", Make<Parser::Type>()});
				}

				String source = "instruction '%0' 'abc';";
				auto i = source.begin();

				auto r = Parser::ParseInstructionDeclaration(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);
				Assert::IsTrue((*r).first == "'%0'");

				auto &instruction = (*r).second;

				Assert::IsTrue(instruction != nullptr);

				auto &result = UpCast<Executable::Result::Instance>(instruction->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == lookup["'abc'"]);
			}
			TEST_METHOD(ParseInstructionDeclaration_NoneResult)
			{
				Parser::Lookup lookup;

				String source = "instruction '%0' none;";
				auto i = source.begin();

				auto r = Parser::ParseInstructionDeclaration(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);
				Assert::IsTrue((*r).first == "'%0'");

				auto &instruction = (*r).second;

				Assert::IsTrue(instruction != nullptr);

				auto &result = UpCast<Executable::Result::None>(instruction->GetResult());

				Assert::IsTrue(result != nullptr);
			}
			TEST_METHOD(ParseInstructionDefinition)
			{
				Parser::Lookup lookup;
				{
					auto typeA = Make<Parser::Type>();

					lookup.insert({"'a'", typeA});
					lookup.insert({"'x'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'y'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::None>())});
					lookup.insert({"'g'", Make<Parser::Instruction>(Make<Parser::Executable::Result::Instance>(typeA))});
				}
				
				String source = "'g': { create 'x'; delete 'x'; call 'f'; 'y': call 'g'; return from 'f'; return 'y' from 'g'; };";
				auto i = source.begin();
				
				auto r = Parser::ParseInstructionDefinition(source, i, lookup);
			}
		public:
			TEST_METHOD(ParseAlgorithmArgument_Instance)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'x'", Make<Parser::Instance>(Make<Parser::Type>())});
				}

				String source = "'x'";
				auto i = source.begin();

				auto r = Parser::ParseAlgorithmArgument(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);

				auto &argument = UpCast<Parser::Algorithm::Argument::Instance>(r);

				Assert::IsTrue(argument != nullptr);
				Assert::IsTrue(argument->GetInstance() == lookup["'x'"]);
			}
			TEST_METHOD(ParseAlgorithmArgument_Instruction)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'x'", Make<Parser::Instruction>(Make<Parser::Executable::Result::Instance>(Make<Parser::Type>()))});
				}

				String source = "'x'";
				auto i = source.begin();

				auto r = Parser::ParseAlgorithmArgument(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);

				auto &argument = UpCast<Parser::Algorithm::Argument::Instruction>(r);

				Assert::IsTrue(argument != nullptr);
				Assert::IsTrue(argument->GetInstruction() == lookup["'x'"]);
			}
			TEST_METHOD(ParseAlgorithmDeclaration)
			{
				Parser::Lookup lookup;
				{
					auto typeA = Make<Parser::Type>();

					lookup.insert({"'a'", typeA});
					lookup.insert({"'x'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'y'", Make<Parser::Instance>(typeA)});
				}

				String source = "algorithm 'f' 'a'('x', 'y');";
				auto i = source.begin();

				auto r = Parser::ParseAlgorithmDeclaration(source, i, lookup);

				Assert::IsTrue(i == source.end());
				Assert::IsTrue(r != nullptr);
				Assert::IsTrue((*r).first == "'f'");

				auto &algorithm = (*r).second;

				Assert::IsTrue(algorithm != nullptr);

				auto &result = UpCast<Executable::Result::Instance>(algorithm->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == lookup["'a'"]);

				auto arguments = algorithm->GetArguments();

				Assert::IsTrue(arguments.size() == 2);
			}
		};
	}
}