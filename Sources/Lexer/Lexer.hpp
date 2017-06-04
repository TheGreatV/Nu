#pragma once

#pragma region Include

#include <regex>

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing
	{
		class Token;
		class Source;
		class Identifier;

		class Unit;
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
		};
		class IdentifiersContainer
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
		};

		class ScopeDependent:
			public Entity
		{
		protected:
			Reference<Scope> scope = nullptr;
		public:
			inline ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_);
		public:
			inline Reference<Scope> GetScope() const;
			inline void SetScope(const Reference<Scope>& scope_);
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
				for(auto &dependency : dependencies)
				{
					dependency->SetScope(new_);
				}
			}
		};
		class Space:
			public Scope
		{
		public:
			inline Space(const Reference<Space>& this_, const Reference<Scope>& scope_):
				Scope(this_, scope_)
			{
			}
			virtual ~Space() override = default;
		};

		class Lexer:
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
			/*inline Reference<Space> ParseSpace(const TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<IScope>& scope_);
			inline void ParseScopeContent(const Reference<IScope>& scope_);
			inline void ParseSpaceContent(const Reference<Space>& space_);*/
			inline bool ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Token> ExtractToken(const Reference<Source>& source_, const Reference<Scope>& scope_);
			inline SymbolsSet ExtractSymbolsSet(const Source::Value& value_);

			inline Reference<Scope> ParseScope(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline void ParseScopeBody(const Reference<Scope>& scope_);
			inline bool ParseScopeBodyContent(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);

			inline Reference<Space> ParseSpace(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline Reference<Space> ParseSpaceDeclaration(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_);
			inline void ParseSpaceBody(const Reference<Space>& space_);
		public:
			inline Reference<Space> Parse(const Reference<NamesDeclarationStage::Scope>& namingScope_);
		};
#pragma region MarkersPreparator
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
				throw Exception();
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

#pragma region Lexer

inline Nu::Lexing::Lexer::Lexer(const Reference<Lexer>& this_):
	Entity(this_)
{
}

/*
inline void Nu::Lexing::Lexer::ParseScopeContent(const Reference<IScope>& scope_)
{
	scope_->RemoveEmptySources();

	auto &tokens = scope_->GetTokens();
	auto it = tokens.begin();
	
	while(true)
	{
		if(auto space = ParseSpace(tokens, it, scope_))
		{
		}
		else if(ParseSource(tokens, it, scope_))
		{
		}
	}

	// for(auto i = tokens.begin(); i != tokens.end(); ++i)
	// {
	// 	auto token = *i;
	// 
	// 	if(auto source = UpCast<Source>(token))
	// 	{
	// 		auto token = ParseSource(source, scope_);
	// 		tokens.insert(i, token);
	// 		throw Retry();
	// 	}
	// 	else if(auto identifier = UpCast<Identifier>(token))
	// 	{
	// 	}
	// }
}
inline void Nu::Lexing::Lexer::ParseSpaceContent(const Reference<Space>& space_)
{
	ParseScopeContent(space_);

	// space_->RemoveEmptySources();
	// 
	// auto &tokens = space_->GetTokens();
	// for(auto i = tokens.begin(); i != tokens.end(); ++i)
	// {
	// 	auto token = *i;
	// 
	// 	if(auto scope = UpCast<IScope>(token))
	// 	{
	// 		ParseScopeContent(scope);
	// 	}
	// }
}
*/

inline bool Nu::Lexing::Lexer::ParseSource(TokensContainer::Tokens& tokens_, TokensContainer::Tokens::const_iterator& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto source = UpCast<Source>(token))
		{
			auto token = ExtractToken(source, scope_);
			tokens_.insert(it_, token);
			throw Retry();
		}
	}

	it_ = o;
	return false;
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
	if(ParseSource(tokens_, it_, scope_))
	{
		return true; // move "throw" here
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

	if(it_ != tokens_.end())
	{
		auto &token = *it_;
		++it_;

		if(auto identifier = UpCast<Identifier>(token))
		{
			auto value = identifier->GetValue();
			if(value)
			{
				if(auto keyword = UpCast<Keyword>(value))
				{
					if(keyword->GetType() == Keyword::Type::Space)
					{
						if(it_ != tokens_.end())
						{
							auto &token = *it_;
							++it_;

							if(auto scope = UpCast<Scope>(token))
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
				}
			}
		}
	}

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
	preparator->Perform(namingScope_);

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

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















