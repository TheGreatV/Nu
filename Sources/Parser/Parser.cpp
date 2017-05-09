#include "Parser.hpp"


#pragma region Nu

#pragma region Entity

#pragma endregion

#pragma region NamesDeclarationStage

#pragma region Entity

#pragma endregion

#pragma region Identifier

#pragma endregion

#pragma region Marker

#pragma endregion

#pragma region Text

#pragma endregion

#pragma region Declaration

#pragma endregion

#pragma region Assembly

void Nu::NamesDeclarationStage::Assembly::Add(const Reference<Marker>& marker_)
{
	markers.push_back(marker_);
}

#pragma endregion

#pragma region Unit

#pragma endregion

#pragma region Scope

void Nu::NamesDeclarationStage::Scope::Add(const Reference<Marker>& marker_)
{
	Assembly::Add(marker_);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Declaration>& declaration_)
{
	Assembly::Add(declaration_);

	auto &identifier = declaration_->GetIdentifier();
	identifiers.push_back(identifier);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Unit>& unit_)
{
	Assembly::Add(unit_);

	units.push_back(unit_);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Scope>& scope_)
{
	Add(Cast<Unit>(scope_));
}

#pragma endregion

#pragma region Parser

#pragma endregion

#pragma endregion


bool Nu::NamesDeclarationStage::IsWhitespace(const char& value_)
{
	switch(value_)
	{
		case ' ':
		case '\t':
		case '\n':
			return true;
		default:
			return false;
	}
}
bool Nu::NamesDeclarationStage::IsDigit(const char& value_)
{
	switch(value_)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
		default:
			return false;
	}
}
bool Nu::NamesDeclarationStage::IsSmallLetter(const char& value_)
{
	switch(value_)
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			return true;
		default:
			return false;
	}
}
bool Nu::NamesDeclarationStage::IsCapitalLetter(const char& value_)
{
	switch(value_)
	{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return true;
		default:
			return false;
	}
};
bool Nu::NamesDeclarationStage::IsLetter(const char& value_)
{
	return
		IsSmallLetter(value_) ||
		IsCapitalLetter(value_);
}
bool Nu::NamesDeclarationStage::IsGlyph(const char& value_)
{
	return
		IsDigit(value_) ||
		IsLetter(value_) ||
		(value_ == '_')
		;
};
bool Nu::NamesDeclarationStage::IsSign(const char& value_)
{
	switch(value_)
	{
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '/':
		case '|':
		case '\\':
		case '<':
		case '>':
		case '?':
			return true;
		default:
			return false;
	}
};
bool Nu::NamesDeclarationStage::IsSymbol(const char& value_)
{
	return
		IsGlyph(value_) ||
		IsSign(value_);
}


Nu::String Nu::NamesDeclarationStage::RemoveWhitespaces(const Nu::String& source_)
{
	auto source = source_;

	while(!source.empty() && IsWhitespace(source.front()))
	{
		source.erase(source.begin());
	}

	while(!source.empty() && IsWhitespace(source.back()))
	{
		source.pop_back();
	}

	return source;
}

#pragma endregion































