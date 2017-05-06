#include <iostream>

#include <../Parser/Parser.hpp>


void print(const Nu::Reference<Nu::NamesDeclarationStage::Scope>& scope)
{
	static int tab = 0;

	for(int t = 0; t < tab; ++t) std::cout << '\t';
	std::cout << "{" << std::endl;

	++tab;

	for(auto &i : scope->identifiers)
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
	}

	--tab;

	for(int t = 0; t < tab; ++t) std::cout << '\t';
	std::cout << "}" << std::endl;
}


void main()
{
	using namespace Nu;
	using namespace NamesDeclarationStage;

	/*
	// "a: schema { b: a; }"
	auto mainScope = Make<Scope>(nullptr); // implicit outer scope
	{
		auto identifier = Make<Identifier>();
		auto declaration = Make<Declaration>(identifier); // representation of "a:"
		mainScope->Assembly::Add(declaration);

		auto value = "schema";
		auto text = Make<Text>(value); // representation of "schema"
		mainScope->Add(text);

		auto scope = Make<Scope>(mainScope); // representation of "{ b: a; }"
		{
			auto nestedIdentifier = Make<Identifier>();
			auto nestedDeclaration = Make<Declaration>(nestedIdentifier); //representation of "b:"
			scope->Add(nestedDeclaration);

			auto nestedValue = "a;";
			auto nestedText = Make<Text>(nestedValue); // representation of "a;"
			scope->Add(nestedText);
		}
		mainScope->Add(scope);
	}
	*/

	// auto source = "a:{x:y:z:{vasya #pupkin:}}b:";
auto source =
"\
MySchema : schema\n\
{\n\
	algorithm none ()\n\
	body\n\
	{\n\
	}\n\
}\n\
myInstance: make MySchema;\n\
";
	// auto source = "{{}}";
	std::cout << source << std::endl;

	auto parser = Make<Parser>();
	auto scope = parser->Parse(source);

	print(scope);

	std::system("pause");
}


#pragma region
#pragma endregion
