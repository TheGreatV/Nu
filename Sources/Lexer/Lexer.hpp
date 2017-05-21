#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Lexing
	{
		class Identifier;
		class Scope;
		class ScopeDependent;
		class ScopesContainer;

		class Token;
		class Declaration;
		class Assembly;

		class Lexer;


		class ScopeDependent:
			public Entity
		{
		protected:
			const Link<Scope> scope;
		public:
			inline ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_);
			virtual ~ScopeDependent() override = default;
		public:
			inline Reference<Scope> GetScope() const;
		};
		class Identifier:
			public ScopeDependent
		{
		public:
			using Value = String;
		protected:
			const Value value;
		public:
			inline Identifier(const Reference<Identifier>& this_, const Value& value_, const Reference<Scope>& scope_);
			virtual ~Identifier() override = default;
		public:
			inline Value GetValue() const;
		};
		class ScopesContainer
		{
		public:
			using Scopes = Vector<Reference<Scope>>;
		protected:
			Scopes scopes;
		public:
			inline ScopesContainer() = default;
			inline ~ScopesContainer() = default;
		public:
			inline Scopes GetScopes() const;
			inline void Add(const Reference<Scope>& scope_);
		};
		class Scope:
			public ScopeDependent,
			public ScopesContainer
		{
		public:
			using Identifiers = Vector<Reference<Identifier>>;
		protected:
			Identifiers identifiers;
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_);
			virtual ~Scope() override = default;
		public:
			inline Identifiers GetOwnedIdentifiers() const;
			Identifiers GetIdentifiers() const;
			inline void Add(const Reference<Identifier>& identifier_);
		};

		class Token:
			public Entity
		{
		public:
			inline Token(const Reference<Token>& this_);
			virtual ~Token() override = default;
		};

		class Lexer:
			public Entity
		{
		protected:
			class MarkersPerformer:
				public NamesDeclarationStage::Marker::Performer
			{
			protected:
				const Reference<Lexer> lexer;
				const Reference<Scope> scope;
			public:
				inline MarkersPerformer(const Reference<MarkersPerformer>& this_, const Reference<Lexer>& lexer_, const Reference<Scope>& scope_);
				virtual ~MarkersPerformer() override = default;
			protected:
				Size ExtractNameNestingLevel(const NamesDeclarationStage::Text::Value& value_, Size& i_);
				NamesDeclarationStage::Text::Value ExtractNameHeader(const NamesDeclarationStage::Text::Value& value_, Size& i_);
			protected:
				virtual void Perform(const Reference<NamesDeclarationStage::Text>& text_) override;
				virtual void Perform(const Reference<NamesDeclarationStage::Scope>& scope_) override;
			};
			friend MarkersPerformer;
		protected:
			Map<Reference<NamesDeclarationStage::Scope>, Reference<Scope>> lookupScope;
			Map<Reference<Scope>, Reference<NamesDeclarationStage::Scope>> lookupScopeBack;
		public:
			inline Lexer(const Reference<Lexer>& this_);
			virtual ~Lexer() override = default;
		protected:
			inline void Prepare(const Reference<Scope>& scope_, const Reference<NamesDeclarationStage::Scope>& namesScope_);
		protected:
			inline void ParseInternal(const Reference<NamesDeclarationStage::Scope>& namesScope_);
		public:
			inline Reference<Scope> Parse(const Reference<NamesDeclarationStage::Scope>& namesScope_);
		};
	}
}


#pragma region Nu

#pragma region Lexing

#pragma region ScopeDependent

inline Nu::Lexing::ScopeDependent::ScopeDependent(const Reference<ScopeDependent>& this_, const Reference<Scope>& scope_):
	Entity(this_),
	scope(scope_)
{
}
inline Nu::Reference<Nu::Lexing::Scope> Nu::Lexing::ScopeDependent::GetScope() const
{
	return MakeReference(scope);
}

#pragma endregion

#pragma region Identifier

inline Nu::Lexing::Identifier::Identifier(const Reference<Identifier>& this_, const Value& value_, const Reference<Scope>& scope_):
	ScopeDependent(this_, scope_),
	value(value_)
{
}
inline Nu::Lexing::Identifier::Value Nu::Lexing::Identifier::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region ScopesContainer

inline Nu::Lexing::ScopesContainer::Scopes Nu::Lexing::ScopesContainer::GetScopes() const
{
	return scopes;
}
inline void Nu::Lexing::ScopesContainer::Add(const Reference<Scope>& scope_)
{
	scopes.push_back(scope_);
}

#pragma endregion

#pragma region Scope

inline Nu::Lexing::Scope::Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_):
	ScopeDependent(this_, scope_),
	ScopesContainer()
{
}

inline Nu::Lexing::Scope::Identifiers Nu::Lexing::Scope::GetOwnedIdentifiers() const
{
	return identifiers;
}
inline void Nu::Lexing::Scope::Add(const Reference<Identifier>& identifier_)
{
	identifiers.push_back(identifier_);
}

#pragma endregion

#pragma region Token

inline Nu::Lexing::Token::Token(const Reference<Token>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Lexer

#pragma region MarkersPerformer

inline Nu::Lexing::Lexer::MarkersPerformer::MarkersPerformer(const Reference<MarkersPerformer>& this_, const Reference<Lexer>& lexer_, const Reference<Scope>& scope_):
	Performer(this_),
	lexer(lexer_),
	scope(scope_)
{
}

#pragma endregion


inline Nu::Lexing::Lexer::Lexer(const Reference<Lexer>& this_):
	Entity(this_)
{
}

inline void Nu::Lexing::Lexer::Prepare(const Reference<Scope>& scope_, const Reference<NamesDeclarationStage::Scope>& namesScope_)
{
	for(auto &namesIdentifier : namesScope_->GetIdentifiers())
	{
		auto identifier = Make<Identifier>(namesIdentifier->GetValue(), scope_);
		scope_->Add(identifier);
	}

	for(auto &marker : namesScope_->GetMarkers())
	{
		if(auto namesScope = UpCast<NamesDeclarationStage::Scope>(marker))
		{
			auto scope = Make<Scope>(scope_);
			lookupScope[namesScope] = scope;
			lookupScopeBack[scope] = namesScope;

			Prepare(scope, namesScope);
		}
	}
}

inline void Nu::Lexing::Lexer::ParseInternal(const Reference<NamesDeclarationStage::Scope>& namesScope_)
{
	auto scope = lookupScope[namesScope_];

	auto performer = Make<MarkersPerformer>(GetThis<Lexer>(), scope);

	for(auto &marker : namesScope_->GetMarkers())
	{
		performer->Performer::Perform(marker);
	}
}

inline Nu::Reference<Nu::Lexing::Scope> Nu::Lexing::Lexer::Parse(const Reference<NamesDeclarationStage::Scope>& namesScope_)
{
	auto keywordsScope = Make<Scope>(nullptr);
	lookupScope[namesScope_] = keywordsScope;
	lookupScopeBack[keywordsScope] = namesScope_;

	// Add keywords
	auto identifierSchema = Make<Identifier>("schema", keywordsScope);
	keywordsScope->Add(identifierSchema);
	auto identifierAlgorithm = Make<Identifier>("algorithm", keywordsScope);
	keywordsScope->Add(identifierAlgorithm);
	auto identifierBody = Make<Identifier>("body", keywordsScope);
	keywordsScope->Add(identifierBody);
	auto identifierMake = Make<Identifier>("make", keywordsScope);
	keywordsScope->Add(identifierMake);

	auto mainScope = Make<Scope>(keywordsScope);
	keywordsScope->ScopesContainer::Add(mainScope);

	Prepare(mainScope, namesScope_);

	ParseInternal(namesScope_);

	return Move(keywordsScope);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















