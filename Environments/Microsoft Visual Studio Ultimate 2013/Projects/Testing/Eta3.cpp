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
			TEST_METHOD(ParseAlgorithmDefinition)
			{
				Parser::Lookup lookup;
				{
					auto typeA = Make<Parser::Type>();

					Parser::Algorithm::Arguments arguments1;
					{
						arguments1.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(typeA)));
					}

					lookup.insert({"'a'", typeA});
					lookup.insert({"'x'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'y'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::None>())});
					lookup.insert({"'g'", Make<Parser::Instruction>(Make<Parser::Executable::Result::Instance>(typeA))});
					lookup.insert({"'h'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::None>(), Parser::Algorithm::Arguments())});
					lookup.insert({"'k'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::None>(), arguments1)});
				}
				
				String source = "'h': { create 'x'; delete 'x'; call 'f'; 'y': call 'g'; return from 'f'; return 'y' from 'g'; call 'h'(); call 'k'('x'); };";
				auto i = source.begin();
				
				auto r = Parser::ParseAlgorithmDefinition(source, i, lookup);
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
		public:
			TEST_METHOD(ParseCreateInstanceCommand)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'x'", Make<Parser::Instance>(Make<Parser::Type>())});
				}
				
				String source = "create 'x';";
				auto i = source.begin();
				
				auto r = Parser::ParseCreateInstanceCommand(source, i, lookup);

				Assert::IsTrue(r->GetInstance() == lookup["'x'"]);
			}
			TEST_METHOD(ParseDeleteInstanceCommand)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'x'", Make<Parser::Instance>(Make<Parser::Type>())});
				}

				String source = "delete 'x';";
				auto i = source.begin();

				auto r = Parser::ParseDeleteInstanceCommand(source, i, lookup);

				Assert::IsTrue(r->GetInstance() == lookup["'x'"]);
			}
			TEST_METHOD(ParseReturnNoneCommand)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::None>())});
				}

				String source = "return from 'f';";
				auto i = source.begin();

				auto r = Parser::ParseReturnNoneCommand(source, i, lookup);

				Assert::IsTrue(r->GetExecutable() == UpCast<Parser::Executable>(lookup["'f'"]));
			}
			TEST_METHOD(ParseReturnInstanceCommand)
			{
				Parser::Lookup lookup;
				{
					auto typeA = Make<Parser::Type>();
					lookup.insert({"'x'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::Instance>(typeA))});
				}

				String source = "return 'x' from 'f';";
				auto i = source.begin();

				auto r = Parser::ParseReturnInstanceCommand(source, i, lookup);
				
				Assert::IsTrue(r->GetExecutable() == UpCast<Parser::Executable>(lookup["'f'"]));
				Assert::IsTrue(r->GetInstance() == lookup["'x'"]);
			}
			TEST_METHOD(ParseNoneInstructionCallCommand)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::None>())});
				}

				String source = "call 'f';";
				auto i = source.begin();

				auto r = Parser::ParseNoneInstructionCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseInstructionCallCommand)
			{
				Parser::Lookup lookup;
				{
					auto typeA = Make<Parser::Type>();
					lookup.insert({"'x'", Make<Parser::Instance>(typeA)});
					lookup.insert({"'f'", Make<Parser::Instruction>(Make<Parser::Executable::Result::Instance>(typeA))});
				}

				String source = "'x': call 'f';";
				auto i = source.begin();

				auto r = Parser::ParseInstructionCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseNoneAlgorithmCallCommand_EmptyArguments)
			{
				Parser::Lookup lookup;
				{
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::None>(), Parser::Algorithm::Arguments())});
				}

				String source = "call 'f'();";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseNoneAlgorithmCallCommand_OneArgument)
			{
				Parser::Lookup lookup;
				{
					auto type = Make<Parser::Type>();

					Parser::Algorithm::Arguments arguments;
					{
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
					}

					lookup.insert({"'x'", Make<Parser::Instance>(type)});
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::None>(), arguments)});
				}

				String source = "call 'f'('x');";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseNoneAlgorithmCallCommand_SeveralArguments)
			{
				Parser::Lookup lookup;
				{
					auto type = Make<Parser::Type>();

					Parser::Algorithm::Arguments arguments;
					{
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
					}

					lookup.insert({"'x'", Make<Parser::Instance>(type)});
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::None>(), arguments)});
				}

				String source = "call 'f'('x','x','x');";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseAlgorithmCallCommand_EmptyArguments)
			{
				Parser::Lookup lookup;
				{
					auto type = Make<Parser::Type>();
					
					lookup.insert({"'x'", Make<Parser::Instance>(type)});
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::Instance>(type), Parser::Algorithm::Arguments())});
				}

				String source = "'x': call 'f'();";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseAlgorithmCallCommand_OneArgument)
			{
				Parser::Lookup lookup;
				{
					auto type = Make<Parser::Type>();

					Parser::Algorithm::Arguments arguments;
					{
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
					}

					lookup.insert({"'x'", Make<Parser::Instance>(type)});
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::Instance>(type), arguments)});
				}

				String source = "'x': call 'f'('x');";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
			TEST_METHOD(ParseAlgorithmCallCommand_SeveralArguments)
			{
				Parser::Lookup lookup;
				{
					auto type = Make<Parser::Type>();

					Parser::Algorithm::Arguments arguments;
					{
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
						arguments.push_back(Make<Parser::Algorithm::Argument::Instance>(Make<Parser::Instance>(type)));
					}

					lookup.insert({"'x'", Make<Parser::Instance>(type)});
					lookup.insert({"'f'", Make<Parser::Algorithm>(Make<Parser::Executable::Result::Instance>(type), arguments)});
				}

				String source = "'x': call 'f'('x','x','x');";
				auto i = source.begin();

				auto r = Parser::ParseNoneAlgorithmCallCommand(source, i, lookup);
			}
		public:
			TEST_METHOD(Sample_1)
			{
				Parser parser;

				auto source = String() +
					"# types declarations														" + "\n" +
					"type 'int';																" + "\n" +
					"																			" + "\n" +
					"# types definitions														" + "\n" +
					"'int': internal;															" + "\n" +
					"																			" + "\n" +
					"# instances declaration													" + "\n" +
					"instance '$0'   'int';														" + "\n" +
					"instance '$1'   'int';														" + "\n" +
					"instance '$2'   'int';														" + "\n" +
					"instance '$3'   'int';														" + "\n" +
					"instance '$4'   'int';														" + "\n" +
					"instance '$5'   'int';														" + "\n" +
					"instance '$6'   'int';														" + "\n" +
					"instance '$7'   'int';														" + "\n" +
					"instance '$8'   'int';														" + "\n" +
					"instance '$9'   'int';														" + "\n" +
					"instance '$10'  'int';														" + "\n" +
					"instance '$11'  'int';														" + "\n" +
					"instance '$12'  'int';														" + "\n" +
					"instance '$13'  'int';														" + "\n" +
					"																			" + "\n" +
					"# instructions declaration													" + "\n" +
					"instruction '%0' none;														" + "\n" +
					"instruction '%1' none;														" + "\n" +
					"																			" + "\n" +
					"# algorithms declaration													" + "\n" +
					"algorithm 'int==int'            'int'   ('$0', '$1');						" + "\n" +
					"algorithm 'int=int'             none    ('$2', '$3');						" + "\n" +
					"algorithm 'int+int'             'int'   ('$12', '$13');					" + "\n" +
					"algorithm 'if'                  none    ('$4', '%0');						" + "\n" +
					"algorithm 'sum(int,int,int)'    'int'   ('$7', '$8', '$9');				" + "\n" +
					"algorithm 'main'                none    ();								" + "\n" +
					"																			" + "\n" +
					"# instructions definitions													" + "\n" +
					"'%0': internal;															" + "\n" +
					"'%1': {																	" + "\n" +
					"    call 'int=int'('$5', '$6');											" + "\n" +
					"};																			" + "\n" +
					"																			" + "\n" +
					"# algorithms definitions													" + "\n" +
					"'int==int'          : internal;											" + "\n" +
					"'int=int'           : internal;											" + "\n" +
					"'if'                : internal;											" + "\n" +
					"'main'              : {													" + "\n" +
					"    create '$5';															" + "\n" +
					"    create '$6';															" + "\n" +
					"    '$7': call 'int==int'('$5', '$6');										" + "\n" +
					"    call 'if'('$7', '%0');													" + "\n" +
					"    delete '$7';															" + "\n" +
					"    delete '$6';															" + "\n" +
					"    delete '$5';															" + "\n" +
					"};																			" + "\n" +
					"'sum(int,int,int)'  : {													" + "\n" +
					"    '$10': call 'int+int'('$7', '$8');										" + "\n" +
					"    '$11': call 'int+int'('$9', '$10');									" + "\n" +
					"    return '$11' from 'sum(int,int,int)';									" + "\n" +
					"};																			" + "\n";
				auto output = parser.Parse(source);
			}
		};
	}
}