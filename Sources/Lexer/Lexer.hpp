#pragma once

#pragma region Include

#include <regex>

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing
	{
		/*
		class Token;
		class Source;
		class Identifier;
		class Declaration;

		class Unit;
		class Scope;
		class Space;

		class Lexer;*/
		/*class Token:
			public Entity
		{
		public:
			inline Token(const Reference<Token>& this_):
				Entity(this_)
			{
			}
			virtual ~Token() override = default;
		};*/
		/*class Source:
			public Token
		{
		public:
			using Value = String;
		protected:
			Value value;
		public:
			inline Source(const Reference<Source>& this_, const Value& value_):
				Token(this_),
				value(value_)
			{
			}
			virtual ~Source() override = default;
		public:
			inline Value GetValue() const
			{
				return value;
			}
			inline void SetValue(const Value & value_)
			{
				value = value_;
			}
		};*/
		/*class Identifier:
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
		};*/
		/*class Declaration:
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
		};*/
		/*class TokensContainer
		{
		public:
			using Tokens = List<Reference<Token>>;
		protected:
			Tokens tokens;
		public:
			inline Tokens& GetTokens()
			{
				return tokens;
			}
		public:
			inline void RemoveEmptySources()
			{
				auto copy = Tokens();

				for(auto &token : tokens)
				{
					if(auto source = UpCast<Source>(token))
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
		};*/
		/*class IdentifiersContainer
		{
		public:
			class IdentifierAccessor
			{
			protected:
				const Reference<Identifier> identifier;
				const Size nestingLevel;
			public:
				inline IdentifierAccessor(const Reference<Identifier>& identifier_, const Size& nestingLevel_):
					identifier(identifier_),
					nestingLevel(nestingLevel_)
				{
				}
				inline IdentifierAccessor(const IdentifierAccessor&) = default;
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
			inline Vector<IdentifierAccessor> GetIdentifiers() const;
		};*/
		/*class ScopeDependent:
			public Entity
		{
		protected:
			Reference<Scope> scope = nullptr;
		public:
			inline ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_);
		public:
			inline Reference<Scope> GetScope() const;
			inline void SetScope(const Reference<Scope>& scope_);
		};*/
		/*class Unit:
			public Entity
		{
		public:
			inline Unit(const Reference<Unit>& this_):
				Entity(this_)
			{
			}
			virtual ~Unit() override = default;
		};*/
		/*class Keyword:
			public Unit
		{
		public:
			enum class Type
			{
				None,

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
		};*/
		/*class Scope:
			public Token,
			public ScopeDependent,
			public TokensContainer,
			public IdentifiersContainer
		{
		protected:
			List<Reference<ScopeDependent>> dependencies;
			friend ScopeDependent;
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_):
				Token(Cast<Token>(this_)),
				ScopeDependent(this_, scope_),
				TokensContainer(),
				IdentifiersContainer(scope_)
			{
			}
			virtual ~Scope() override = default;
		public:
			template<class T>
			inline void ChangeTo(const Reference<T>& new_)
			{
				auto copy = dependencies;
				for(auto &dependency : copy)
				{
					dependency->SetScope(new_);
				}
				new_->tokens = tokens;
			}
		};*/
		/*class Space:
			public Scope,
			public Unit
		{
		public:
			inline Space(const Reference<Space>& this_, const Reference<Scope>& scope_):
				Scope(this_, scope_),
				Unit(this_)
			{
			}
			virtual ~Space() override = default;
		};*/
		/*class Lexer:
			public Entity
		{
		protected:
			class Retry
			{
			};
			class MarkersPreparator;
			class SymbolsSet
			{
			protected:
				const String set;
				const Size nestingLevel;
				const Size size;
			public:
				inline SymbolsSet(const String& set_, const Size& nestingLevel_, const Size& size_):
					set(set_),
					nestingLevel(nestingLevel_),
					size(size_)
				{
				}
			public:
				inline String GetSet() const
				{
					return set;
				}
				inline Size GetNestingLevel() const
				{
					return nestingLevel;
				}
				inline Size GetSize() const
				{
					return size;
				}
			};
		public:
			inline Lexer(const Reference<Lexer>& this_);
			virtual ~Lexer() override = default;
		protected:
			inline Reference<Token> ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Token> ExtractToken(const Reference<Source>& source_, const Reference<Scope>& scope_);
			inline SymbolsSet ExtractSymbolsSet(const Source::Value& value_);

			inline Reference<Keyword> ParseKeyword(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Identifier> ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Declaration> ParseIdentifierDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Unit> ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Scope> ParseScope(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline void ParseScopeBody(const Reference<Scope>& scope_);
			inline bool ParseScopeBodyContent(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Space> ParseSpace(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Space> ParseSpaceDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline void ParseSpaceBody(const Reference<Space>& space_);
		public:
			inline Reference<Space> Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_);
		};*/
/*#pragma region MarkersPreparator
		class Lexer::MarkersPreparator:
			public NamesDeclarationStage::Marker::Performer
		{
		protected:
			const Reference<Lexer> lexer;
			const Reference<Scope> scope;
		public:
			inline MarkersPreparator(const Reference<MarkersPreparator>& this_, const Reference<Lexer>& lexer_, const Reference<Scope>& scope_):
				Performer(this_),
				lexer(lexer_),
				scope(scope_)
			{
			}
			virtual ~MarkersPreparator() = default;
		public:
			virtual void Perform(const Reference<NamesDeclarationStage::Text>& marker_) override
			{
				auto source = Make<Source>(marker_->GetValue());
				scope->GetTokens().push_back(source);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Declaration>& marker_) override
			{
				auto name = marker_->GetIdentifier()->GetValue();
				auto identifier = Make<Identifier>(name);

				scope->Add(identifier);

				auto declaration = Make<Declaration>(identifier);

				scope->GetTokens().push_back(declaration);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Scope>& marker_) override
			{
				auto newScope = Make<Scope>(scope);
				scope->GetTokens().push_back(newScope);

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, newScope);
					preparator->Performer::Perform(marker);
				}
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Root>& marker_) override
			{
				auto space = Make<Space>(scope);
				scope->GetTokens().push_back(space);

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, space);
					preparator->Performer::Perform(marker);
				}
			}
		};
#pragma endregion
		*/

		class Token;
		class Source;
		class Symbol;
		class Identifier;
		class TokensContainer;
		class Unit;
		// class Undefined;
		class ScopeDependent;
		class Keyword;
		class Declaration;
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
		class Source:
			public Token
		{
		public:
			using Value = String;
		protected:
			Value value;
		public:
			inline Source(const Reference<Source>& this_, const Value& value_):
				Token(this_),
				value(value_)
			{
			}
			virtual ~Source() override = default;
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
			inline void RemoveEmptySources()
			{
				auto copy = Tokens();

				for(auto &token : tokens)
				{
					if(auto source = UpCast<Source>(token))
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
			inline Vector<IdentifierAccessor> GetIdentifiers() const;
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
		/*class Undefined:
			public Unit
		{
		public:
			inline Undefined(const Reference<Undefined>& this_):
				Unit(this_)
			{
			}
			virtual ~Undefined() override = default;
		};*/
		class ScopeDependent:
			public Entity
		{
		protected:
			Reference<Scope> scope = nullptr;
		public:
			inline ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_);
			virtual ~ScopeDependent() override = default;
		public:
			inline Reference<Scope> GetScope() const;
			inline void SetScope(const Reference<Scope>& scope_);
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
		class Scope:
			public Token,
			public ScopeDependent,
			public TokensContainer,
			public IdentifiersContainer
		{
		protected:
			List<Reference<ScopeDependent>> dependencies;
			friend ScopeDependent;
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_):
				Token(Cast<Token>(this_)),
				ScopeDependent(this_, scope_),
				TokensContainer(),
				IdentifiersContainer(scope_)
			{
			}
			virtual ~Scope() override = default;
		public:
			template<class T>
			inline void ChangeTo(const Reference<T>& new_)
			{
				auto copy = dependencies;
				for(auto &dependency : copy)
				{
					dependency->SetScope(new_);
				}
				new_->tokens = tokens;
			}
		};
		class Unnamed:
			public Unit
		{
		public:
			inline Unnamed(const Reference<Unnamed>& this_):
				Unit(this_)
			{
			}
			virtual ~Unnamed() override = default;
		};
		class Space:
			public Scope,
			public Unnamed
		{
		public:
			inline Space(const Reference<Space>& this_, const Reference<Scope>& scope_):
				Scope(this_, scope_),
				Unnamed(this_)
			{
			}
			virtual ~Space() override = default;
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
			class SymbolsSet;
			class NameBase;
		protected:
			bool isSkips = false;
		public:
			inline Lexer(const Reference<Lexer>& this_):
				Entity(this_)
			{
			}
			virtual ~Lexer() override = default;
		protected:
			inline Reference<Symbol> ParseSymbol(const Symbol::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			// inline Reference<Token> ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			// inline Reference<Token> ExtractToken(const Reference<Source>& source_, const Reference<Scope>& scope_);
			// inline SymbolsSet ExtractSymbolsSet(const Source::Value& value_);

			// inline Reference<Identifier> ParseNameBaseIdentifier(const Size& nestingLevel_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			// inline Reference<NameBase> ParseNameBase(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Identifier> ParseName(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Token> ParseToken(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Keyword> ParseKeyword(const Keyword::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Unit> ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Identifier> ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Declaration> ParseDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Scope> ParseScope(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			// inline void ParseScopeBody(const Reference<Scope>& scope_);
			// inline bool ParseScopeContent(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Unnamed> ParseUnnamed(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Space> ParseSpace(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Space> ParseSpaceDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_);
			inline void ParseSpaceBody(const Reference<Space>& space_);
			inline bool ParseSpaceContent(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Space>& space_);
		public:
			inline Reference<Space> Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_);
		};
#pragma region Lexer::SymbolsSet
		class Lexer::SymbolsSet
		{
		protected:
			const String set;
			const Size nestingLevel;
			const Size size;
		public:
			inline SymbolsSet(const String& set_, const Size& nestingLevel_, const Size& size_):
				set(set_),
				nestingLevel(nestingLevel_),
				size(size_)
			{
			}
		public:
			inline String GetSet() const
			{
				return set;
			}
			inline Size GetNestingLevel() const
			{
				return nestingLevel;
			}
			inline Size GetSize() const
			{
				return size;
			}
		};
#pragma endregion
#pragma region Lexer::MarkersPreparator
		class Lexer::MarkersPreparator:
			public NamesDeclarationStage::Marker::Performer
		{
		protected:
			const Reference<Lexer> lexer;
			const Reference<Scope> scope;
		public:
			inline MarkersPreparator(const Reference<MarkersPreparator>& this_, const Reference<Lexer>& lexer_, const Reference<Scope>& scope_):
				Performer(this_),
				lexer(lexer_),
				scope(scope_)
			{
			}
			virtual ~MarkersPreparator() = default;
		public:
			virtual void Perform(const Reference<NamesDeclarationStage::Text>& marker_) override
			{
				auto source = Make<Source>(marker_->GetValue());
				scope->GetTokens().push_back(source);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Declaration>& marker_) override
			{
				auto name = marker_->GetIdentifier()->GetValue();
				auto identifier = Make<Identifier>(name);

				scope->Add(identifier);

				auto declaration = Make<Declaration>(identifier);

				scope->GetTokens().push_back(declaration);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::SpecialSymbol>& marker_) override
			{
				auto symbol = Make<Symbol>(marker_->GetType());

				scope->GetTokens().push_back(symbol);
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Scope>& marker_) override
			{
				auto newScope = Make<Scope>(scope);
				scope->GetTokens().push_back(newScope);

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, newScope);
					preparator->Performer::Perform(marker);
				}
			}
			virtual void Perform(const Reference<NamesDeclarationStage::Root>& marker_) override
			{
				auto space = Make<Space>(scope);
				scope->GetTokens().push_back(space);

				for(auto &marker : marker_->GetMarkers())
				{
					auto preparator = Make<MarkersPreparator>(lexer, space);
					preparator->Performer::Perform(marker);
				}
			}
		};
#pragma endregion
#pragma region Lexer::NameBase
		class Lexer::NameBase
		{
		public:
			Vector<Reference<Symbol>> nestingSymbols;
			Reference<Identifier> name;
		};
#pragma endregion
	}
}


#pragma region Nu

#pragma region Lexing

#pragma region ScopeDependent

inline Nu::Lexing::ScopeDependent::ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_):
	Entity(this_)
{
	SetScope(scope_);
}
inline Nu::Reference<Nu::Lexing::Scope> Nu::Lexing::ScopeDependent::GetScope() const
{
	return scope;
}
inline void Nu::Lexing::ScopeDependent::SetScope(const Reference<Scope>& scope_)
{
	auto shared = GetThis<ScopeDependent>();

	if(scope)
	{
		scope->dependencies.remove(shared);
	}

	scope = scope_;

	if(scope)
	{
		scope->dependencies.push_back(shared);
	}
}

#pragma endregion

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

/*
#pragma region Lexer

inline Nu::Lexing::Lexer::Lexer(const Reference<Lexer>& this_):
	Entity(this_)
{
}

inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto source = UpCast<Source>(token))
		{
			auto token = ExtractToken(source, scope_);
			return token;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ExtractToken(const Reference<Source>& source_, const Reference<Scope>& scope_)
{
	auto symbolsSet = ExtractSymbolsSet(source_->GetValue());
	
	if(symbolsSet.GetSize() > 0)
	{
		auto identifiers = scope_->GetIdentifiers();

		for(auto &accessor : identifiers)
		{
			auto &identifier = accessor.GetIdentifier();
			auto nestingLevel = accessor.GetNestingLevel();

			if(nestingLevel == symbolsSet.GetNestingLevel())
			{
				if([&]()
				{
					if(identifier->GetName().size() <= symbolsSet.GetSet().size())
					{
						for(Size i = 0; i < identifier->GetName().size(); ++i)
						{
							if(identifier->GetName()[i] != symbolsSet.GetSet()[i])
							{
								return false;
							}
						}

						return true;
					}
					else
					{
						return false;
					}
				}())
				{
					auto size = symbolsSet.GetSize() - (symbolsSet.GetSet().size() - identifier->GetName().size());

					auto value = source_->GetValue().substr(size, source_->GetValue().size() - size);
					source_->SetValue(
						std::regex_replace(
							std::regex_replace(value, std::regex("^\\s+"), ""),
							std::regex("\\s+$"), ""
						)
					);

					return identifier;
				}
			}
		}

		throw Exception();
	}

	throw Exception();
}
inline Nu::Lexing::Lexer::SymbolsSet Nu::Lexing::Lexer::ExtractSymbolsSet(const Source::Value& value_)
{
	Size i = 0;

	auto skipWhitespaces = [&]()
	{
		while(i < value_.size() && NamesDeclarationStage::IsWhitespace(value_[i]))
		{
			++i;
		}
	};
	auto skipSymbols = [&]()
	{
		while(i < value_.size() && NamesDeclarationStage::IsSymbol(value_[i]))
		{
			++i;
		}
	};
	auto countDots = [&]()
	{
		auto j = i;
		while(i < value_.size() && value_[i] == '.')
		{
			++i;
		}
		return i - j;
	};
	auto countNestingLevel = [&]()
	{
		Size nestingLevel = 0;
		while(true)
		{
			skipWhitespaces();
			auto dotsCount = countDots();
			if(dotsCount > 0)
			{
				nestingLevel += dotsCount;
			}
			else
			{
				break;
			}
		}
		return nestingLevel;
	};

	auto nestingLevel = countNestingLevel();
	skipWhitespaces();
	auto j = i;
	skipSymbols();
	if(i > j)
	{
		auto set = value_.substr(j, i - j);

		return SymbolsSet(set, nestingLevel, i);
	}

	return SymbolsSet("", 0, 0);
}

inline Nu::Reference<Nu::Lexing::Keyword> Nu::Lexing::Lexer::ParseKeyword(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto identifier = ParseIdentifier(tokens_, it_, scope_))
	{
		if(auto value = identifier->GetValue())
		{
			if(auto keyword = UpCast<Keyword>(value))
			{
				return keyword;
			}
		}
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto identifier = UpCast<Identifier>(token))
		{
			return identifier;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Declaration> Nu::Lexing::Lexer::ParseIdentifierDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto declaration = UpCast<Declaration>(token))
		{
			auto identifier = declaration->GetIdentifier();

			if(auto unit = ParseUnit(tokens_, it_, scope_))
			{
				identifier->SetValue(unit);
				// TODO: parse value

				return declaration;
			}
			else
			{
				throw Exception();
			}
		}
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Unit> Nu::Lexing::Lexer::ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ParseSource(tokens_, it_, scope_))
	{
		tokens_.insert(o, token);
		throw Retry();
	}
	else if(auto space = ParseSpaceDeclaration(tokens_, it_, scope_))
	{
		auto i = tokens_.erase(o, it_);
		tokens_.insert(i, space);
		throw Retry();
	}
	else if(auto space = ParseSpace(tokens_, it_, scope_))
	{
		return space;
	}
	else if(auto identifier = ParseIdentifier(tokens_, it_, scope_))
	{
		auto value = identifier->GetValue();
		return value;
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Scope> Nu::Lexing::Lexer::ParseScope(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto scope = UpCast<Scope>(token))
		{
			ParseScopeBody(scope);

			return scope;
		}
	}

	it_ = o;
	return false;
}
inline void Nu::Lexing::Lexer::ParseScopeBody(const Reference<Scope>& scope_)
{
	scope_->RemoveEmptySources();

	auto &tokens = scope_->GetTokens();
	auto it = tokens.begin();

	while(it != tokens.end())
	{
		if(!ParseScopeBodyContent(tokens, it, scope_))
		{
			throw Exception();
		}
	}
}
inline bool Nu::Lexing::Lexer::ParseScopeBodyContent(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	// TODO
	if(auto token = ParseSource(tokens_, it_, scope_))
	{
		tokens_.insert(o, token);
		throw Retry();
	}
	else if(auto space = ParseSpaceDeclaration(tokens_, it_, scope_))
	{
		auto i = tokens_.erase(o, it_);
		tokens_.insert(i, space);
		throw Retry();
	}
	else if(auto space = ParseSpace(tokens_, it_, scope_))
	{
		return true;
	}
	else if(auto scope = ParseScope(tokens_, it_, scope_))
	{
		return true;
	}
	else if(auto declaration = ParseIdentifierDeclaration(tokens_, it_, scope_))
	{
		return true;
	}

	it_ = o;
	return false;
}

inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::ParseSpace(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto space = UpCast<Space>(token))
		{
			ParseSpaceBody(space);

			return space;
		}
	}

	it_ = o;
	return false;
}
inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::ParseSpaceDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto keyword = ParseKeyword(tokens_, it_, scope_))
	{
		if(keyword->GetType() == Keyword::Type::Space)
		{
			if(auto scope = ParseScope(tokens_, it_, scope_))
			{
				auto space = Make<Space>(scope_);
				scope->ChangeTo(space);
				return space;
			}
			else
			{
				throw Exception();
			}
		}
	}
	// if(it_ != tokens_.end())
	// {
	// 	auto &token = *it_;
	// 	++it_;
	// 
	// 	if(auto identifier = UpCast<Identifier>(token))
	// 	{
	// 		auto value = identifier->GetValue();
	// 		if(value)
	// 		{
	// 			if(auto keyword = UpCast<Keyword>(value))
	// 			{
	// 				if(keyword->GetType() == Keyword::Type::Space)
	// 				{
	// 					if(it_ != tokens_.end())
	// 					{
	// 						auto &token = *it_;
	// 						++it_;
	// 
	// 						if(auto scope = UpCast<Scope>(token))
	// 						{
	// 							auto space = Make<Space>(scope_);
	// 							scope->ChangeTo(space);
	// 							return space;
	// 						}
	// 						else
	// 						{
	// 							throw Exception();
	// 						}
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	it_ = o;
	return false;
}
inline void Nu::Lexing::Lexer::ParseSpaceBody(const Reference<Space>& space_)
{
	ParseScopeBody(space_);
}

inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_)
{
	auto keywordsSpace = Make<Space>(nullptr);

	auto spaceIdentifier = Make<Identifier>("space");
	{
		auto spaceKeyword = Make<Keyword>(Keyword::Type::Space);
		spaceIdentifier->SetValue(spaceKeyword);

		keywordsSpace->Add(spaceIdentifier);
	}

	auto preparator = Make<MarkersPreparator>(GetThis<Lexer>(), Cast<Space>(keywordsSpace));
	preparator->Performer::Perform(Cast<NamesDeclarationStage::Marker>(namingScope_));

	while(true)
	{
		try
		{
			ParseSpaceBody(keywordsSpace);
			break;
		}
		catch(Retry)
		{
		}
	}

	return Move(keywordsSpace);
}

#pragma endregion
*/

#pragma region Lexer

inline Nu::Reference<Nu::Lexing::Symbol> Nu::Lexing::Lexer::ParseSymbol(const Symbol::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto symbol = UpCast<Symbol>(token))
		{
			if(type_ == Symbol::Type::AnyValue || symbol->GetType() == type_)
			{
				return symbol;
			}
		}
	}

	it_ = o;
	return nullptr;
}

/*inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto source = UpCast<Source>(token))
		{
			auto token = ExtractToken(source, scope_);
			return token;
		}
	}

	it_ = o;
	return nullptr;
}*/
/*inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ExtractToken(const Reference<Source>& source_, const Reference<Scope>& scope_)
{
	auto symbolsSet = ExtractSymbolsSet(source_->GetValue());
	
	if(symbolsSet.GetSize() > 0)
	{
		auto identifiers = scope_->GetIdentifiers();

		for(auto &accessor : identifiers)
		{
			auto &identifier = accessor.GetIdentifier();
			auto nestingLevel = accessor.GetNestingLevel();

			if(nestingLevel == symbolsSet.GetNestingLevel())
			{
				if([&]()
				{
					if(identifier->GetName().size() <= symbolsSet.GetSet().size())
					{
						for(Size i = 0; i < identifier->GetName().size(); ++i)
						{
							if(identifier->GetName()[i] != symbolsSet.GetSet()[i])
							{
								return false;
							}
						}

						return true;
					}
					else
					{
						return false;
					}
				}())
				{
					auto size = symbolsSet.GetSize() - (symbolsSet.GetSet().size() - identifier->GetName().size());

					auto value = source_->GetValue().substr(size, source_->GetValue().size() - size);
					source_->SetValue(
						std::regex_replace(
							std::regex_replace(value, std::regex("^\\s+"), ""),
							std::regex("\\s+$"), ""
						)
					);

					return identifier;
				}
			}
		}

		throw Exception();
	}

	throw Exception();
}*/
/*inline Nu::Lexing::Lexer::SymbolsSet Nu::Lexing::Lexer::ExtractSymbolsSet(const Source::Value& value_)
{
	Size i = 0;

	auto skipWhitespaces = [&]()
	{
		while(i < value_.size() && NamesDeclarationStage::IsWhitespace(value_[i]))
		{
			++i;
		}
	};
	auto skipSymbols = [&]()
	{
		while(i < value_.size() && NamesDeclarationStage::IsSymbol(value_[i]))
		{
			++i;
		}
	};
	auto countDots = [&]()
	{
		auto j = i;
		while(i < value_.size() && value_[i] == '.')
		{
			++i;
		}
		return i - j;
	};
	auto countNestingLevel = [&]()
	{
		Size nestingLevel = 0;
		while(true)
		{
			skipWhitespaces();
			auto dotsCount = countDots();
			if(dotsCount > 0)
			{
				nestingLevel += dotsCount;
			}
			else
			{
				break;
			}
		}
		return nestingLevel;
	};

	auto nestingLevel = countNestingLevel();
	skipWhitespaces();
	auto j = i;
	skipSymbols();
	if(i > j)
	{
		auto set = value_.substr(j, i - j);

		return SymbolsSet(set, nestingLevel, i);
	}

	return SymbolsSet("", 0, 0);
}*/

/*inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ParseNameBaseIdentifier(const Size& nestingLevel_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto source = UpCast<Source>(token))
		{
			auto value = source->GetValue();

			auto identifierAccessors = scope_->GetIdentifiers();

			std::sort(identifierAccessors.begin(), identifierAccessors.end(), [](
				const IdentifiersContainer::IdentifierAccessor& a,
				const IdentifiersContainer::IdentifierAccessor& b
			){
				return a.GetIdentifier()->GetName().size() < b.GetIdentifier()->GetName().size();
			});
			 
			// TODO: need to iterate by length of identifier (starting from the longest)
			for(auto identifierAccessor : identifierAccessors)
			{
				auto nestingLevel = identifierAccessor.GetNestingLevel();
				auto identifier = identifierAccessor.GetIdentifier();

				if(nestingLevel == nestingLevel_)
				{
					auto name = identifier->GetName();

					if(value.find(name) == 0)
					{
						return identifier;
					}
				}
			}

			throw Exception();
		}
	}

	it_ = o;
	return nullptr;
}*/
/*inline Nu::Reference<Nu::Lexing::Lexer::NameBase> Nu::Lexing::Lexer::ParseNameBase(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	Vector<Reference<Symbol>> nestingSymbols;

	while(auto nestingSymbol = ParseSymbol(Symbol::Type::Dot, tokens_, it_, scope_))
	{
		nestingSymbols.push_back(nestingSymbol);
	}

	if(auto baseIdentifier = ParseNameBaseIdentifier(nestingSymbols.size(), tokens_, it_, scope_))
	{
		auto name = baseIdentifier->GetName();
		// TODO: cut
	}

	it_ = o;
	return nullptr;
}*/
inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ParseName(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	Vector<Reference<Symbol>> nestingSymbols;
	{
		while(auto nestingSymbol = ParseSymbol(Symbol::Type::Dot, tokens_, it_, scope_))
		{
			nestingSymbols.push_back(nestingSymbol);
		}
	}

	// replace source with identifier
	auto i = tokens_.erase(o, it_); // TODO: check

	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto source = UpCast<Source>(token))
		{
			auto value = source->GetValue();

			auto identifierAccessors = scope_->GetIdentifiers();

			// longer identifiers should be checked first
			std::sort(identifierAccessors.begin(), identifierAccessors.end(), [](
				const IdentifiersContainer::IdentifierAccessor& a,
				const IdentifiersContainer::IdentifierAccessor& b
			){
				return a.GetIdentifier()->GetName().size() > b.GetIdentifier()->GetName().size();
			});
			
			auto baseIdentifier = [&]()
			{
				// TODO: need to iterate by length of identifier (starting from the longest)
				for(auto identifierAccessor : identifierAccessors)
				{
					auto nestingLevel = identifierAccessor.GetNestingLevel();
					auto identifier = identifierAccessor.GetIdentifier();

					if(nestingLevel == nestingSymbols.size())
					{
						auto name = identifier->GetName();

						if(value.find(name) == 0)
						{
							value = value.substr(name.size());
							source->SetValue(value);
							return identifier;
						}
					}
				}

				throw Exception();
			}();

			tokens_.insert(i, baseIdentifier);

			// TODO: childs (a.x)

			throw RetryException();

			return baseIdentifier;
		}
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Token> Nu::Lexing::Lexer::ParseToken(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
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

inline Nu::Reference<Nu::Lexing::Keyword> Nu::Lexing::Lexer::ParseKeyword(const Keyword::Type& type_, TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
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
}

inline Nu::Reference<Nu::Lexing::Unit> Nu::Lexing::Lexer::ParseUnit(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto space = ParseSpace(tokens_, it_, scope_))
	{
		return space;
	}

	it_ = o;
	if(auto keyword = ParseKeyword(Keyword::Type::AnyValue, tokens_, it_, scope_))
	{
		return keyword;
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Identifier> Nu::Lexing::Lexer::ParseIdentifier(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto identifier = UpCast<Identifier>(token))
		{
			return identifier;
		}
	}

	it_ = o;
	if(auto declaration = ParseDeclaration(tokens_, it_, scope_))
	{
		auto identifier = declaration->GetIdentifier();
		return identifier;
	}

	it_ = o;
	if(auto identifier = ParseName(tokens_, it_, scope_))
	{
		return identifier;
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Declaration> Nu::Lexing::Lexer::ParseDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto declaration = UpCast<Declaration>(token))
		{
			if(auto identifier = declaration->GetIdentifier())
			{
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
						identifier->SetValue(unit);
						return declaration;
					}
				}
				else
				{
					throw Exception();
				}
			}
			else
			{
				throw Exception();
			}
		}
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Scope> Nu::Lexing::Lexer::ParseScope(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto scope = UpCast<Scope>(token))
		{
			// TODO: ParseScopeBody(scope);

			return scope;
		}
	}

	return nullptr;
}
/*inline void Nu::Lexing::Lexer::ParseScopeBody(const Reference<Scope>& scope_)
{
	scope_->RemoveEmptySources();

	auto &tokens = scope_->GetTokens();
	auto it = tokens.begin();

	while(it != tokens.end()) // iterate through collection utill end
	{
		try
		{
			if(!ParseScopeContent(tokens, it, scope_))
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
}*/
/*inline bool Nu::Lexing::Lexer::ParseScopeContent(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto token = ParseSource(tokens_, it_, scope_))
	{
		tokens_.insert(o, token);
		throw RetryException();
	}

	it_ = o;
	if(auto space = ParseSpace(tokens_, it_, scope_))
	{
		return true;
	}

	it_ = o;
	if(auto scope = ParseScope(tokens_, it_, scope_))
	{
		return true;
	}

	// it_ = o;
	// if(auto unit = ParseUnit(tokens_, it_, scope_))
	// {
	// 	return true;
	// }

	it_ = o;
	return false;
}*/

inline Nu::Reference<Nu::Lexing::Unnamed> Nu::Lexing::Lexer::ParseUnnamed(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto space = ParseSpace(tokens_, it_, scope_))
	{
		return space;
	}

	it_ = o;
	return nullptr;
}

inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::ParseSpace(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto token = ParseToken(tokens_, it_, scope_))
	{
		if(auto space = UpCast<Space>(token))
		{
			ParseSpaceBody(space);

			return space;
		}
	}

	it_ = o;
	if(auto identifier = ParseIdentifier(tokens_, it_, scope_))
	{
		if(auto value = identifier->GetValue())
		{
			if(auto space = UpCast<Space>(value))
			{
				ParseSpaceBody(space);

				return space;
			}
		}
	}

	it_ = o;
	if(auto space = ParseSpaceDeclaration(tokens_, it_, scope_))
	{
		auto i = tokens_.erase(o, it_);
		tokens_.insert(i, space);
		throw RetryException();
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::ParseSpaceDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	if(auto keyword = ParseKeyword(Keyword::Type::Space, tokens_, it_, scope_))
	{
		if(auto scope = ParseScope(tokens_, it_, scope_))
		{
			auto space = Make<Space>(scope_);
			scope->ChangeTo(space);
			return space;
		}
	}

	it_ = o;
	return nullptr;
}
inline void Nu::Lexing::Lexer::ParseSpaceBody(const Reference<Space>& space_)
{
	space_->RemoveEmptySources();

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
			isSkips = true;
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

	it_ = o;
	if(auto unnamed = ParseUnnamed(tokens_, it_, space_))
	{
		return true;
	}

	it_ = o;
	if(auto symbol = ParseSymbol(Symbol::Type::Semicolon, tokens_, it_, space_))
	{
		return true;
	}

	it_ = o;
	return false;
}

inline Nu::Reference<Nu::Lexing::Space> Nu::Lexing::Lexer::Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_)
{
	auto keywordsSpace = Make<Space>(nullptr);

	auto spaceIdentifier = Make<Identifier>("space");
	{
		auto spaceKeyword = Make<Keyword>(Keyword::Type::Space);
		spaceIdentifier->SetValue(spaceKeyword);

		keywordsSpace->Add(spaceIdentifier);
	}

	auto preparator = Make<MarkersPreparator>(GetThis<Lexer>(), Cast<Space>(keywordsSpace));
	preparator->Performer::Perform(Cast<NamesDeclarationStage::Marker>(namingScope_));

	while(true)
	{
		isSkips = false;

		try
		{
			ParseSpaceBody(keywordsSpace);
			if(!isSkips)
			{
				break;
			}
		}
		catch(RetryException)
		{
		}
	}

	return keywordsSpace;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion


/*

ParseSpace
	ParseToken + UpCast + ParseSpaceContent
	ParseSpaceDeclaration + ParseSpaceContent

ParseSpaceDeclaration
	ParseKeyword + ParseScope = Retry

ParseKeyword
	ParseIdentifier + Value + UpCast = Skip

ParseIdentifier
	ParseToken + UpCast
	ParseDeclaration
	ParseName

*/


















