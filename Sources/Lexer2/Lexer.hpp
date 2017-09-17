#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing2
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
			inline Token() = delete;
			inline Token(const Reference<Token>& this_);
			inline Token(const Token&) = delete;
			virtual ~Token() override = default;
		public:
			inline Token& operator = (const Token&) = delete;
		};
		class Text:
			public Token
		{
		public:
			using Value = String;
		protected:
			const Value value;
		public:
			inline Text() = delete;
			inline Text(const Reference<Text>& this_, const Value& value_);
			inline Text(const Text&) = delete;
			virtual ~Text() override = default;
		public:
			inline Text& operator = (const Text&) = delete;
		public:
			inline Value GetValue() const;
		};
		class Container:
			public Entity
		{
		public:
			using Tokens = Vector<Reference<Token>>;
		protected:
			Tokens tokens;
		public:
			inline Container() = delete;
			inline Container(const Group&) = delete;
			inline Container(const Reference<Container>& this_, const Tokens& tokens_ = Tokens());
			virtual ~Container() override = default;
		public:
			inline Group& operator = (const Group&) = delete;
		public:
			inline Tokens& GetTokens();
		};
		class Group:
			public Token,
			public Container
		{
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
		public:
			inline Group() = delete;
			inline Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_, const Tokens& tokens_ = Tokens());
			inline Group(const Group&) = delete;
			virtual ~Group() override = default;
		public:
			inline Group& operator = (const Group&) = delete;
		public:
			inline BraceType GetOpening() const;
			inline BraceType GetClosing() const;
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
			inline Special() = delete;
			inline Special(const Reference<Special>& this_, const Value& value_);
			inline Special(const Special&) = delete;
			virtual ~Special() override = default;
		public:
			inline Special& operator = (const Special&) = delete;
		public:
			inline Value GetValue() const;
		};
		class Lexer:
			public Entity
		{
		public:
			using Input = String;
			using Output = Reference<Container>;
			using Glyph = char;
		protected:
			using It = Input::const_iterator;
		protected:
			inline static It SkipWhitespaces(const Input& input_, It& it_);
			inline static Group::BraceType ExtractOpeningBraceType(const Glyph& glyph_);
			inline static Group::BraceType ExtractClosingBraceType(const Glyph& glyph_);
		public:
			inline static bool IsWhitespace(const Glyph& glyph_);
			inline static bool IsUnderscore(const Glyph& glyph_);
			inline static bool IsDigin(const Glyph& glyph_);
			inline static bool IsLetter(const Glyph& glyph_);
			inline static bool IsSign(const Glyph& glyph_);
			inline static bool IsSymbol(const Glyph& glyph_);
		public:
			inline Lexer() = delete;
			inline Lexer(const Reference<Lexer>& this_);
			inline Lexer(const Lexer&) = delete;
			virtual ~Lexer() override = default;
		public:
			inline Lexer& operator = (const Lexer&) = delete;
		protected:
			inline Reference<Text> ParseText(const Input& input_, It& it_);
			inline Reference<Group> ParseGroup(const Input& input_, It& it_);
			inline Reference<Special> ParseSpecial(const Input& input_, It& it_);
			inline Reference<Token> ParseAnyToken(const Input& input_, It& it_);
		public:
			inline Output Parse(const Input& input_);
		};
	}
}


#pragma region Nu

#pragma region Lexing2

#pragma region Token

inline Nu::Lexing2::Token::Token(const Reference<Token>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Text

inline Nu::Lexing2::Text::Text(const Reference<Text>& this_, const Value& value_):
	Token(this_),
	value(value_)
{
}

inline Nu::Lexing2::Text::Value Nu::Lexing2::Text::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Container

inline Nu::Lexing2::Container::Container(const Reference<Container>& this_, const Tokens& tokens_) :
	Entity(this_),
	tokens(tokens_)
{
}

inline Nu::Lexing2::Container::Tokens& Nu::Lexing2::Container::GetTokens()
{
	return tokens;
}

#pragma endregion

#pragma region Group

inline Nu::Lexing2::Group::Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_, const Tokens& tokens_) :
	Token(this_),
	Container(this_, tokens_),
	opening(opening_),
	closing(closing_)
{
}

inline Nu::Lexing2::Group::BraceType Nu::Lexing2::Group::GetOpening() const
{
	return opening;
}
inline Nu::Lexing2::Group::BraceType Nu::Lexing2::Group::GetClosing() const
{
	return closing;
}

#pragma endregion

#pragma region Special

inline Nu::Lexing2::Special::Special(const Reference<Special>& this_, const Value& value_):
	Token(this_),
	value(value_)
{

}

inline Nu::Lexing2::Special::Value Nu::Lexing2::Special::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Lexer

inline Nu::Lexing2::Lexer::It Nu::Lexing2::Lexer::SkipWhitespaces(const Input& input_, It& it_)
{
	auto it = it_;

	while (it != input_.cend() && IsWhitespace(*it))
	{
		++it;
	}

	return it;
}
inline Nu::Lexing2::Group::BraceType Nu::Lexing2::Lexer::ExtractOpeningBraceType(const Glyph& glyph_)
{
	if (glyph_ == '{')
	{
		return Group::BraceType::Figure;
	}
	else if (glyph_ == '(')
	{
		return Group::BraceType::Round;
	}
	else if (glyph_ == '[')
	{
		return Group::BraceType::Square;
	}
	else
	{
		return Group::BraceType::None;
	}
}
inline Nu::Lexing2::Group::BraceType Nu::Lexing2::Lexer::ExtractClosingBraceType(const Glyph& glyph_)
{
	if (glyph_ == '}')
	{
		return Group::BraceType::Figure;
	}
	else if (glyph_ == ')')
	{
		return Group::BraceType::Round;
	}
	else if (glyph_ == ']')
	{
		return Group::BraceType::Square;
	}
	else
	{
		return Group::BraceType::None;
	}
}

inline bool Nu::Lexing2::Lexer::IsWhitespace(const Glyph& glyph_)
{
	return 
		glyph_ == ' ' ||
		glyph_ == '\t' ||
		glyph_ == '\r' ||
		glyph_ == '\n';
}
inline bool Nu::Lexing2::Lexer::IsUnderscore(const Glyph& glyph_)
{
	return
		glyph_ == '_';
}
inline bool Nu::Lexing2::Lexer::IsDigin(const Glyph& glyph_)
{
	return
		glyph_ == '0' ||
		glyph_ == '1' ||
		glyph_ == '2' ||
		glyph_ == '3' ||
		glyph_ == '4' ||
		glyph_ == '5' ||
		glyph_ == '6' ||
		glyph_ == '7' ||
		glyph_ == '8' ||
		glyph_ == '9';
}
inline bool Nu::Lexing2::Lexer::IsLetter(const Glyph& glyph_)
{
	return
		glyph_ == 'a' || glyph_ == 'A' ||
		glyph_ == 'b' || glyph_ == 'B' ||
		glyph_ == 'c' || glyph_ == 'C' ||
		glyph_ == 'd' || glyph_ == 'D' ||
		glyph_ == 'e' || glyph_ == 'E' ||
		glyph_ == 'f' || glyph_ == 'F' ||
		glyph_ == 'g' || glyph_ == 'G' ||
		glyph_ == 'h' || glyph_ == 'H' ||
		glyph_ == 'i' || glyph_ == 'I' ||
		glyph_ == 'j' || glyph_ == 'J' ||
		glyph_ == 'k' || glyph_ == 'K' ||
		glyph_ == 'l' || glyph_ == 'L' ||
		glyph_ == 'm' || glyph_ == 'M' ||
		glyph_ == 'n' || glyph_ == 'N' ||
		glyph_ == 'o' || glyph_ == 'O' ||
		glyph_ == 'p' || glyph_ == 'P' ||
		glyph_ == 'q' || glyph_ == 'Q' ||
		glyph_ == 'r' || glyph_ == 'R' ||
		glyph_ == 's' || glyph_ == 'S' ||
		glyph_ == 't' || glyph_ == 'T' ||
		glyph_ == 'u' || glyph_ == 'U' ||
		glyph_ == 'v' || glyph_ == 'V' ||
		glyph_ == 'w' || glyph_ == 'W' ||
		glyph_ == 'x' || glyph_ == 'X' ||
		glyph_ == 'y' || glyph_ == 'Y' ||
		glyph_ == 'z' || glyph_ == 'Z';
}
inline bool Nu::Lexing2::Lexer::IsSign(const Glyph& glyph_)
{
	return
		glyph_ == '~' ||
		glyph_ == '!' ||
		glyph_ == '@' ||
		glyph_ == '#' ||
		glyph_ == '$' ||
		glyph_ == '%' ||
		glyph_ == '^' ||
		glyph_ == '&' ||
		glyph_ == '<' ||
		glyph_ == '>' ||
		glyph_ == '+' ||
		glyph_ == '-' ||
		glyph_ == '*' ||
		glyph_ == '/' ||
		glyph_ == '|' ||
		glyph_ == '\\' ||
		glyph_ == '?';
}
inline bool Nu::Lexing2::Lexer::IsSymbol(const Glyph& glyph_)
{
	return
		IsUnderscore(glyph_) ||
		IsDigin(glyph_) ||
		IsLetter(glyph_) ||
		IsSign(glyph_);
}

inline Nu::Lexing2::Lexer::Lexer(const Reference<Lexer>& this_):
	Entity(this_)
{
}

inline Nu::Reference<Nu::Lexing2::Text> Nu::Lexing2::Lexer::ParseText(const Input& input_, It& it_)
{
	auto o = it_;
	auto it = SkipWhitespaces(input_, it_);

	auto begin = it;

	while (it != input_.cend() && IsSymbol(*it))
	{
		++it;
	}

	auto end = it;

	if (begin != end)
	{
		auto value = Text::Value(begin, end);
		auto text = Make<Text>(value);

		it_ = it;

		return Move(text);
	}

	it_ = o;
	
	return nullptr;
}
inline Nu::Reference<Nu::Lexing2::Group> Nu::Lexing2::Lexer::ParseGroup(const Input& input_, It& it_)
{
	auto o = it_;
	auto it = SkipWhitespaces(input_, it_);

	auto begin = it;
	if (begin != input_.cend())
	{
		auto beginValue = *it;

		++it;

		auto openingBraceType = ExtractOpeningBraceType(beginValue);
	
		if (openingBraceType != Group::BraceType::None)
		{
			auto tokens = Group::Tokens();

			while (auto token = ParseAnyToken(input_, it))
			{
				tokens.push_back(token);
			}

			it = SkipWhitespaces(input_, it);

			auto end = it;

			if (end != input_.cend())
			{
				auto endValue = *it;

				++it;

				auto closingBraceType = ExtractClosingBraceType(endValue);

				if (closingBraceType != Group::BraceType::None)
				{
					auto group = Make<Group>(openingBraceType, closingBraceType, Move(tokens));

					it_ = it;

					return Move(group);
				}
			}
			else
			{
				throw Exception(); // TODO
			}
		}
	}

	it_ = o;

	return nullptr;
}
inline Nu::Reference<Nu::Lexing2::Special> Nu::Lexing2::Lexer::ParseSpecial(const Input& input_, It& it_)
{
	auto o = it_;
	auto it = SkipWhitespaces(input_, it_);

	if (it != input_.cend())
	{
		auto value = *it;

		++it;

		if (value == '.')
		{
			auto special = Make<Special>(Special::Value::Dot);

			it_ = it;

			return Move(special);
		}
		else if (value == ',')
		{
			auto special = Make<Special>(Special::Value::Comma);

			it_ = it;

			return Move(special);
		}
		else if (value == ':')
		{
			auto special = Make<Special>(Special::Value::Colon);

			it_ = it;

			return Move(special);
		}
		else if (value == ';')
		{
			auto special = Make<Special>(Special::Value::Semicolon);

			it_ = it;

			return Move(special);
		}
	}

	it_ = o;

	return nullptr;
}
inline Nu::Reference<Nu::Lexing2::Token> Nu::Lexing2::Lexer::ParseAnyToken(const Input& input_, It& it_)
{
	auto o = it_;

	if (auto text = ParseText(input_, it_))
	{
		return Move(text);
	}

	if (auto special = ParseSpecial(input_, it_))
	{
		return Move(special);
	}

	if (auto group = ParseGroup(input_, it_))
	{
		return Move(group);
	}

	it_ = o;
	
	return nullptr;
}

inline Nu::Lexing2::Lexer::Output Nu::Lexing2::Lexer::Parse(const Input& input_)
{
	auto mainContainer = Make<Container>();

	auto it = input_.cbegin();

	while (auto token = ParseAnyToken(input_, it))
	{
		auto &tokens = mainContainer->GetTokens();

		tokens.push_back(token);
	}

	SkipWhitespaces(input_, it);

	if (it != input_.end())
	{
		throw Exception(); // TODO
	}

	return Move(mainContainer);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















