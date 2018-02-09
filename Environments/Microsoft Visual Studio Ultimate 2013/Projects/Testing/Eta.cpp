#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Eta/Eta.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace EtaT
	{
		using namespace Nu;
		using namespace Eta;

		TEST_CLASS(EtaParser)
		{
		public:
			TEST_METHOD(SkipDoubleQuotes)
			{
				String source = "x\"ab\\\"cd\"y";
				
				auto i = source.begin(); ++i;
				auto j = Parser::SkipDoubleQuotes(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
			TEST_METHOD(SkipSingleQuotes)
			{
				String source = "x'ab\\'cd'y";

				auto i = source.begin(); ++i;
				auto j = Parser::SkipSingleQuotes(source, i);

				auto e = source.begin(); ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e; ++e;

				Assert::IsTrue(j == e);
			}
			TEST_METHOD(SkipComment)
			{
				String source = "x#ab\ny";

				auto i = source.begin(); ++i;
				auto j = Parser::SkipComment(source, i);

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
			TEST_METHOD(SingleSchemaDeclaration)
			{
				auto parser = Parser();

				parser.Parse("schema \"abc\";");
			}
			TEST_METHOD(SeveralSchemasDeclaration)
			{
				auto parser = Parser();

				parser.Parse("schema \"abc\";\nschema \"xyz\";\n");
			}
			TEST_METHOD(SingleSchemaDefinition)
			{
				auto parser = Parser();

				parser.Parse("schema \"abc\";\n\"abc\": {};");
			}
			TEST_METHOD(SeveralSchemasDefinitions)
			{
				auto parser = Parser();

				parser.Parse("schema \"abc\";\nschema \"xyz\";\n\"abc\": {};\n\"xyz\": {};\n");
			}
		public:
			TEST_METHOD(SingleAlgorithmDeclaration)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();");
			}
			TEST_METHOD(SingleAlgorithmDeclarationWithSingleArgument)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");");
			}
			TEST_METHOD(SingleAlgorithmDeclarationWithSeveralArguments)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");");
			}
			TEST_METHOD(SingleAlgorithmDefinition)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () {\n};");
			}
			TEST_METHOD(SingleAlgorithmDefinitionWithSingleArgument)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");\n'f': ($0) {\n};");
			}
			TEST_METHOD(SingleAlgorithmDefinitionWithSeveralArguments)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");\n'f': ($0, $1, $2) {\n};");
			}
		public:
			TEST_METHOD(SingleCommandCreate)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () { $0: create \"a\";\n};");
			}
			TEST_METHOD(SingleCommandCall)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () { $0: call 'f'();\n};");
			}
			TEST_METHOD(SingleCommandCallWithSingleArgument)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");\n'f': ($0) { $1: call 'f'($0);\n};");
			}
			TEST_METHOD(SingleCommandCallWithSeveralArguments)
			{
				auto parser = Parser();

				parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");\n'f': ($0, $1, $2) { $3: call 'f'($0, $1, $2);\n};");
			}
		};
	}
}