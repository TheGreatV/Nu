#include "Lexer.hpp"


#pragma region Nu

#pragma region Lexing

/*
#pragma region Scope

Nu::Vector<Nu::Lexing::Scope::IdentifierAccessor> Nu::Lexing::Scope::GetIdentifiers() const
{
	Vector<IdentifierAccessor> owned;

	Map<Reference<Identifier>, Size> ownedCounter;

	for(auto &identifier : identifiers)
	{
		auto nestingLevel = [&]() -> Size
		{
			if(ownedCounter.find(identifier) == ownedCounter.end())
			{
				ownedCounter[identifier] = 0;
				return 0;
			}
			else
			{
				++ownedCounter[identifier];
				return ownedCounter[identifier];
			}
		}();
		
		owned.push_back(IdentifierAccessor(identifier, nestingLevel));
	}

	auto inherited = !scope.expired()
		? GetScope()->GetIdentifiers()
		: Vector<IdentifierAccessor>();

	for(auto &accessor : inherited)
	{
		auto identifier = accessor.GetIdentifier();

		if(ownedCounter.find(identifier) != ownedCounter.end())
		{
			owned.push_back(IdentifierAccessor(identifier, accessor.GetNestingLevel() + ownedCounter[identifier]));
		}
		else
		{
			owned.push_back(accessor);
		}
	}

	return owned;
}

#pragma endregion

#pragma region Lexer

#pragma region MarkersPerformer

void Nu::Lexing::Lexer::MarkersPerformer::Perform(const Reference<NamesDeclarationStage::Text>& marker_)
{
	auto sourceText = Make<SoureText>(marker_->GetValue());
	scope->Add(sourceText);
}
void Nu::Lexing::Lexer::MarkersPerformer::Perform(const Reference<NamesDeclarationStage::Declaration>& marker_)
{
	auto identifier = lexer->identifiersLookup[marker_->GetIdentifier()];
	auto declaration = Make<Declaration>(identifier);
	scope->Add(declaration);
}
void Nu::Lexing::Lexer::MarkersPerformer::Perform(const Reference<NamesDeclarationStage::Scope>& marker_)
{
	auto childScope = Make<Scope>(scope);
	lexer->scopesLookup[marker_] = childScope;
	scope->Add(childScope);

	lexer->Prepare(childScope, marker_);
}

#pragma endregion


#pragma endregion
*/

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion

