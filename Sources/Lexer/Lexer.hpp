#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing
	{
		class Identifier;

		class Token;
		class Name;
		class Scope;

		class Lexer;


		class Identifier:
			public Entity
		{
		public:
			using Value = String;
		protected:
			const Value value;
		public:
			inline Identifier(const Reference<Identifier>& this_, const Value& value_);
			virtual ~Identifier() override = default;
		public:
			inline Value GetValue() const;
		};

		class Token:
			public Entity
		{
		public:
			inline Token(const Reference<Token>& this_);
			virtual ~Token() override = default;
		};
		class Name:
			public Token
		{
		public:
			inline Name(const Reference<Name>& this_);
			virtual ~Name() override = default;
		};
		class Scope:
			public Token
		{
		public:
			inline Scope(const Reference<Scope>& this_);
			virtual ~Scope() override = default;
		};

		class Lexer:
			public Entity
		{
		public:
			inline Lexer(const Reference<Lexer>& this_);
			virtual ~Lexer() override = default;
		protected:
			inline void ExtractIdentifiers();
		public:
			inline void Parse(const Reference<NamesDeclarationStage::Scope>& scope_);
		};
	}
}


#pragma region Nu

#pragma region Lexing

#pragma region Identifier

inline Nu::Lexing::Identifier::Identifier(const Reference<Identifier>& this_, const Value& value_):
	Entity(this_),
	value(value_)
{
}

inline Nu::Lexing::Identifier::Value Nu::Lexing::Identifier::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Token

inline Nu::Lexing::Token::Token(const Reference<Token>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Name

inline Nu::Lexing::Name::Name(const Reference<Name>& this_):
	Token(this_)
{
}

#pragma endregion

#pragma region Scope

inline Nu::Lexing::Scope::Scope(const Reference<Scope>& this_):
	Token(this_)
{
}

#pragma endregion

#pragma region Lexer

inline void Nu::Lexing::Lexer::Parse(const Reference<NamesDeclarationStage::Scope>& scope_)
{

}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















