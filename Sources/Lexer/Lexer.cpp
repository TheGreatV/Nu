#include "Lexer.hpp"


#pragma region Nu

#pragma region Lexing

#pragma region Scope

/*bool Nu::Lexing::Scope::IsExist(const Reference<Identifier>& identifier_)
{
	auto result = unitsMapping.find(identifier_) != unitsMapping.end();
	return result;
}

void Nu::Lexing::Scope::Add(const Reference<Identifier>& identifier_, const Reference<Unit>& unit_)
{
	unitsMapping[identifier_] = unit_;
}*/
inline Nu::Lexing::Scope::Identifiers Nu::Lexing::Scope::GetIdentifiers() const
{
	auto owned = GetOwnedIdentifiers();

	auto parent = !scope.expired()
		? GetScope()->GetIdentifiers()
		: Identifiers();

	for(auto &identifier : parent)
	{
		if(std::find_if(owned.begin(), owned.end(), [&](const Reference<Identifier>& identifier_)
			{
				return identifier_->GetValue() == identifier->GetValue();
			}
		) == owned.end())
		{
			owned.push_back(identifier);
		}
	}

	return owned;
}

#pragma endregion

#pragma region Lexer

#pragma region MarkersPerformer

Nu::Size Nu::Lexing::Lexer::MarkersPerformer::ExtractNameNestingLevel(const NamesDeclarationStage::Text::Value& value_, Size& i_)
{
	Size nestingLevel = 0;

	while(true)
	{
		if(i_ < value_.size())
		{
			auto x = value_[i_];

			if(NamesDeclarationStage::IsWhitespace(x))
			{
				++i_;
			}
			else if(x == '.')
			{
				++i_;
				++nestingLevel;
			}
			else
			{
				break;
			}
		}
		else
		{
			throw Exception();
		}
	}

	return nestingLevel;
}
Nu::NamesDeclarationStage::Text::Value Nu::Lexing::Lexer::MarkersPerformer::ExtractNameHeader(const NamesDeclarationStage::Text::Value& value_, Size& i_)
{
	auto begin = i_;
	auto end = i_;

	while(end < value_.size())
	{
		auto x = value_[end];

		if(NamesDeclarationStage::IsSymbol(x))
		{
			++end;
		}
		else
		{
			break;
		}
	}

	auto header = value_.substr(begin, end - begin);

	i_ = end;

	return header;
}

void Nu::Lexing::Lexer::MarkersPerformer::Perform(const Reference<NamesDeclarationStage::Text>& text_)
{
	auto value = text_->GetValue();

	Size i = 0;
	auto nestingLevel = ExtractNameNestingLevel(value, i);
	auto nameHeader = ExtractNameHeader(value, i);

	auto identifiers = scope->GetIdentifiers();

	for(auto &identifier : identifiers)
	{
		auto name = identifier->GetValue();
		if(nameHeader.substr(0, name.size()) == name)
		{
			// auto nameTail = value.substr(i, value.length() - i);
			return;
		}
	}

	throw Exception();
}
void Nu::Lexing::Lexer::MarkersPerformer::Perform(const Reference<NamesDeclarationStage::Scope>& scope_)
{
	lexer->ParseInternal(scope_);
}

#pragma endregion


#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion

