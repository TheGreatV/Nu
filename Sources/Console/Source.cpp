#include <iostream>
#include <fstream>

#include <../Cleaner/Cleaner.hpp>
#include <../Parser/Parser.hpp>
#include <../Lexer/Lexer.hpp>
using namespace Nu;


void print(const Reference<NamesDeclarationStage::Marker>& marker)
{
	static int tab = 0;

	if(auto scope = Nu::UpCast<Nu::NamesDeclarationStage::Scope>(marker))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';

		auto openingBrace =
			scope->opening == NamesDeclarationStage::Scope::BraceType::Round ? "(" :
			scope->opening == NamesDeclarationStage::Scope::BraceType::Figure ? "{" :
			scope->opening == NamesDeclarationStage::Scope::BraceType::Square ? "[" :
			throw Exception();

		std::cout << openingBrace << std::endl;

		++tab;

		for(auto &marker : scope->GetMarkers())
		{
			print(marker);
		}
		/*for(auto &i : scope->identifiers)
		{
			for(int t = 0; t < tab; ++t) std::cout << '\t';

			std::cout << i->GetValue() << std::endl;
		}

		for(auto &i : scope->units)
		{
			if(auto s = Nu::UpCast<Nu::NamesDeclarationStage::Scope>(i))
			{
				print(s);
			}
		}*/

		--tab;

		for(int t = 0; t < tab; ++t) std::cout << '\t';

		auto closingBrace =
			scope->closing == NamesDeclarationStage::Scope::BraceType::Round ? ")" :
			scope->closing == NamesDeclarationStage::Scope::BraceType::Figure ? "}" :
			scope->closing == NamesDeclarationStage::Scope::BraceType::Square ? "]" :
			throw Exception();

		std::cout << closingBrace << std::endl;
	}
	else if(auto text = Nu::UpCast<Nu::NamesDeclarationStage::Text>(marker))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		std::cout << '"' << text->GetValue() << '"' << std::endl;
	}
	else if(auto declaration = Nu::UpCast<Nu::NamesDeclarationStage::Declaration>(marker))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		std::cout << '<' << declaration->GetIdentifier()->GetValue() << '>' << std::endl;
	}
}


void main()
{
	NamesDeclarationStage::Parser::Source source;
	{
		std::ifstream file(L"../../../../Media/Source.ν"); // relative to project (.vcxproj)
		std::getline(file, source, '\0');
		file.close();
	}

	// std::cout << "source:" << std::endl << source << std::endl;
	
	auto cleaner = Make<Cleaning::Cleaner>();
	auto cleanCode = cleaner->Parse(source);

	// std::cout << "clean:" << std::endl << cleanCode << std::endl;

	auto parser = Make<NamesDeclarationStage::Parser>();
	auto nameScope = parser->Parse(cleanCode);
	
	std::cout << "structure:" << std::endl;
	print(nameScope);
	
	auto lexer = Make<Lexing::Lexer>();
	auto tokenScope = lexer->Parse(nameScope);

	std::system("pause");
}


#pragma region
#pragma endregion
