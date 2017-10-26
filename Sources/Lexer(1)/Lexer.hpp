#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing
	{
		class Token;
		class Text;
		class Group;
		class Special;
		class Lexer;

		class Token:
			public Entity
		{
		public:
			inline Token(const Reference<Token>& this_);
			virtual ~Token() override = default;
		};
		class Text:
			public Token
		{
		public:
			using Value = String;
		protected:
			const Value value;
		public:
			inline Text(const Reference<Text>& this_, const Value& value_);
			virtual ~Text() override = default;
		public:
			inline Value GetValue() const;
		};
		class Group:
			public Token
		{
		public:
			using Tokens = Vector<Reference<Token>>;
		public:
			enum class BraceType
			{
				None, // not in use

				Round,
				Figure,
				Square,
			};
		protected:
			const BraceType opening;
			const BraceType closing;
			Tokens tokens;
		public:
			inline Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_);
			virtual ~Group() override = default;
		public:
			inline BraceType GetOpening() const;
			inline BraceType GetClosing() const;
			inline Tokens& GetTokens();
		};
		class Special:
			public Token
		{
		public:
			enum class Value
			{
				None, // not in use

				Dot,
				Comma,
				Colon,
				Semicolon,
			};
		protected:
			const Value value;
		public:
			inline Special(const Reference<Special>& this_, const Value& value_);
			virtual ~Special() override = default;
		public:
			inline Value GetValue() const;
		};
		class Lexer:
			public Entity
		{
		public:
			inline Lexer(const Reference<Lexer>& this_);
			virtual ~Lexer() override = default;
		public:
			inline Reference<Group> Parse();
		};
	}
}


#pragma region Nu

#pragma region Token

inline Nu::Lexing::Token::Token(const Reference<Token>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Text

inline Nu::Lexing::Text::Text(const Reference<Text>& this_, const Value& value_):
	Token(this_),
	value(value_)
{
}

inline Nu::Lexing::Text::Value Nu::Lexing::Text::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Group

inline Nu::Lexing::Group::Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_):
	Token(this_),
	opening(opening_),
	closing(closing_)
{
}

inline Nu::Lexing::Group::BraceType Nu::Lexing::Group::GetOpening() const
{
	return opening;
}
inline Nu::Lexing::Group::BraceType Nu::Lexing::Group::GetClosing() const
{
	return closing;
}
inline Nu::Lexing::Group::Tokens& Nu::Lexing::Group::GetTokens()
{
	return tokens;
}

#pragma endregion

#pragma region Special

inline Nu::Lexing::Special::Special(const Reference<Special>& this_, const Value& value_):
	Token(this_),
	value(value_)
{

}

inline Nu::Lexing::Special::Value Nu::Lexing::Special::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Lexer

inline Nu::Lexing::Lexer::Lexer(const Reference<Lexer>& this_):
	Entity(this_)
{
}

inline Nu::Reference<Nu::Lexing::Group> Nu::Lexing::Lexer::Parse()
{
	auto mainGroup = Make<Group>(Group::BraceType::Figure, Group::BraceType::Figure);

	return Move(mainGroup);
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















