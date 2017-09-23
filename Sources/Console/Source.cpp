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
		std::cout << '<' << declaration->GetIdentifier()->GetValue() << '>' << ':' << std::endl;
	}
	else if(auto specialSymbol = Nu::UpCast<Nu::NamesDeclarationStage::SpecialSymbol>(marker))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		auto symbol =
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Dot ? "." :
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Comma ? "," :
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Semicolon ? ";" :
			throw Exception();

		std::cout << symbol << std::endl;
	}
}

void print(const Reference<Lexing::Token>& token)
{
	static int tab = 0;

	if(auto group = Nu::UpCast<Nu::Lexing::Group>(token))
	{
		if(auto space = UpCast<Nu::Lexing::Space>(group))
		{
			for(int t = 0; t < tab; ++t) std::cout << '\t';
			std::cout << "(space)" << std::endl;
		}
		else if(auto scope = UpCast<Nu::Lexing::Space>(group))
		{
			for(int t = 0; t < tab; ++t) std::cout << '\t';
			std::cout << "(scope)" << std::endl;
		}
		else
		{
			for(int t = 0; t < tab; ++t) std::cout << '\t';
			std::cout << "(group)" << std::endl;
		}

		for(int t = 0; t < tab; ++t) std::cout << '\t';

		auto openingBrace =
			group->opening == Lexing::Group::BraceType::Round ? "(" :
			group->opening == Lexing::Group::BraceType::Figure ? "{" :
			group->opening == Lexing::Group::BraceType::Square ? "[" :
			throw Exception();

		std::cout << openingBrace << std::endl;

		++tab;

		for(auto &token : group->GetTokens())
		{
			print(token);
		}

		--tab;

		for(int t = 0; t < tab; ++t) std::cout << '\t';

		auto closingBrace =
			group->opening == Lexing::Group::BraceType::Round ? ")" :
			group->opening == Lexing::Group::BraceType::Figure ? "}" :
			group->opening == Lexing::Group::BraceType::Square ? "]" :
			throw Exception();

		std::cout << closingBrace << std::endl;
	}
	else if(auto text = Nu::UpCast<Nu::Lexing::Text>(token))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		std::cout << '"' << text->GetValue() << '"' << std::endl;
	}
	else if(auto declaration = Nu::UpCast<Nu::Lexing::Declaration>(token))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		std::cout << '<' << declaration->GetIdentifier()->GetName() << '>' << ':' << std::endl;
	}
	else if(auto specialSymbol = Nu::UpCast<Nu::Lexing::Symbol>(token))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		auto symbol =
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Dot ? "." :
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Comma ? "," :
			specialSymbol->GetType() == Nu::NamesDeclarationStage::SpecialSymbol::Type::Semicolon ? ";" :
			throw Exception();

		std::cout << symbol << std::endl;
	}
	else if(auto identifier = Nu::UpCast<Nu::Lexing::Identifier>(token))
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';
		std::cout << identifier->GetName() << std::endl;
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
	// std::cout << "source:" << std::endl;
	// std::cout << source << std::endl;
	
	auto cleaner = Make<Cleaning::Cleaner>();
	auto cleanCode = cleaner->Parse(source);
	std::cout << "clean:" << std::endl;
	std::cout << cleanCode << std::endl;

	auto parser = Make<NamesDeclarationStage::Parser>();
	auto nameScope = parser->Parse(cleanCode);
	std::cout << "structure:" << std::endl;
	print(nameScope);
	
	// auto lexer = Make<Lexing::Lexer>();
	// auto tokenGroup = lexer->Parse();

	// auto lexer = Make<Lexing::Lexer>();
	// auto tokenScope = lexer->Parse(nameScope);
	// std::cout << "tokens:" << std::endl;
	// print(Cast<Lexing::Scope>(tokenScope));

	std::system("pause");
}


#pragma region
#pragma endregion
