#pragma once

#pragma region Include

#include <../Header/Header.hpp>
#include <../Eta2/Eta.hpp>

#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <clocale>
#include <Windows.h>

#pragma endregion


Nu::String ScreenCharacters(const Nu::String& source_)
{
	return Nu::Replace(source_, "\"", "\\\"");
}


void wmain(int argc, wchar_t* argv[])
{
	// std::system("pause");

	// try
	// {
		_setmode(_fileno(stdout), _O_WTEXT);

		Nu::Size totalFilesCount = argc > 1
			? static_cast<Nu::Size>(argc)-1
			: 0;

		// std::wcout << L"total files count: " << totalFilesCount << std::endl;

		Nu::Vector<Nu::WString> filenames(totalFilesCount);
		{
			for (Nu::Size i = 0; i < totalFilesCount; ++i)
			{
				auto &filename = filenames[i];
				auto &rawFilename = argv[i + 1];

				filename = static_cast<Nu::WString>(rawFilename);
			}
		}

		Nu::Map<Nu::WString, Nu::String> inputs;
		{
			for (auto &filename : filenames)
			{
				auto &input = inputs[filename];

				// std::wcout << L"loading file \"" << filename << L"\"..." << std::endl;

				std::ifstream file(filename);

				std::getline(file, input, '\0');

				// std::cout << "content: " << std::endl << input << std::endl;

				file.close();
			}
		}

		auto parser = Nu::MakeReference<Nu::Eta2::Parser>();

		for (auto &it : inputs)
		{
			auto &filename = it.first;
			auto &source = it.second;
			auto &assembly = parser->Parse(source);
			auto output = Nu::String();

			auto sourceByLines = Nu::Split(source, "\n");

			output += "auto source = String() +\n";

			for (auto &i : sourceByLines)
			{
				output += "\t\"" + ScreenCharacters(i) + "\" + \"\\n\" +\n";
			}

			output += "\t\"\";\n";
		
			output += "auto parser = Parser();\n";
			output += "auto &assembly = parser.Parse(source);\n";
			output += "\n";
			output += "Assert::IsTrue(assembly != nullptr);\n";
			output += "\n";

			auto &types = assembly->GetTypes();

			output += "auto &types = assembly->GetTypes();\n";
			output += "\n";
			output += "Assert::IsTrue(types.size() == " + std::to_string(types.size()) + ");\n";
			output += "\n";

			Nu::Map<Nu::Reference<Nu::Eta2::Type>, Nu::String> typeIDs;
		
			for (auto &it : types)
			{
				auto &typeName = it.first;
				auto &type = it.second;
				auto typeID = "type" + std::to_string(typeIDs.size() + 1);

				typeIDs[type] = typeID;

				output += "auto &" + typeID + " = types[\"" + ScreenCharacters(typeName) + "\"];\n";
				output += "\n";
				output += "Assert::IsTrue(" + typeID + " != nullptr);\n";
				output += "\n";
			}

			auto &algorithms = assembly->GetAlgorithms();

			output += "auto &algorithms = assembly->GetAlgorithms();\n";
			output += "\n";
			output += "Assert::IsTrue(algorithms.size() == " + std::to_string(algorithms.size()) + ");\n";
			output += "\n";
		
			Nu::Map<Nu::Reference<Nu::Eta2::Algorithm>, Nu::String> algorithmIDs;
			Nu::Map<Nu::Reference<Nu::Eta2::Algorithm::Result>, Nu::String> algorithmResultIDs;
			Nu::Map<Nu::Reference<Nu::Eta2::Algorithm::Argument>, Nu::String> algorithmArgumentIDs;

			for (auto &it : algorithms)
			{
				auto &algorithmName = it.first;
				auto &algorithm = it.second;
				auto algorithmID = "algorithm" + std::to_string(algorithmIDs.size() + 1);

				algorithmIDs[algorithm] = algorithmID;
			
				output += "auto &" + algorithmID + " = algorithms[\"" + ScreenCharacters(algorithmName) + "\"];\n";
				output += "\n";
				output += "Assert::IsTrue(" + algorithmID + " != nullptr);\n";
				output += "\n";

				auto &result = algorithm->GetResult();
				auto resultID = algorithmID + "_result";

				algorithmResultIDs[result] = resultID;

				if (auto instanceResult = Nu::UpCast<Nu::Eta2::Algorithm::Result::Instance>(result))
				{
					if (typeIDs.find(instanceResult->GetType()) == typeIDs.end())
					{
						throw Nu::Exception();
					}

					output += "auto &" + resultID + " = UpCast<Algorithm::Result::Instance>(" + algorithmID + "->GetResult());\n";
					output += "\n";
					output += "Assert::IsTrue(" + resultID + " != nullptr);\n";
					output += "Assert::IsTrue(" + resultID + "->GetType() == " + typeIDs[instanceResult->GetType()] + ");\n";
					output += "\n";
				}
				else
				{
					throw Nu::NotImplementedException();
				}

				auto &arguments = algorithm->GetArguments();
				auto argumentsID = algorithmID + "_arguments";

				output += "auto &" + argumentsID + " = " + algorithmID + "->GetArguments();\n";
				output += "\n";
				output += "Assert::IsTrue(" + argumentsID + ".size() == " + std::to_string(arguments.size()) + ");\n";
				output += "\n";

				for (Nu::Size i = 0; i < arguments.size(); ++i)
				{
					auto &argument = arguments[i];
					auto algorithmArgumentID = algorithmID + "_argument" + std::to_string(i + 1);

					algorithmArgumentIDs[argument] = algorithmArgumentID;

					if (auto instanceArgument = Nu::UpCast<Nu::Eta2::Algorithm::Argument::Instance>(argument))
					{
						if (typeIDs.find(instanceArgument->GetInstance()->GetType()) == typeIDs.end())
						{
							throw Nu::Exception();
						}

						output += "auto &" + algorithmArgumentID + " = UpCast<Algorithm::Argument::Instance>(" + argumentsID + "[" + std::to_string(i) + "]);\n";
						output += "\n";
						output += "Assert::IsTrue(" + algorithmArgumentID + " != nullptr);\n";
						output += "Assert::IsTrue(" + algorithmArgumentID + "->GetInstance()->GetType() == " + typeIDs[instanceArgument->GetInstance()->GetType()] + ");\n";
						output += "\n";
					}
					else
					{
						throw Nu::NotImplementedException();
					}
				}
			}

			auto &instances = assembly->GetInstances();
			
			Nu::Map<Nu::Reference<Nu::Eta2::Instance>, Nu::String> instanceIDs;
			{
				for (auto &it : instances)
				{
					instanceIDs[it.second] = it.first;
				}
			}


			output += "auto &instances = assembly->GetInstances();\n";
			output += "\n";

			for (auto &it : algorithms)
			{
				auto &algorithmName = it.first;
				auto &algorithm = it.second;
				auto algorithmID = algorithmIDs[algorithm];
				auto &commands = algorithm->GetCommands();
				auto commandsID = algorithmID + "_commands";

				output += "auto &" + commandsID + " = " + algorithmID + "->GetCommands();\n";
				output += "\n";
				output += "Assert::IsTrue(" + commandsID + ".size() == " + std::to_string(commands.size()) + ");\n";
				output += "\n";
			
				auto &result = algorithm->GetResult();
				auto resultID = algorithmResultIDs[result];

				for (Nu::Size i = 0; i < commands.size(); ++i)
				{
					auto &command = commands[i];
					auto commandID = algorithmID + "_command" + std::to_string(i + 1);

					if (auto createInstanceCommand = Nu::UpCast<Nu::Eta2::Algorithm::Command::CreateInstance>(command))
					{
						output += "auto &" + commandID + " = UpCast<Algorithm::Command::CreateInstance>(" + commandsID + "[" + std::to_string(i) + "]);\n";
						output += "\n";
						output += "Assert::IsTrue(" + commandID + " != nullptr);\n";
						output += "Assert::IsTrue(" + commandID + "->GetInstance() != nullptr);\n";
						output += "\n";
					}
					else if (auto returnInstanceCommand = Nu::UpCast<Nu::Eta2::Algorithm::Command::ReturnInstance>(command))
					{
						output += "auto &" + commandID + " = UpCast<Algorithm::Command::ReturnInstance>(" + commandsID + "[" + std::to_string(i) + "]);\n";
						output += "\n";
						output += "Assert::IsTrue(" + commandID + " != nullptr);\n";
						output += "Assert::IsTrue(" + commandID + "->GetInstance() != nullptr);\n";

						if (Nu::UpCast<Nu::Eta2::Algorithm::Result::Instance>(result))
						{
							output += "Assert::IsTrue(" + commandID + "->GetInstance()->GetType() == " + resultID + "->GetType());\n";
						}
						else
						{
							throw Nu::NotImplementedException();
						}

						output += "\n";
					}
					else if (auto callAlgorithmCommand = Nu::UpCast<Nu::Eta2::Algorithm::Command::CallAlgorithm>(command))
					{
						auto &targetAlgorithm = callAlgorithmCommand->GetAlgorithm();

						if (algorithmIDs.find(targetAlgorithm) == algorithmIDs.end())
						{
							throw Nu::Exception();
						}

						auto &targetAlgorithmResult = targetAlgorithm->GetResult();
						auto &targetAlgorithmArguments = targetAlgorithm->GetArguments();

						output += "auto &" + commandID + " = UpCast<Algorithm::Command::CallAlgorithm>(" + commandsID + "[" + std::to_string(i) + "]);\n";
						output += "\n";
						output += "Assert::IsTrue(" + commandID + " != nullptr);\n";
						output += "Assert::IsTrue(" + commandID + "->GetAlgorithm() == " + algorithmIDs[targetAlgorithm] + ");\n";
						output += "\n";

						auto callResult = callAlgorithmCommand->GetResult();
						auto callResultID = commandID + "_result";
						
						if (auto instanceResult = Nu::UpCast<Nu::Eta2::Algorithm::Command::CallAlgorithm::Result::Instance>(callResult))
						{
							output += "auto &" + callResultID + " = UpCast<Algorithm::Command::CallAlgorithm::Result::Instance>(" + commandID + "->GetResult());\n";
							output += "\n";

							output += "Assert::IsTrue(" + callResultID + " != nullptr);\n";
							output += "Assert::IsTrue(" + callResultID + "->GetInstance() != nullptr);\n";

							if (Nu::UpCast<Nu::Eta2::Algorithm::Result::Instance>(targetAlgorithmResult))
							{
								if (algorithmResultIDs.find(targetAlgorithmResult) == algorithmResultIDs.end())
								{
									throw Nu::Exception();
								}

								output += "Assert::IsTrue(" + callResultID + "->GetInstance()->GetType() == " + algorithmResultIDs[targetAlgorithmResult] + "->GetType());\n";
							}
							else
							{
								throw Nu::NotImplementedException();
							}

							output += "\n";
						}
						else
						{
							throw Nu::NotImplementedException();
						}

						auto callArguments = callAlgorithmCommand->GetArguments();

						if (callArguments.size() != targetAlgorithmArguments.size())
						{
							throw Nu::Exception();
						}

						auto callArgumentsID = commandID + "_arguments";

						output += "auto &" + callArgumentsID + " = " + commandID + "->GetArguments();\n";
						output += "\n";
						output += "Assert::IsTrue(" + callArgumentsID + ".size() == " + std::to_string(targetAlgorithmArguments.size()) + ");\n";
						output += "\n";

						for (Nu::Size i = 0; i < callArguments.size(); ++i)
						{
							auto &callArgument = callArguments[i];
							auto callArgumentID = callArgumentsID + "_argument" + std::to_string(i + 1);

							if (auto instanceArgument = Nu::UpCast<Nu::Eta2::Algorithm::Command::CallAlgorithm::Argument::Instance>(callArgument))
							{
								output += "auto &" + callArgumentID + " = UpCast<Algorithm::Command::CallAlgorithm::Argument::Instance>(" + callArgumentsID + "[" + std::to_string(i) + "]);\n";
								output += "\n";
								output += "Assert::IsTrue(" + callArgumentID + " != nullptr);\n";

								auto &instance = instanceArgument->GetInstance();

								if (instanceIDs.find(instance) == instanceIDs.end())
								{
									throw Nu::Exception();
								}

								output += "Assert::IsTrue(" + callArgumentID + "->GetInstance() == instances[\"" + ScreenCharacters(instanceIDs[instance]) + "\"]);\n";

								auto &expectedArgument = targetAlgorithmArguments[i];

								if (algorithmArgumentIDs.find(expectedArgument) == algorithmArgumentIDs.end())
								{
									throw Nu::Exception();
								}

								auto &expectedArgumentID = algorithmArgumentIDs[expectedArgument];

								if (auto expectedInstanceArgument = Nu::UpCast<Nu::Eta2::Algorithm::Argument::Instance>(expectedArgument))
								{
									output += "Assert::IsTrue(" + callArgumentID + "->GetInstance()->GetType() == " + expectedArgumentID + "->GetInstance()->GetType()]);\n";
								}
								else
								{
									throw Nu::NotImplementedException();
								}

								output += "\n";
							}
							else
							{
								throw Nu::NotImplementedException();
							}
						}
					}
					else
					{
						throw Nu::NotImplementedException();
					}
				}
			}

			// output += "auto &instances = assembly->GetInstances();\n";

			std::ofstream file(L"output.cpp");
			{
				file.write(output.data(), output.size());
				file.close();
			}
		}
	// }
	// catch (...)
	// {
	// 	std::cout << "ERROR" << std::endl;
	// 
	// 	std::system("pause");
	// }
}