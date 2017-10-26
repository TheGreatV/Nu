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
		class Symbol;
		class Identifier;
		class Declaration;
		class Unit;
		class TokensContainer;
		class IdentifiersContainer;
		class Group;
		class Scope;
		class Space;
		class Lexer;

		class Token:
			public Entity
		{
		public:
			inline Token(const Reference<Token>& this_):
				Entity(this_)
			{
			}
			virtual ~Token() override = default;
		};
		class Text:
			public Token
		{
		public:
			using Value = String;
		protected:
			Value value;
		public:
			inline Text(const Reference<Text>& this_, const Value& value_):
				Token(this_),
				value(value_)
			{
			}
			virtual ~Text() override = default;
		public:
			inline Value GetValue() const
			{
				return value;
			}
			inline void SetValue(const Value & value_)
			{
				value = value_;
			}
		};
		class Symbol:
			public Token
		{
		public:
			using Type = NamesDeclarationStage::SpecialSymbol::Type;
		protected:
			const Type type;
		public:
			inline Symbol(const Reference<Symbol>& this_, const Type& type_):
				Token(this_),
				type(type_)
			{
			}
			virtual ~Symbol() override = default;
		public:
			inline Type GetType() const
			{
				return type;
			}
		};
		class Identifier:
			public Token
		{
		public:
			using Name = String;
			using Value = Reference<Unit>;
		protected:
			const Name name;
			Value value = nullptr;
		public:
			inline Identifier(const Reference<Identifier>& this_, const Name& name_):
				Token(this_),
				name(name_)
			{
			}
			virtual ~Identifier() override = default;
		public:
			inline Name GetName() const
			{
				return name;
			}
			inline Value GetValue() const
			{
				return value;
			}
			inline void SetValue(const Value& value_)
			{
				value = value_;
			}
		};
		class Declaration:
			public Token
		{
		protected:
			const Reference<Identifier> identifier;
		public:
			inline Declaration(const Reference<Declaration>& this_, const Reference<Identifier>& identifier_):
				Token(this_),
				identifier(identifier_)
			{
			}
			virtual ~Declaration() override = default;
		public:
			inline Reference<Identifier> GetIdentifier() const
			{
				return identifier;
			}
		};
		class Unit:
			public Entity
		{
		public:
			inline Unit(const Reference<Unit>& this_):
				Entity(this_)
			{
			}
			virtual ~Unit() override = default;
		};
		class Keyword:
			public Unit
		{
		public:
			enum class Type
			{
				AnyValue,

				Space,
			};
		protected:
			const Type type;
		public:
			inline Keyword(const Reference<Keyword>& this_, const Type& type_):
				Unit(this_),
				type(type_)
			{
			}
			virtual ~Keyword() override = default;
		public:
			inline Type GetType() const
			{
				return type;
			}
		};
		class TokensContainer
		{
		public:
			using Tokens = List<Reference<Token>>;
			using Iterator = Tokens::const_iterator;
		protected:
			Tokens tokens;
		public:
			inline Tokens& GetTokens()
			{
				return tokens;
			}
			inline void RemoveEmptyText()
			{
				auto copy = Tokens();

				for(auto &token : tokens)
				{
					if(auto source = UpCast<Text>(token))
					{
						if(source->GetValue().empty())
						{
							continue;
						}
					}

					copy.push_back(token);
				}

				if(copy.size() != tokens.size())
				{
					tokens = copy;
				}
			}
		};
		class IdentifiersContainer
		{
		public:
			class IdentifierAccessor
			{
			protected:
				Reference<Identifier> identifier;
				Size nestingLevel;
			public:
				inline IdentifierAccessor(const Reference<Identifier>& identifier_, const Size& nestingLevel_):
					identifier(identifier_),
					nestingLevel(nestingLevel_)
				{
				}
				inline IdentifierAccessor(const IdentifierAccessor&) = default;
			public:
				inline IdentifierAccessor& operator = (const IdentifierAccessor&) = default;
			public:
				inline Reference<Identifier> GetIdentifier() const
				{
					return identifier;
				}
				inline Size GetNestingLevel() const
				{
					return nestingLevel;
				}
			};
		public:
			using Identifiers = Vector<Reference<Identifier>>;
		protected:
			const Reference<IdentifiersContainer> parent;
			Identifiers identifiers;
		public:
			inline IdentifiersContainer(const Reference<IdentifiersContainer>& parent_):
				parent(parent_)
			{
			}
		public:
			inline void Add(const Reference<Identifier>& identifier_);
			inline virtual Vector<IdentifierAccessor> GetIdentifiers() const;
		};
		class Group:
			public Token,
			public TokensContainer
		{
		public:
			using BraceType = NamesDeclarationStage::Scope::BraceType;
		public:
			BraceType opening, closing;
		public:
			inline Group(const Reference<Group>& this_):
				Token(this_),
				TokensContainer()
			{
			}
			virtual ~Group() override = default;
		};
		class Scope:
			public Group
		{
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& parent_):
				Group(this_)
			{
			}
			virtual ~Scope() override = default;
		};
		class Space:
			public Scope
		{
		public:
			inline Space(const Reference<Space>& this_, const Reference<Scope>& parent_):
				Scope(this_, parent_)
			{
			}
			virtual ~Space() override = default;
		public:

		};
		class Lexer:
			public Entity
		{
		protected:
			class RetryException
			{
			};
			class SkipException
			{
			};
		protected:
			class MarkersPreparator;
			class RootMarkersPreparator;
		public:
			inline Lexer(const Reference<Lexer>& this_):
				Entity(this_)
			{
			}
			virtual ~Lexer() override = default;
		protected:
			inline Reference<Token> ExtractToken(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Identifier> ExtractIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Identifier> ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			// inline Reference<Keyword> ExtractKeyword(const Keyword::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Unit> ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Declaration> ExtractDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Declaration> ParseDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline void PerformSpace(const Reference<Space>& space_);
			inline void ParseSpaceBody(const Reference<Space>& space_);
			inline bool ParseSpaceContent(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Space>& space_);
		public:
			inline Reference<Space> Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_);
		};
#pragma region Lexer::MarkersPreparator
		class Lexer::MarkersPreparator:
			public NamesDeclarationStage::Marker::Performer
		{
		protected:
			const Reference<Lexer> lexer;
			const Reference<Group> group;
		public:
			inline MarkersPreparator(const Reference<MarkersPreparator>& this_, const Reference<Lexer>& lexer_, const Reference<Group>& group_):
				Performer(this_),
				lexer(lexer_),
				group(group_)
			{
			}
			virtual ~MarkersPreparator() = default;
		public:
			virtual void Perform(const Reference<NamesDeclarationStage::Text>& marker_) override
			{
				auto text = Make<Text>(marker_->GetValue());
				group->GetTokens().push_back(text);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Declaration>& marker_) override
			{
				auto name = marker_->GetIdentifier()->GetValue();
				auto identifier = Make<Identifier>(name);

				auto declaration = Make<Declaration>(identifier);

				group->GetTokens().push_back(declaration);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::SpecialSymbol>& marker_) override
			{
				auto symbol = Make<Symbol>(marker_->GetType());

				group->GetTokens().push_back(symbol);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Scope>& marker_) override
			{
				auto newGroup = Make<Group>();
				group->GetTokens().push_back(newGroup);

				newGroup->opening = marker_->opening;
				newGroup->closing = marker_->closing;

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, newGroup);
					preparator->Performer::Perform(marker);
				}
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Root>& marker_) override
			{
				throw Exception();
			}
		};
#pragma endregion
#pragma region Lexer::RootMarkersPreparator
		class Lexer::RootMarkersPreparator:
			public NamesDeclarationStage::Marker::Performer
		{
		protected:
			const Reference<Lexer> lexer;
			const Reference<Scope> scope;
		public:
			inline RootMarkersPreparator(const Reference<RootMarkersPreparator>& this_, const Reference<Lexer>& lexer_, const Reference<Scope>& scope_):
				Performer(this_),
				lexer(lexer_),
				scope(scope_)
			{
			}
			virtual ~RootMarkersPreparator() = default;
		public:
			virtual void Perform(const Reference<NamesDeclarationStage::Text>& marker_) override
			{
				throw Exception();
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Declaration>& marker_) override
			{
				throw Exception();
			}
			virtual void Perform(const Reference<NamesDeclarationStage::SpecialSymbol>& marker_) override
			{
				throw Exception();
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Scope>& marker_) override
			{
				throw Exception();
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Root>& marker_) override
			{
				auto space = Make<Space>(scope);
				scope->GetTokens().push_back(space);

				space->opening = marker_->opening;
				space->closing = marker_->closing;

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, space);
					preparator->Performer::Perform(marker);
				}
			}
		};
#pragma endregion
	}
}


#pragma region Nu

#pragma region Lexing

#pragma region IdentifiersContainer

inline void Nu::Lexing::IdentifiersContainer::Add(const Reference<Identifier>& identifier_)
{
	identifiers.push_back(identifier_);
}
inline Nu::Vector<Nu::Lexing::IdentifiersContainer::IdentifierAccessor> Nu::Lexing::IdentifiersContainer::GetIdentifiers() const
{
	Vector<IdentifierAccessor> owned;
	Map<Reference<Identifier>, Size> counter;

	for(auto i = identifiers.rbegin(); i != identifiers.rend(); ++i) // reverse bypass need to last identifier gets least nesting level
	{
		auto &identifier = *i;

		Size nestingLevel = (counter.find(identifier) != counter.end())
			? counter[identifier]++
			: 0;
		owned.push_back(IdentifierAccessor(identifier, nestingLevel));
	}

	if(parent)
	{
		auto parentIdentifiers = parent->GetIdentifiers();

		for(auto &accessor : parentIdentifiers)
		{
			auto &identifier = accessor.GetIdentifier();

			Size nestingLevel = (counter.find(identifier) != counter.end())
				? counter[identifier] + accessor.GetNestingLevel()
				: accessor.GetNestingLevel();
			owned.push_back(IdentifierAccessor(identifier, nestingLevel));
		}
	}

	return owned;
}

#pragma endregion

#pragma region Lexer

inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ExtractToken(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto token = *it_;
		++it_;

		return token;
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ExtractIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ExtractToken(tokens_, it_, scope_))
	{
		if(auto identifier = UpCast<Identifier>(token))
		{
			return identifier;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto identifier = ExtractIdentifier(tokens_, it_, scope_))
	{
		return identifier;
	}

	it_ = o;
	if(auto declaration = ParseDeclaration(tokens_, it_, scope_))
	{
		auto identifier = declaration->GetIdentifier();
		return identifier;
	}

	// TODO: extract name

	it_ = o;
	return nullptr;
}

/*inline Nu::Reference<Nu::Lexing::Keyword> Nu::Lexing::Lexer::ExtractKeyword(const Keyword::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto identifier = ParseIdentifier(tokens_, it_, scope_))
	{
		if(auto value = identifier->GetValue())
		{
			if(auto keyword = UpCast<Keyword>(value))
			{
				if(type_ == Keyword::Type::AnyValue || keyword->GetType() == type_)
				{
					return keyword;
				}
			}
		}
		else
		{
			throw SkipException();
		}
	}

	it_ = o;
	return nullptr;
}*/

inline Nu::Reference<Nu::Lexing::Unit> Nu::Lexing::Lexer::ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	
	if(auto identifier = ParseIdentifier(tokens_, it_, scope_))
	{
		auto unit = identifier->GetValue();
		return unit;
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Declaration> Nu::Lexing::Lexer::ExtractDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ExtractToken(tokens_, it_, scope_))
	{
		if(auto declaration = UpCast<Declaration>(token))
		{
			return declaration;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Declaration> Nu::Lexing::Lexer::ParseDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto declaration = ExtractDeclaration(tokens_, it_, scope_))
	{
		auto identifier = declaration->GetIdentifier();

		if(auto unit = ParseUnit(tokens_, it_, scope_))
		{
			if(auto value = identifier->GetValue())
			{
				if(value == unit)
				{
					return declaration;
				}
				else
				{
					throw Exception();
				}
			}
			else
			{
				// TODO: add identifier to scope
				identifier->SetValue(unit);
				return declaration;
			}
		}
		else
		{
			throw Exception();
		}
	}

	it_ = o;
	return nullptr;
}

inline void Nu::Lexing::Lexer::PerformSpace(const Reference<Space>& space_)
{
	ParseSpaceBody(space_);
}
inline void Nu::Lexing::Lexer::ParseSpaceBody(const Reference<Space>& space_)
{
	space_->RemoveEmptyText();

	auto &tokens = space_->GetTokens();
	auto it = tokens.begin();

	while(it != tokens.end()) // iterate through collection utill end
	{
		try
		{
			if(!ParseSpaceContent(tokens, it, space_))
			{
				if(it != tokens.end())
				{
					throw Exception();
				}
			}
		}
		catch(SkipException)
		{
			++it;
		}
	}
}
inline bool Nu::Lexing::Lexer::ParseSpaceContent(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Space>& space_)
{
	auto o = it_;
	if(auto declaration = ParseDeclaration(tokens_, it_, space_))
	{
		return true;
	}

	/*it_ = o;
	if(auto unnamed = ParseUnnamed(tokens_, it_, space_))
	{
		return true;
	}

	it_ = o;
	if(auto symbol = ParseSymbol(Symbol::Type::Semicolon, tokens_, it_, space_))
	{
		return true;
	}*/

	it_ = o;
	return false;
}


inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_)
{
	auto spaceOfKeywords = Make<Space>(nullptr);

	spaceOfKeywords->opening = Lexing::Group::BraceType::Figure;
	spaceOfKeywords->closing = Lexing::Group::BraceType::Figure;

	auto preparator = Make<RootMarkersPreparator>(GetThis<Lexer>(), spaceOfKeywords);
	preparator->Performer::Perform(Cast<NamesDeclarationStage::Marker>(namingScope_));

	while(true)
	{
		try
		{
			PerformSpace(spaceOfKeywords);
			break;
		}
		catch(RetryException)
		{
		}
	}

	return spaceOfKeywords;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















