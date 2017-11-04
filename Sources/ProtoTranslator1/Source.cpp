﻿#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <clocale>

#include <../Cleaner/Cleaner.hpp>
#include <../Parser3/Parser.hpp>
#include <Windows.h>


void collectSchemas(const Nu::Reference<Nu::Parsing3::MarkersContainer>& markersContainer_, Nu::Vector<Nu::Reference<Nu::Parsing3::Schema>>& schemas_);
void collectSchemas(const Nu::Reference<Nu::Parsing3::Scope>& scope_, Nu::Vector<Nu::Reference<Nu::Parsing3::Schema>>& schemas_);

void collectSchemas(const Nu::Reference<Nu::Parsing3::MarkersContainer>& markersContainer_, Nu::Vector<Nu::Reference<Nu::Parsing3::Schema>>& schemas_)
{
	auto &markers = markersContainer_->GetMarkers();

	auto add = [&](const Nu::Reference<Nu::Parsing3::Schema>& schema_)
	{
		if (std::find(schemas_.begin(), schemas_.end(), schema_) == schemas_.end())
		{
			schemas_.push_back(schema_);
		}
	};

	for (auto &marker : markers)
	{
		if (auto schema = Nu::UpCast<Nu::Parsing3::Schema>(marker))
		{
			add(schema);
		}
		else if (auto declaration = Nu::UpCast<Nu::Parsing3::Markers::Declaration>(marker))
		{
			auto unit = declaration->GetUnit();

			if (auto schema = Nu::UpCast<Nu::Parsing3::Schema>(unit))
			{
				add(schema);
			}

			if (auto scope = Nu::UpCast<Nu::Parsing3::Scope>(unit))
			{
				collectSchemas(scope, schemas_);
			}
		}

		if (auto scope = Nu::UpCast<Nu::Parsing3::Scope>(marker))
		{
			collectSchemas(scope, schemas_);
		}
	}
}
void collectSchemas(const Nu::Reference<Nu::Parsing3::Scope>& scope_, Nu::Vector<Nu::Reference<Nu::Parsing3::Schema>>& schemas_)
{
	if (auto markersContainer = Nu::UpCast<Nu::Parsing3::MarkersContainer>(scope_))
	{
		collectSchemas(markersContainer, schemas_);
	}
}

void wmain(int argc, wchar_t* argv[])
{
	_setmode(_fileno(stdout), _O_WTEXT);

	// std::wcout << L"argc: " << argc << L'\n';
	// 
	// for (int i = 0; i < argc; ++i)
	// {
	// 	auto &arg = argv[i];
	// 
	// 	std::wcout << L"argv[" << i << L"]: " << arg << L'\n';
	// }

	// argc = 2;
	// argv = new wchar_t*[2];
	// argv[1] = L"F:/Projects/Projects/Nu/_Build/Microsoft Visual Studio Ultimate 2013/ProtoTranslator1/Win32/Debug/source.ν";

	Nu::Size totalFilesCount = argc > 1
		? static_cast<Nu::Size>(argc) - 1
		: 0;

	std::wcout << L"total files count: " << totalFilesCount << std::endl;

	Nu::Vector<Nu::WString> filenames(totalFilesCount);
	{
		for (std::size_t i = 0; i < totalFilesCount; ++i)
		{
			auto &filename = filenames[i];
			auto &rawFilename = argv[i + 1];

			filename = static_cast<Nu::WString>(rawFilename);
		}
	}

	Nu::Map<Nu::WString, Nu::Lexing2::Lexer::Input> inputs;
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

	Nu::Lexing2::Lexer::Input totalInput;
	{
		for (auto &inputIt : inputs)
		{
			auto &input = inputIt.second;

			totalInput += input;
		}
	}

	// std::cout << "totalInput: " << std::endl << totalInput << std::endl;

	auto cleaner = Nu::Make<Nu::Cleaning::Cleaner>();

	auto cleanSource = cleaner->Parse(totalInput);

	auto lexer = Nu::Make<Nu::Lexing2::Lexer>();

	auto tokens = lexer->Parse(cleanSource);

	auto parser = Nu::Make<Nu::Parsing3::Parser>();

	auto marker = parser->Parse(tokens);

	Nu::Vector<Nu::Reference<Nu::Parsing3::Schema>> schemas;
	collectSchemas(Nu::Cast<Nu::Parsing3::Scope>(marker), schemas);

	Nu::Map<Nu::Reference<Nu::Parsing3::Schema>, Nu::String> schemasNames;
	{
		Nu::Size i = 0;

		for (auto &schema : schemas)
		{
			Nu::String name = "schema #" + std::to_string(i++);

			schemasNames[schema] = name;
		}
	}

	Nu::String output;
	{
		// schemas declarations
		output += "# schemas declarations\n";

		for (auto schema : schemas)
		{
			auto &schemaName = schemasNames[schema];

			output += "schema \"" + schemaName + "\";\n";
		}

		output += "\n";

		// schemas definitions
		output += "# schemas definitions\n";

		for (auto schema : schemas)
		{
			auto &schemaName = schemasNames[schema];

			output += "\"" + schemaName + "\": {};\n";
		}
	}

	std::ofstream file(L"output.η");
	{
		file.write(output.data(), output.size());

		file.close();
	}

	std::wcout << "schemas count: " << schemas.size() << std::endl;

	std::system("pause");
}