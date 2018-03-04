#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Eta2/Eta.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Eta2T
	{
		using namespace Nu;
		using namespace Eta2;

		TEST_CLASS(EtaParser)
		{
		/*public:
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
			*/
		public:
			TEST_METHOD(SingleSchemaDeclaration)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"abc\";");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"abc\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();
				
				Assert::IsTrue(algorithms.empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SeveralSchemasDeclaration)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"abc\";\nschema \"xyz\";\n");
				auto &types = assembly->GetTypes();
				
				Assert::IsTrue(types.size() == 2);
				Assert::IsTrue(types["\"abc\""] != nullptr);
				Assert::IsTrue(types["\"xyz\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SingleSchemaDefinition)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"abc\";\n\"abc\": {};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"abc\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SeveralSchemasDefinitions)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"abc\";\nschema \"xyz\";\n\"abc\": {};\n\"xyz\": {};\n");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 2);
				Assert::IsTrue(types["\"abc\""] != nullptr);
				Assert::IsTrue(types["\"xyz\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
		public:
			TEST_METHOD(SingleAlgorithmDeclaration)
			{
				auto parser = Parser();
				auto assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());
				
				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetArguments().empty());
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SingleAlgorithmDeclarationWithSingleArgument)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 1);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SingleAlgorithmDeclarationWithSeveralArguments)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 3);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);
				auto argument2 = UpCast<Algorithm::Argument::Instance>(arguments[1]);
				auto argument3 = UpCast<Algorithm::Argument::Instance>(arguments[2]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument2 != nullptr);
				Assert::IsTrue(argument2->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument3 != nullptr);
				Assert::IsTrue(argument3->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SingleAlgorithmDefinition)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () {\n};");

				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				Assert::IsTrue(algorithm1->GetArguments().empty());
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.empty());
			}
			TEST_METHOD(SingleAlgorithmDefinitionWithSingleArgument)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");\n'f': ($0) {\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 1);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 1);

				auto &instance1 = instances["$0"];
				
				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == argument1->GetInstance());
			}
			TEST_METHOD(SingleAlgorithmDefinitionWithSeveralArguments)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");\n'f': ($0, $1, $2) {\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 3);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);
				auto argument2 = UpCast<Algorithm::Argument::Instance>(arguments[1]);
				auto argument3 = UpCast<Algorithm::Argument::Instance>(arguments[2]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument2 != nullptr);
				Assert::IsTrue(argument2->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument3 != nullptr);
				Assert::IsTrue(argument3->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetCommands().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 3);

				auto &instance1 = instances["$0"];
				auto &instance2 = instances["$1"];
				auto &instance3 = instances["$2"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == argument1->GetInstance());
				Assert::IsTrue(instance2 != nullptr);
				Assert::IsTrue(instance2 == argument2->GetInstance());
				Assert::IsTrue(instance3 != nullptr);
				Assert::IsTrue(instance3 == argument3->GetInstance());
			}
		public:
			TEST_METHOD(SingleCommandCreate)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () { $0: create \"a\";\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetArguments().empty());

				auto &commands = algorithm1->GetCommands();

				Assert::IsTrue(commands.size() == 1);

				auto &command1 = UpCast<Algorithm::Command::CreateInstance>(commands[0]);

				Assert::IsTrue(command1 != nullptr);
				Assert::IsTrue(command1->GetInstance() != nullptr);
				Assert::IsTrue(command1->GetInstance()->GetType() == types["\"a\""]);

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 1);

				auto &instance1 = instances["$0"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == command1->GetInstance());
			}
			TEST_METHOD(SingleCommandReturn)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");\n'f': ($0) { return $0;\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 1);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);

				auto &commands = algorithm1->GetCommands();

				Assert::IsTrue(commands.size() == 1);

				auto &command1 = UpCast<Algorithm::Command::ReturnInstance>(commands[0]);

				Assert::IsTrue(command1 != nullptr);
				Assert::IsTrue(command1->GetInstance() != nullptr);
				Assert::IsTrue(command1->GetInstance() == argument1->GetInstance());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 1);

				auto &instance1 = instances["$0"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == command1->GetInstance());
			}
			TEST_METHOD(SingleCommandCall)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'();\n'f': () { $0: call 'f'();\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);
				Assert::IsTrue(algorithm1->GetArguments().empty());

				auto &commands = algorithm1->GetCommands();

				Assert::IsTrue(commands.size() == 1);

				auto &command1 = UpCast<Algorithm::Command::CallAlgorithm>(commands[0]);

				Assert::IsTrue(command1 != nullptr);

				auto commandResult1 = UpCast<Algorithm::Command::CallAlgorithm::Result::Instance>(command1->GetResult());

				Assert::IsTrue(commandResult1->GetInstance() != nullptr);
				Assert::IsTrue(commandResult1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(command1->GetArguments().empty());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 1);

				auto &instance1 = instances["$0"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == commandResult1->GetInstance());
			}
			TEST_METHOD(SingleCommandCallWithSingleArgument)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\");\n'f': ($0) { $1: call 'f'($0);\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 1);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);

				auto &commands = algorithm1->GetCommands();

				Assert::IsTrue(commands.size() == 1);

				auto &command1 = UpCast<Algorithm::Command::CallAlgorithm>(commands[0]);

				Assert::IsTrue(command1 != nullptr);

				auto commandResult1 = UpCast<Algorithm::Command::CallAlgorithm::Result::Instance>(command1->GetResult());

				Assert::IsTrue(commandResult1->GetInstance() != nullptr);
				Assert::IsTrue(commandResult1->GetInstance()->GetType() == types["\"a\""]);

				auto &commandArguments1 = command1->GetArguments();

				Assert::IsTrue(commandArguments1.size() == 1);

				auto &commandArgument1 = UpCast<Algorithm::Command::CallAlgorithm::Argument::Instance>(commandArguments1[0]);

				Assert::IsTrue(commandArgument1 != nullptr);
				Assert::IsTrue(commandArgument1->GetInstance() == argument1->GetInstance());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 2);

				auto &instance1 = instances["$0"];
				auto &instance2 = instances["$1"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == argument1->GetInstance());
				Assert::IsTrue(instance2 != nullptr);
				Assert::IsTrue(instance2 == commandResult1->GetInstance());
			}
			TEST_METHOD(SingleCommandCallWithSeveralArguments)
			{
				auto parser = Parser();
				auto &assembly = parser.Parse("schema \"a\";\nalgorithm \"a\" 'f'(\"a\", \"a\", \"a\");\n'f': ($0, $1, $2) { $3: call 'f'($0, $1, $2);\n};");
				auto &types = assembly->GetTypes();

				Assert::IsTrue(types.size() == 1);
				Assert::IsTrue(types["\"a\""] != nullptr);

				auto &algorithms = assembly->GetAlgorithms();

				Assert::IsTrue(algorithms.size() == 1);

				auto &algorithm1 = algorithms["'f'"];

				Assert::IsTrue(algorithm1 != nullptr);

				auto &result = UpCast<Algorithm::Result::Instance>(algorithm1->GetResult());

				Assert::IsTrue(result != nullptr);
				Assert::IsTrue(result->GetType() == types["\"a\""]);

				auto &arguments = algorithm1->GetArguments();

				Assert::IsTrue(arguments.size() == 3);

				auto argument1 = UpCast<Algorithm::Argument::Instance>(arguments[0]);
				auto argument2 = UpCast<Algorithm::Argument::Instance>(arguments[1]);
				auto argument3 = UpCast<Algorithm::Argument::Instance>(arguments[2]);

				Assert::IsTrue(argument1 != nullptr);
				Assert::IsTrue(argument1->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument2 != nullptr);
				Assert::IsTrue(argument2->GetInstance()->GetType() == types["\"a\""]);
				Assert::IsTrue(argument3 != nullptr);
				Assert::IsTrue(argument3->GetInstance()->GetType() == types["\"a\""]);

				auto &commands = algorithm1->GetCommands();

				Assert::IsTrue(commands.size() == 1);

				auto &command1 = UpCast<Algorithm::Command::CallAlgorithm>(commands[0]);

				Assert::IsTrue(command1 != nullptr);

				auto commandResult1 = UpCast<Algorithm::Command::CallAlgorithm::Result::Instance>(command1->GetResult());

				Assert::IsTrue(commandResult1->GetInstance() != nullptr);
				Assert::IsTrue(commandResult1->GetInstance()->GetType() == types["\"a\""]);

				auto &commandArguments1 = command1->GetArguments();

				Assert::IsTrue(commandArguments1.size() == 3);

				auto &commandArgument1 = UpCast<Algorithm::Command::CallAlgorithm::Argument::Instance>(commandArguments1[0]);
				auto &commandArgument2 = UpCast<Algorithm::Command::CallAlgorithm::Argument::Instance>(commandArguments1[1]);
				auto &commandArgument3 = UpCast<Algorithm::Command::CallAlgorithm::Argument::Instance>(commandArguments1[2]);

				Assert::IsTrue(commandArgument1 != nullptr);
				Assert::IsTrue(commandArgument1->GetInstance() == argument1->GetInstance());
				Assert::IsTrue(commandArgument2 != nullptr);
				Assert::IsTrue(commandArgument2->GetInstance() == argument2->GetInstance());
				Assert::IsTrue(commandArgument3 != nullptr);
				Assert::IsTrue(commandArgument3->GetInstance() == argument3->GetInstance());

				auto &instances = assembly->GetInstances();

				Assert::IsTrue(instances.size() == 4);

				auto &instance1 = instances["$0"];
				auto &instance2 = instances["$1"];
				auto &instance3 = instances["$2"];
				auto &instance4 = instances["$3"];

				Assert::IsTrue(instance1 != nullptr);
				Assert::IsTrue(instance1 == argument1->GetInstance());
				Assert::IsTrue(instance2 != nullptr);
				Assert::IsTrue(instance2 == argument2->GetInstance());
				Assert::IsTrue(instance3 != nullptr);
				Assert::IsTrue(instance3 == argument3->GetInstance());
				Assert::IsTrue(instance4 != nullptr);
				Assert::IsTrue(instance4 == commandResult1->GetInstance());
			}
		};
	}
}