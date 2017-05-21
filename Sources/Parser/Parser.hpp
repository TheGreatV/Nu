#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace NamesDeclarationStage
	{
		class Entity;

		class Identifier;

		class Marker;
		class Text;
		class Declaration;
		class Assembly;

		class Unit;
		class Scope;

		class Parser;


		class Entity:
			public Nu::Entity
		{
		public:
			inline Entity(const Reference<Entity>& this_);
			virtual ~Entity() override = default;
		};

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

		class Marker:
			public Entity
		{
		public:
			class Performer;
		public:
			inline Marker(const Reference<Marker>& this_);
			virtual ~Marker() override = default;
		public:
			virtual void Accept(const Reference<Performer>& performer_);
		};
#pragma region Marker::Performer
		class Marker::Performer:
			public Entity
		{
		public:
			inline Performer(const Reference<Entity>& this_);
			virtual ~Performer() = default;
		public:
			inline void Perform(const Reference<Marker>& marker_);
			virtual void Perform(const Reference<Text>& marker_);
			virtual void Perform(const Reference<Declaration>& marker_);
			virtual void Perform(const Reference<Scope>& marker_);
		};
#pragma endregion
		class Text:
			public Marker
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
		public:
			virtual void Accept(const Reference<Performer>& performer_) override;
		};
		class Declaration:
			public Marker
		{
		protected:
			const Reference<Identifier> identifier;
		public:
			inline Declaration(const Reference<Declaration>& this_, const Reference<Identifier>& identifier_);
			virtual ~Declaration() override = default;
		public:
			inline Reference<Identifier> GetIdentifier() const;
		public:
			virtual void Accept(const Reference<Performer>& performer_) override;
		};
		class Assembly
		{
		public:
			using Markers = Vector<Reference<Marker>>;
		protected:
			 Markers markers;
		public:
			inline Assembly() = default;
			virtual ~Assembly() = default;
		public:
			virtual void Add(const Reference<Marker>& marker_);
			inline const Markers& GetMarkers() const;
		};

		class Unit:
			public Marker
		{
		protected:
			const Link<Scope> scope;
		public:
			inline Unit(const Reference<Unit>& this_, const Reference<Scope>& scope_);
			virtual ~Unit() override = default;
		public:
			inline Reference<Scope> GetScope() const;
		};
		class Scope:
			public Unit,
			public Assembly
		{
		public:
			enum class BraceType
			{
				None, // Not in use
				Round,
				Figure,
				Square,
			};
			using Identifiers = Vector<Reference<Identifier>>;
		protected:
			Identifiers identifiers;
			Vector<Reference<Unit>> units;
		public:
			BraceType opening = BraceType::None;
			BraceType closing = BraceType::None;
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_);
			virtual ~Scope() override = default;
		public:
			virtual void Add(const Reference<Marker>& marker_); // C++ shit workaround
			virtual void Add(const Reference<Declaration>& declaration_);
			virtual void Add(const Reference<Unit>& unit_);
			virtual void Add(const Reference<Scope>& scope_); // C++ shit workaround
			inline Identifiers GetIdentifiers() const;
		public:
			virtual void Accept(const Reference<Performer>& performer_) override;
		};

		class Parser:
			public This<Parser>
		{
		public:
			using Source = String;
			using Iterator = int;
		public:
			inline Parser(const Reference<Parser>& this_);
		protected:
			inline void ParseScope(const Source& source_, Iterator& it_, const Reference<Scope>& scope_);
		public:
			inline Reference<Scope> Parse(const Source& source_);
		};


		bool IsWhitespace(const char& value_);
		bool IsDigit(const char& value_);
		bool IsSmallLetter(const char& value_);
		bool IsCapitalLetter(const char& value_);
		bool IsLetter(const char& value_);
		bool IsGlyph(const char& value_);
		bool IsSign(const char& value_);
		bool IsSymbol(const char& value_);
		bool IsOpeningBrace(const char& value_);
		bool IsClosingBrace(const char& value_);

		String RemoveWhitespaces(const Nu::String& source_);
	}
}


#pragma region Nu

#pragma region NamesDeclarationStage

#pragma region Entity

inline Nu::NamesDeclarationStage::Entity::Entity(const Reference<Entity>& this_):
	Nu::Entity(this_)
{
}

#pragma endregion

#pragma region Identifier

inline Nu::NamesDeclarationStage::Identifier::Identifier(const Reference<Identifier>& this_, const Value& value_):
Entity(this_),
value(value_)
{
}

inline Nu::NamesDeclarationStage::Identifier::Value Nu::NamesDeclarationStage::Identifier::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Marker

#pragma region Performer

inline Nu::NamesDeclarationStage::Marker::Performer::Performer(const Reference<Entity>& this_):
	Entity(this_)
{
}

inline void Nu::NamesDeclarationStage::Marker::Performer::Perform(const Reference<Marker>& marker_)
{
	marker_->Accept(GetThis<Performer>());
}

#pragma endregion


inline Nu::NamesDeclarationStage::Marker::Marker(const Reference<Marker>& this_):
Entity(this_)
{
}

#pragma endregion

#pragma region Text

inline Nu::NamesDeclarationStage::Text::Text(const Reference<Text>& this_, const Value& value_):
Marker(this_),
value(value_)
{
}

inline Nu::NamesDeclarationStage::Text::Value Nu::NamesDeclarationStage::Text::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Declaration

inline Nu::NamesDeclarationStage::Declaration::Declaration(const Reference<Declaration>& this_, const Reference<Identifier>& identifier_):
Marker(this_),
identifier(identifier_)
{
}

inline Nu::Reference<Nu::NamesDeclarationStage::Identifier> Nu::NamesDeclarationStage::Declaration::GetIdentifier() const
{
	return identifier;
}

#pragma endregion

#pragma region Assembly

inline const Nu::NamesDeclarationStage::Assembly::Markers& Nu::NamesDeclarationStage::Assembly::GetMarkers() const
{
	return markers;
}

#pragma endregion

#pragma region Unit

inline Nu::NamesDeclarationStage::Unit::Unit(const Reference<Unit>& this_, const Reference<Scope>& scope_):
Marker(this_),
scope(scope_)
{
}

inline Nu::Reference<Nu::NamesDeclarationStage::Scope> Nu::NamesDeclarationStage::Unit::GetScope() const
{
	return MakeReference(scope);
}

#pragma endregion

#pragma region Scope

inline Nu::NamesDeclarationStage::Scope::Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_):
	Unit(this_, scope_),
	Assembly()
{
}

inline Nu::NamesDeclarationStage::Scope::Identifiers Nu::NamesDeclarationStage::Scope::GetIdentifiers() const
{
	return identifiers;
}

#pragma endregion

#pragma region Parser

inline Nu::NamesDeclarationStage::Parser::Parser(const Reference<Parser>& this_):
This(this_)
{
}

inline void Nu::NamesDeclarationStage::Parser::ParseScope(const Source& source_, Iterator& it_, const Reference<Scope>& scope_)
{
	Iterator textBegin = it_;

	while(it_ < static_cast<Iterator>(source_.length()))
	{
		auto value = source_[it_];

		if(value == ':')
		{
			auto i = it_ > 0
				? it_ - 1
				: throw Exception("Illegal \":\"");

			while(i > 0 && IsWhitespace(source_[i]))
			{
				--i;
			}

			if(i > 0 && IsSymbol(source_[i]))
			{
				while(i >= 0 && IsSymbol(source_[i]))
				{
					--i;
				}
				++i;

				auto rawText = RemoveWhitespaces(source_.substr(textBegin, i - textBegin));
				textBegin = it_ + 1;
				if(!rawText.empty())
				{
					auto text = Make<Text>(rawText);
					scope_->Add(text);
					// std::cout << rawText << std::endl;
				}

				auto identifierValue = source_.substr(i, it_ - i);
				auto identifier = Make<Identifier>(identifierValue);
				auto declaration = Make<Declaration>(identifier);
				scope_->Add(declaration);
			}
			else
			{
				throw Exception("Illegal \":\"");
			}
		}
		else if(IsOpeningBrace(value))
		{
			auto rawText = RemoveWhitespaces(source_.substr(textBegin, it_ - textBegin));
			textBegin = it_ + 1;
			if(!rawText.empty())
			{
				auto text = Make<Text>(rawText);
				scope_->Add(text);
				// std::cout << rawText << std::endl;
			}

			++it_;

			auto scope = Make<Scope>(scope_);

			scope->opening =
				value == '(' ? Scope::BraceType::Round :
				value == '{' ? Scope::BraceType::Figure :
				value == '[' ? Scope::BraceType::Square :
				throw Exception("Invalid brace type");

			ParseScope(source_, it_, scope);

			textBegin = it_;

			scope_->Add(scope);

			continue;
		}
		else if(IsClosingBrace(value))
		{
			scope_->closing =
				value == ')' ? Scope::BraceType::Round :
				value == '}' ? Scope::BraceType::Figure :
				value == ']' ? Scope::BraceType::Square :
				throw Exception("Invalid brace type");

			auto rawText = RemoveWhitespaces(source_.substr(textBegin, it_ - textBegin));
			textBegin = it_ + 1;
			if(!rawText.empty())
			{
				auto text = Make<Text>(rawText);
				scope_->Add(text);
				// std::cout << rawText << std::endl;
			}

			++it_;

			return;
		}

		++it_;
	}

	auto rawText = RemoveWhitespaces(source_.substr(textBegin, it_ - textBegin));
	textBegin = it_ + 1;
	if(!rawText.empty())
	{
		auto text = Make<Text>(rawText);
		scope_->Add(text);
		// std::cout << rawText << std::endl;
	}
}

inline Nu::Reference<Nu::NamesDeclarationStage::Scope> Nu::NamesDeclarationStage::Parser::Parse(const Source& source_)
{
	auto mainScope = Make<Scope>(nullptr);
	mainScope->opening = Scope::BraceType::Figure;
	mainScope->closing = Scope::BraceType::Figure;

	int it = 0;

	ParseScope(source_, it, mainScope);

	return mainScope;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















