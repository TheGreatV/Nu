#pragma once

#pragma region Include

#include "Header.hpp"

#include <../Lexer2/Lexer.hpp>

#pragma endregion


namespace Nu
{
	template<class T> Vector<T> ToVector(const List<T>& source_)
	{
		auto vector = Vector<T>();

		vector.reserve(source_.size());

		for (auto &i : source_)
		{
			vector.push_back(i);
		}

		return Move(vector);
	}

	namespace Parsing4
	{
		/*
		class T:
		public Entity
		{
		public:
		inline T() = delete;
		inline T(const Reference<T>& this_);
		inline T(const T&) = delete;
		inline virtual ~T() override = default;
		public:
		inline T& operator = (const T&) = delete;
		};
		*/

		// Declarations
		class Marker;
		namespace Markers
		{
			class Token;
			class Delimiter;
			class Group;
			class Declaration;
		}
		class MarkersContainer;

		class Unit;
		class Keyword;
		class Scope;
		namespace Scopes
		{
			class ThroughAccessScope;
			class SpaceLikeScope;

			class Outer;
			class Root;
			class Space;
			class Schema;
		}
		class Algorithm;
		namespace Algorithms
		{
			class BraceAlgorithm;
		}
		class AlgorithmsContainer;

		class Context;
		class Parser;


		// Definitions
		class Marker:
			public Entity
		{
		public:
			inline Marker() = delete;
			inline Marker(const Reference<Marker>& this_);
			inline Marker(const Marker&) = delete;
			inline virtual ~Marker() override = default;
		public:
			inline Marker& operator = (const Marker&) = delete;
		};
		class MarkersContainer
		{
		public:
			using Markers = List<Reference<Marker>>;
		protected:
			Markers markers;
		public:
			inline MarkersContainer(const Markers& markers_ = Markers());
			inline MarkersContainer(const MarkersContainer&) = delete;
			inline ~MarkersContainer() = default;
		public:
			inline MarkersContainer& operator = (const MarkersContainer&) = delete;
		public:
			inline Markers& GetMarkers();
		};
		namespace Markers
		{
			class Token:
				public Marker
			{
			public:
				using Value = Reference<Lexing2::Token>;
			protected:
				const Value value;
			public:
				inline Token() = delete;
				inline Token(const Reference<Token>& this_, const Value& value_);
				inline Token(const Token&) = delete;
				inline virtual ~Token() override = default;
			public:
				inline Token& operator = (const Token&) = delete;
			public:
				inline Value GetValue() const;
			};
			class Delimiter:
				public Marker
			{
			public:
				inline Delimiter() = delete;
				inline Delimiter(const Reference<Delimiter>& this_);
				inline Delimiter(const Delimiter&) = delete;
				inline virtual ~Delimiter() override = default;
			public:
				inline Delimiter& operator = (const Delimiter&) = delete;
			};
			class Group:
				public Marker,
				public MarkersContainer
			{
			public:
				using BraceType = Lexing2::Group::BraceType;
			protected:
				const BraceType opening;
				const BraceType closing;
			public:
				inline Group() = delete;
				inline Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_ = Markers());
				inline Group(const Group&) = delete;
				inline virtual ~Group() override = default;
			public:
				inline Group& operator = (const Group&) = delete;
			public:
				inline BraceType GetOpening() const;
				inline BraceType GetClosing() const;
			};
			class Declaration:
				public Marker
			{
			public:
				using Value = String;
			protected:
				const Value value;
			public:
				inline Declaration() = delete;
				inline Declaration(const Reference<Declaration>& this_, const Value& value_);
				inline Declaration(const Declaration&) = delete;
				inline virtual ~Declaration() override = default;
			public:
				inline Declaration& operator = (const Declaration&) = delete;
			public:
				inline Value GetValue() const;
			};
			class Name:
				public Marker
			{
			protected:
				const Reference<Unit> unit;
			public:
				inline Name() = delete;
				inline Name(const Reference<Name>& this_, const Reference<Unit>& unit_);
				inline Name(const Name&) = delete;
				inline virtual ~Name() override = default;
			public:
				inline Name& operator = (const Name&) = delete;
			public:
				inline Reference<Unit> GetUnit() const;
			};
			class SpaceDeclaration:
				public Marker
			{
			protected:
				const Reference<Scopes::Space> space;
			public:
				inline SpaceDeclaration() = delete;
				inline SpaceDeclaration(const Reference<SpaceDeclaration>& this_, const Reference<Scopes::Space>& space_);
				inline SpaceDeclaration(const SpaceDeclaration&) = delete;
				inline virtual ~SpaceDeclaration() override = default;
			public:
				inline SpaceDeclaration& operator = (const SpaceDeclaration&) = delete;
			public:
				inline Reference<Scopes::Space> GetSpace() const;
			};
			class SchemaDeclaration:
				public Marker
			{
			protected:
				const Reference<Scopes::Schema> schema;
			public:
				inline SchemaDeclaration() = delete;
				inline SchemaDeclaration(const Reference<SchemaDeclaration>& this_, const Reference<Scopes::Schema>& schema_);
				inline SchemaDeclaration(const SchemaDeclaration&) = delete;
				inline virtual ~SchemaDeclaration() override = default;
			public:
				inline SchemaDeclaration& operator = (const SchemaDeclaration&) = delete;
			public:
				inline Reference<Scopes::Schema> GetSchema() const;
			};
		}

		class Unit:
			public Entity
		{
		public:
			inline Unit() = delete;
			inline Unit(const Reference<Unit>& this_);
			inline Unit(const Unit&) = delete;
			inline virtual ~Unit() override = default;
		public:
			inline Unit& operator = (const Unit&) = delete;
		};
		class Keyword:
			public Unit
		{
		public:
			enum class Value
			{
				None, // not in use
				Space,
				Schema,
				Algorithm,
			};
		protected:
			const Value value;
		public:
			inline Keyword() = delete;
			inline Keyword(const Reference<Keyword>& this_, const Value& value_);
			inline Keyword(const Keyword&) = delete;
			inline virtual ~Keyword() override = default;
		public:
			inline Keyword& operator = (const Keyword&) = delete;
		public:
			inline Value GetValue() const;
		};
		class AlgorithmsContainer
		{
		public:
			inline AlgorithmsContainer() = default;
			inline AlgorithmsContainer(const AlgorithmsContainer&) = delete;
			inline ~AlgorithmsContainer() = default;
		public:
			inline AlgorithmsContainer& operator = (const AlgorithmsContainer&) = delete;
		};
		class Scope:
			public Unit,
			public MarkersContainer
		{
		public:
			inline Scope() = delete;
			inline Scope(const Reference<Scope>& this_, const Markers& markers_ = Markers());
			inline Scope(const Scope&) = delete;
			inline virtual ~Scope() override = default;
		public:
			inline Scope& operator = (const Scope&) = delete;
		};
		namespace Scopes
		{
			class ThroughAccessScope:
				public Scope
			{
			public:
				inline ThroughAccessScope() = delete;
				inline ThroughAccessScope(const Reference<ThroughAccessScope>& this_, const Markers& markers_ = Markers());
				inline ThroughAccessScope(const ThroughAccessScope&) = delete;
				inline virtual ~ThroughAccessScope() override = default;
			public:
				inline ThroughAccessScope& operator = (const ThroughAccessScope&) = delete;
			};
			class SpaceLikeScope:
				public ThroughAccessScope
			{
			public:
				inline SpaceLikeScope() = delete;
				inline SpaceLikeScope(const Reference<SpaceLikeScope>& this_, const Markers& markers_ = Markers());
				inline SpaceLikeScope(const SpaceLikeScope&) = delete;
				inline virtual ~SpaceLikeScope() override = default;
			public:
				inline SpaceLikeScope& operator = (const SpaceLikeScope&) = delete;
			};

			class Outer:
				public ThroughAccessScope
			{
			protected:
				const Reference<Parsing4::Markers::Declaration> declarationSpace = Make<Parsing4::Markers::Declaration>("space");
				const Reference<Parsing4::Markers::Declaration> declarationSchema = Make<Parsing4::Markers::Declaration>("schema");
				const Reference<Parsing4::Markers::Declaration> declarationAlgorithm = Make<Parsing4::Markers::Declaration>("algorithm");
				const Reference<Keyword> keywordSpace = Make<Keyword>(Keyword::Value::Space);
				const Reference<Keyword> keywordSchema = Make<Keyword>(Keyword::Value::Schema);
				const Reference<Keyword> keywordAlgorithm = Make<Keyword>(Keyword::Value::Algorithm);
			public:
				inline Outer() = delete;
				inline Outer(const Reference<Outer>& this_);
				inline Outer(const Outer&) = delete;
				inline virtual ~Outer() override = default;
			public:
				inline Outer& operator = (const Outer&) = delete;
			public:
				inline void BindToContext(const Reference<Context>& context_);
			};
			class Root:
				public SpaceLikeScope
			{
			public:
				inline Root() = delete;
				inline Root(const Reference<Root>& this_, const Markers& markers_ = Markers());
				inline Root(const Root&) = delete;
				inline virtual ~Root() override = default;
			public:
				inline Root& operator = (const Root&) = delete;
			};
			class Space:
				public SpaceLikeScope,
				public AlgorithmsContainer
			{
			public:
				inline Space() = delete;
				inline Space(const Reference<Space>& this_, const Markers& markers_ = Markers());
				inline Space(const Space&) = delete;
				inline virtual ~Space() override = default;
			public:
				inline Space& operator = (const Space&) = delete;
			};
			class Schema:
				public Scope
			{
			public:
				inline Schema() = delete;
				inline Schema(const Reference<Schema>& this_, const Markers& markers_ = Markers());
				inline Schema(const Schema&) = delete;
				inline virtual ~Schema() override = default;
			public:
				inline Schema& operator = (const Schema&) = delete;
			};
		}
		class Algorithm:
			public Unit,
			public MarkersContainer
		{
		public:
			inline Algorithm() = delete;
			inline Algorithm(const Reference<Algorithm>& this_, const Markers& markers_ = Markers());
			inline Algorithm(const Algorithm&) = delete;
			inline virtual ~Algorithm() override = default;
		public:
			inline Algorithm& operator = (const Algorithm&) = delete;
		};
		namespace Algorithms
		{
			class BraceAlgorithm:
				public Algorithm
			{
			public:
				using BraceType = Lexing2::Group::BraceType;
			protected:
				const BraceType opening;
				const BraceType closing;
			public:
				inline BraceAlgorithm() = delete;
				inline BraceAlgorithm(const Reference<BraceAlgorithm>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_ = Markers());
				inline BraceAlgorithm(const BraceAlgorithm&) = delete;
				inline virtual ~BraceAlgorithm() override = default;
			public:
				inline BraceAlgorithm& operator = (const BraceAlgorithm&) = delete;
			public:
				inline BraceType GetOpening() const;
				inline BraceType GetClosing() const;
			};
		}

		class Parser:
			public Entity
		{
		public:
			using Input = Reference<Lexing2::Container>;
			using Output = Reference<Context>;
			using Data = MarkersContainer::Markers;
			using It = Data::iterator;
		public:
			class MarkersReplaceRequired;
			class MarkersSkipRequired;
		public:
			inline static Reference<Marker> Convert(const Reference<Lexing2::Token>& token_);
			inline static MarkersContainer::Markers Convert(const Lexing2::Container::Tokens& tokens_);
			inline static Reference<Scopes::Root> Convert(const Reference<Lexing2::Container>& container_);
		protected:
			Reference<Context> context;
		public:
			inline Parser() = delete;
			inline Parser(const Reference<Parser>& this_);
			inline Parser(const Parser&) = delete;
			inline virtual ~Parser() override = default;
		public:
			inline Parser& operator = (const Parser&) = delete;
		protected:
			// utilities
			inline void																SkipUntilDeclaration(Data& data_, It& it_, const It& o_);
			// basic objects
			inline Reference<Marker>												ParseMarker(Data& data_, It& it_);
			template<class T> inline Reference<T>									ParseMarker(Data& data_, It& it_);
			template<class T> inline Reference<T>									ParseToken(Data& data_, It& it_);
			template<Lexing2::Special::Value T> inline Reference<Lexing2::Special>	ParseSpecialToken(Data& data_, It& it_);
			// names
			inline Size																CountDots(Data& data_, It& it_);
			inline Reference<Markers::Declaration>									ProcessExtractingChildsChain(Data& data_, It& it_, const Reference<Markers::Declaration>& parent_);
			inline Reference<Markers::Name>											ExtractName(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::Name>											ParseName(Data& data_, It& it_, const Reference<Scope>& scope_);
			template<class T> inline Reference<T>									ParseNamed(Data& data_, It& it_, const Reference<Scope>& scope_);
			// declarations
			inline Reference<Scopes::Space>											ParseSpace(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Space>											ExtractSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::SpaceDeclaration>								ParseSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Schema>										ParseSchema(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Schema>										ExtractSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::SchemaDeclaration>							ParseSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			// keyword
			inline Reference<Keyword>												ParseKeyword(Data& data_, It& it_, const Reference<Scope>& scope_, const Keyword::Value& value_ = Keyword::Value::None);
			// content of scopes
			inline void																ParseContent(const Reference<Scopes::SpaceLikeScope>& space_);
			inline void																ParseContent(const Reference<Scopes::Schema>& schema_);
		public:
			inline Output															Parse(const Input& input_);
		};
		class Parser::MarkersReplaceRequired
		{
		public:
			const It begin;
			const It end;
			const Data markers;
		public:
			inline MarkersReplaceRequired(const It& begin_, const It& end_, const Data& markers_);
		};
		class Parser::MarkersSkipRequired
		{
		public:
			const It begin;
			const It end;
		public:
			inline MarkersSkipRequired(const It& begin_, const It& end_);
		};
		class Context
		{
		public:
			using It = Parser::It;
			using UnorderedNames = Map<String, List<Reference<Markers::Declaration>>>;
			using Names = Vector<Pair<String, Vector<Reference<Markers::Declaration>>>>;
		public:
			static inline UnorderedNames MergeNames(const UnorderedNames& front_, const UnorderedNames& back_);
		public: // TODO: make protected
			bool isSkipped;
			bool isChanged;
			Reference<Scopes::Root> root = nullptr;
			Map<Reference<Scope>, Parser::It*> currentPosition;
			Vector<Reference<Scope>> pendingToParse;
			Map<Reference<Unit>, Reference<Scope>> parentLookup;
			Map<Reference<Markers::Declaration>, Reference<Unit>> valueLookup;
		public:
			// root
			inline Reference<Scopes::Root> GetRoot() const;
			inline void SetRoot(const Reference<Scopes::Root>& root_);
			// parenthood
			inline void SetParent(const Reference<Unit>& unit_, const Reference<Scope>& scope_);
			inline Reference<Scope> GetParent(const Reference<Unit>& unit_);
			// declarations value
			inline void SetValue(const Reference<Markers::Declaration>& declaration_, const Reference<Unit>& unit_);
			inline Reference<Unit> GetValue(const Reference<Markers::Declaration>& declaration_);
			// names
			inline UnorderedNames GetOwnNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_);
			inline UnorderedNames GetNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_);
			inline Names GetNames(const Reference<Scope>& fromScope_, const It& fromIt_);
			// current position
			inline void SetPosition(const Reference<Scope>& scope_, It* it_);
			inline void ResetPosition(const Reference<Scope>& scope_);
			// pending to parse
			inline void AddToPendingToParse(const Reference<Scope>& scope_);
			inline void RemoveFromPendingToParse(const Reference<Scope>& scope_);
			inline Vector<Reference<Scope>> GetPendingToParse();
		};
	}
}


#pragma region Nu

#pragma region Parsing4

/*
#pragma region T

Nu::Parsing4::T::T(const Reference<T>& this_):
	Entity(this_)
{
}

#pragma endregion
*/

#pragma region Marker

Nu::Parsing4::Marker::Marker(const Reference<Marker>& this_):
Entity(this_)
{
}

#pragma endregion

#pragma region Markers

#pragma region Token

Nu::Parsing4::Markers::Token::Token(const Reference<Token>& this_, const Value& value_):
	Marker(this_),
	value(value_)
{
}

Nu::Parsing4::Markers::Token::Value Nu::Parsing4::Markers::Token::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Delimiter

Nu::Parsing4::Markers::Delimiter::Delimiter(const Reference<Delimiter>& this_):
	Marker(this_)
{
}

#pragma endregion

#pragma region Group

Nu::Parsing4::Markers::Group::Group(const Reference<Group>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_):
	Marker(this_),
	MarkersContainer(markers_),
	opening(opening_),
	closing(closing_)
{
}

Nu::Parsing4::Markers::Group::BraceType Nu::Parsing4::Markers::Group::GetOpening() const
{
	return opening;
}
Nu::Parsing4::Markers::Group::BraceType Nu::Parsing4::Markers::Group::GetClosing() const
{
	return closing;
}

#pragma endregion

#pragma region Declaration

Nu::Parsing4::Markers::Declaration::Declaration(const Reference<Declaration>& this_, const Value& value_):
	Marker(this_),
	value(value_)
{
}

Nu::Parsing4::Markers::Declaration::Value Nu::Parsing4::Markers::Declaration::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Name

Nu::Parsing4::Markers::Name::Name(const Reference<Name>& this_, const Reference<Unit>& unit_):
	Marker(this_),
	unit(unit_)
{
}

Nu::Reference<Nu::Parsing4::Unit> Nu::Parsing4::Markers::Name::GetUnit() const
{
	return unit;
}

#pragma endregion

#pragma region SpaceDeclaration

Nu::Parsing4::Markers::SpaceDeclaration::SpaceDeclaration(const Reference<SpaceDeclaration>& this_, const Reference<Scopes::Space>& space_):
	Marker(this_),
	space(space_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Space> Nu::Parsing4::Markers::SpaceDeclaration::GetSpace() const
{
	return space;
}

#pragma endregion

#pragma region SchemaDeclaration

Nu::Parsing4::Markers::SchemaDeclaration::SchemaDeclaration(const Reference<SchemaDeclaration>& this_, const Reference<Scopes::Schema>& schema_):
	Marker(this_),
	schema(schema_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Schema> Nu::Parsing4::Markers::SchemaDeclaration::GetSchema() const
{
	return schema;
}

#pragma endregion

#pragma endregion

#pragma region MarkersContainer

Nu::Parsing4::MarkersContainer::MarkersContainer(const Markers& markers_):
	markers(markers_)
{
}

Nu::Parsing4::MarkersContainer::Markers& Nu::Parsing4::MarkersContainer::GetMarkers()
{
	return markers;
}

#pragma endregion

#pragma region Unit

Nu::Parsing4::Unit::Unit(const Reference<Unit>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Keyword

Nu::Parsing4::Keyword::Keyword(const Reference<Keyword>& this_, const Value& value_):
	Unit(this_),
	value(value_)
{
}

Nu::Parsing4::Keyword::Value Nu::Parsing4::Keyword::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Scope

Nu::Parsing4::Scope::Scope(const Reference<Scope>& this_, const Markers& markers_):
	Unit(this_),
	MarkersContainer(markers_)
{
}

#pragma endregion

#pragma region Scopes

#pragma region ThroughAccessScope

Nu::Parsing4::Scopes::ThroughAccessScope::ThroughAccessScope(const Reference<ThroughAccessScope>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma region SpaceLikeScope

Nu::Parsing4::Scopes::SpaceLikeScope::SpaceLikeScope(const Reference<SpaceLikeScope>& this_, const Markers& markers_):
	ThroughAccessScope(this_, markers_)
{
}

#pragma endregion

#pragma region Outer

Nu::Parsing4::Scopes::Outer::Outer(const Reference<Outer>& this_):
	ThroughAccessScope(this_)
{
	markers.push_back(declarationSpace);
	markers.push_back(declarationSchema);
	markers.push_back(declarationAlgorithm);
}

void Nu::Parsing4::Scopes::Outer::BindToContext(const Reference<Context>& context_)
{
	context_->SetValue(declarationSpace, keywordSpace);
	context_->SetValue(declarationSchema, keywordSchema);
	context_->SetValue(declarationAlgorithm, keywordAlgorithm);
}

#pragma endregion

#pragma region Root

Nu::Parsing4::Scopes::Root::Root(const Reference<Root>& this_, const Markers& markers_):
	SpaceLikeScope(this_, markers_)
{
}

#pragma endregion

#pragma region Space

Nu::Parsing4::Scopes::Space::Space(const Reference<Space>& this_, const Markers& markers_):
	SpaceLikeScope(this_, markers_),
	AlgorithmsContainer()
{
}

#pragma endregion

#pragma region Schema

Nu::Parsing4::Scopes::Schema::Schema(const Reference<Schema>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma endregion

#pragma region Algorithm

Nu::Parsing4::Algorithm::Algorithm(const Reference<Algorithm>& this_, const Markers& markers_):
	Unit(this_),
	MarkersContainer(markers_)
{
}

#pragma endregion

#pragma region Algorithms

#pragma region BraceAlgorithm

Nu::Parsing4::Algorithms::BraceAlgorithm::BraceAlgorithm(const Reference<BraceAlgorithm>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_):
	Algorithm(this_, markers_),
	opening(opening_),
	closing(closing_)
{
}

Nu::Parsing4::Algorithms::BraceAlgorithm::BraceType Nu::Parsing4::Algorithms::BraceAlgorithm::GetOpening() const
{
	return opening;
}
Nu::Parsing4::Algorithms::BraceAlgorithm::BraceType Nu::Parsing4::Algorithms::BraceAlgorithm::GetClosing() const
{
	return closing;
}

#pragma endregion

#pragma endregion

#pragma region AlgorithmsContainer

#pragma endregion

#pragma region Context

Nu::Parsing4::Context::UnorderedNames Nu::Parsing4::Context::MergeNames(const UnorderedNames& front_, const UnorderedNames& back_)
{
	auto names = back_;

	for (auto &i : front_)
	{
		auto &j = names[i.first];
		
		j.insert(j.begin(), i.second.begin(), i.second.end());
	}

	return Move(names);
}

Nu::Reference<Nu::Parsing4::Scopes::Root> Nu::Parsing4::Context::GetRoot() const
{
	return root;
}
void Nu::Parsing4::Context::SetRoot(const Reference<Scopes::Root>& root_)
{
	if (!root)
	{
		root = root_;
	}
	else
	{
		throw Exception();
	}
}

void Nu::Parsing4::Context::SetParent(const Reference<Unit>& unit_, const Reference<Scope>& scope_)
{
	auto it = parentLookup.find(unit_);

	if (it == parentLookup.end())
	{
		parentLookup[unit_] = scope_;
	}
	else
	{
		auto parent = (*it).second;

		if (parent != scope_)
		{
			throw Exception(); // TODO
		}
	}
}
Nu::Reference<Nu::Parsing4::Scope> Nu::Parsing4::Context::GetParent(const Reference<Unit>& unit_)
{
	auto it = parentLookup.find(unit_);

	if (it != parentLookup.end())
	{
		return (*it).second;
	}
	else
	{
		return nullptr;
	}
}

void Nu::Parsing4::Context::SetValue(const Reference<Markers::Declaration>& declaration_, const Reference<Unit>& unit_)
{
	auto it = valueLookup.find(declaration_);

	if (it == valueLookup.end())
	{
		valueLookup[declaration_] = unit_;
	}
	else
	{
		auto value = (*it).second;

		if (unit_ != value)
		{
			throw Exception(); // TODO
		}
	}
}
Nu::Reference<Nu::Parsing4::Unit> Nu::Parsing4::Context::GetValue(const Reference<Markers::Declaration>& declaration_)
{
	auto it = valueLookup.find(declaration_);

	if (it != valueLookup.end())
	{
		return (*it).second;
	}
	else
	{
		return nullptr;
	}
}

Nu::Parsing4::Context::UnorderedNames Nu::Parsing4::Context::GetOwnNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_)
{
	if (auto throughAccessScope = UpCast<Scopes::ThroughAccessScope>(target_))
	{
		UnorderedNames names;

		auto &markers = throughAccessScope->GetMarkers();

		for (auto &marker : markers)
		{
			if (auto declaration = UpCast<Markers::Declaration>(marker))
			{
				auto value = declaration->GetValue();

				names[value].push_front(declaration);
			}
		}

		return Move(names);
	}
	else
	{
		throw Exception();
	}
}
Nu::Parsing4::Context::UnorderedNames Nu::Parsing4::Context::GetNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_)
{
	if (target_ == nullptr)
	{
		return UnorderedNames();
	}
	else if (auto throughAccessScope = UpCast<Scopes::ThroughAccessScope>(target_))
	{
		auto ownNames = GetOwnNames(target_, fromScope_, fromIt_);
		auto parent = GetParent(target_);
		auto parentNames = GetNames(parent, fromScope_, fromIt_);
		auto names = MergeNames(ownNames, parentNames);
		
		return Move(names);
	}
	else
	{
		throw Exception();
	}
}
Nu::Parsing4::Context::Names Nu::Parsing4::Context::GetNames(const Reference<Scope>& fromScope_, const It& fromIt_)
{
	auto unordered = Move(GetNames(fromScope_, fromScope_, fromIt_));
	auto ordered = Names();

	for (auto &i : unordered)
	{
		ordered.push_back(Pair<String, Vector<Reference<Markers::Declaration>>>(i.first, ToVector(i.second)));
	}

	std::sort(ordered.begin(), ordered.end(), [](const Pair<String, Vector<Reference<Markers::Declaration>>>& a, const Pair<String, Vector<Reference<Markers::Declaration>>>& b)
	{
		return a.first < b.first;
	});
	
	return Move(ordered);
}

void Nu::Parsing4::Context::SetPosition(const Reference<Scope>& scope_, It* it_)
{
	currentPosition[scope_] = it_;
}
void Nu::Parsing4::Context::ResetPosition(const Reference<Scope>& scope_)
{
	currentPosition.erase(scope_);
}

void Nu::Parsing4::Context::AddToPendingToParse(const Reference<Scope>& scope_)
{
	pendingToParse.push_back(scope_);
}
void Nu::Parsing4::Context::RemoveFromPendingToParse(const Reference<Scope>& scope_)
{
	pendingToParse.erase(std::find(pendingToParse.begin(), pendingToParse.end(), scope_));
}
Nu::Vector<Nu::Reference<Nu::Parsing4::Scope>> Nu::Parsing4::Context::GetPendingToParse()
{
	return pendingToParse;
}

#pragma endregion

#pragma region Parser

#pragma region MarkersReplaceRequired

inline Nu::Parsing4::Parser::MarkersReplaceRequired::MarkersReplaceRequired(const It& begin_, const It& end_, const Data& markers_):
	begin(begin_),
	end(end_),
	markers(markers_)
{
}

#pragma endregion

#pragma region MarkersSkipRequired

inline Nu::Parsing4::Parser::MarkersSkipRequired::MarkersSkipRequired(const It& begin_, const It& end_):
	begin(begin_),
	end(end_)
{
}

#pragma endregion


Nu::Reference<Nu::Parsing4::Marker> Nu::Parsing4::Parser::Convert(const Reference<Lexing2::Token>& token_)
{
	if (auto groupToken = UpCast<Lexing2::Group>(token_))
	{
		auto &tokens = groupToken->GetTokens();
		auto markers = Convert(tokens);

		auto group = Make<Markers::Group>(groupToken->GetOpening(), groupToken->GetClosing(), Move(markers));

		return Move(group);
	}
	else if (auto specialToken = UpCast<Lexing2::Special>(token_))
	{
		if (specialToken->GetValue() == Lexing2::Special::Value::Semicolon)
		{
			auto delimiter = Make<Markers::Delimiter>();

			return Move(delimiter);
		}
	}

	auto tokenMarker = Make<Markers::Token>(token_);

	return Move(tokenMarker);
}
Nu::Parsing4::MarkersContainer::Markers Nu::Parsing4::Parser::Convert(const Lexing2::Container::Tokens& tokens_)
{
	auto markers = MarkersContainer::Markers();

	for (auto &token : tokens_)
	{
		auto marker = Convert(token);

		markers.push_back(marker);
	}

	// convert definitions
	for (auto it = markers.begin(); it != markers.end(); ++it)
	{
		auto marker = *it;

		if (auto tokenMarker = UpCast<Markers::Token>(marker))
		{
			auto value = tokenMarker->GetValue();

			if (auto text = UpCast<Lexing2::Text>(value))
			{
				auto it1 = it; ++it1;

				if (it1 != markers.end())
				{
					auto marker1 = *it1;

					if (auto tokenMarker1 = UpCast<Markers::Token>(marker1))
					{
						auto value1 = tokenMarker1->GetValue();

						if (auto special = UpCast<Lexing2::Special>(value1))
						{
							if (special->GetValue() == Lexing2::Special::Value::Colon)
							{
								auto it2 = it1; ++it2;
								auto textValue = text->GetValue();
								auto declaration = Make<Markers::Declaration>(textValue);

								it = markers.erase(it, it2);
								it = markers.insert(it, declaration);
							}
						}
					}
				}
			}
		}
	}

	return Move(markers);
}
Nu::Reference<Nu::Parsing4::Scopes::Root> Nu::Parsing4::Parser::Convert(const Reference<Lexing2::Container>& container_)
{
	auto &tokens = container_->GetTokens();
	auto &markers = Move(Convert(tokens));
	auto root = Make<Scopes::Root>(markers);

	return root;
}

Nu::Parsing4::Parser::Parser(const Reference<Parser>& this_):
	Entity(this_)
{
}

void Nu::Parsing4::Parser::SkipUntilDeclaration(Data& data_, It& it_, const It& o_)
{
	auto it = it_;

	while (it != data_.end() && !UpCast<Markers::Declaration>(*it))
	{
		++it;
	}

	throw MarkersSkipRequired(o_, it);
}

Nu::Reference<Nu::Parsing4::Marker> Nu::Parsing4::Parser::ParseMarker(Data& data_, It& it_)
{
	auto o = it_;

	if (it_ != data_.end())
	{
		auto marker = *it_;

		++it_;

		return marker;
	}

	it_ = o;
	return nullptr;
}
template<class T> Nu::Reference<typename T> Nu::Parsing4::Parser::ParseMarker(Data& data_, It& it_)
{
	auto o = it_;

	if (auto marker = ParseMarker(data_, it_))
	{
		if (auto casted = UpCast<T>(marker))
		{
			return casted;
		}
	}

	it_ = o;
	return nullptr;
}
template<class T> Nu::Reference<typename T> Nu::Parsing4::Parser::ParseToken(Data& data_, It& it_)
{
	auto o = it_;

	if (auto markerToken = ParseMarker<Markers::Token>(data_, it_))
	{
		auto token = markerToken->GetValue();
		
		if (auto casted = UpCast<T>(token))
		{
			return casted;
		}
	}

	it_ = o;
	return nullptr;
}
template<Nu::Lexing2::Special::Value T> Nu::Reference<Nu::Lexing2::Special> Nu::Parsing4::Parser::ParseSpecialToken(Data& data_, It& it_)
{
	auto o = it_;

	if (auto special = ParseToken<Lexing2::Special>(data_, it_))
	{
		if (special->GetValue() == T)
		{
			return special;
		}
	}

	it_ = o;
	return nullptr;
}

Nu::Size Nu::Parsing4::Parser::CountDots(Data& data_, It& it_)
{
	Size dotsCount = 0;

	while (auto dot = ParseSpecialToken<Lexing2::Special::Value::Dot>(data_, it_))
	{
		++dotsCount;
	}
	
	return dotsCount;
}
Nu::Reference<Nu::Parsing4::Markers::Declaration> Nu::Parsing4::Parser::ProcessExtractingChildsChain(Data& data_, It& it_, const Reference<Markers::Declaration>& parent_)
{
	auto o = it_;

	auto dotsCount = CountDots(data_, it_);

	if (dotsCount > 0)
	{
		auto unit = context->GetValue(parent_);

		if (unit)
		{
			if (auto scope = UpCast<Scope>(unit))
			{
				if (auto text = ParseToken<Lexing2::Text>(data_, it_))
				{
					auto value = text->GetValue();
					auto names = context->GetNames(scope, it_); // names ordered from larger ot smaller

					for (auto &nameIt : names)
					{
						auto &nameValue = nameIt.first;

						if (value.find(nameValue) == 0)
						{
							auto &levels = nameIt.second;
							auto requiredLevel = dotsCount - 1;

							if (requiredLevel < levels.size())
							{
								auto name = levels[requiredLevel];

								if (value.size() == nameValue.size())
								{
									return ProcessExtractingChildsChain(data_, it_, name);
								}
								else
								{
									// TODO: splice
									throw NotImplementedException();
								}
							}
							else
							{
								throw Exception(); // TODO
							}
						}
					}

					throw Exception(); // TODO
				}
				else
				{
					throw Exception(); // TODO
				}
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		else
		{
			SkipUntilDeclaration(data_, it_, o);
		}
	}
	else
	{
		return parent_;
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::Name> Nu::Parsing4::Parser::ExtractName(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	auto dotsCount = CountDots(data_, it_);

	if (auto text = ParseToken<Lexing2::Text>(data_, it_))
	{
		auto value = text->GetValue();
		auto names = context->GetNames(scope_, it_); // names ordered from larger ot smaller
		
		for (auto &nameIt : names)
		{
			auto &nameValue = nameIt.first;

			if (value.find(nameValue) == 0)
			{
				auto &levels = nameIt.second;
				auto requiredLevel = dotsCount;

				if (requiredLevel < levels.size())
				{
					auto name = levels[requiredLevel];

					if (value.size() == nameValue.size())
					{
						auto lastDeclaration = ProcessExtractingChildsChain(data_, it_, name);
						auto lastValue = context->GetValue(lastDeclaration);

						if (lastValue)
						{
							auto name = Make<Markers::Name>(lastValue);

							return Move(name);
						}
						else
						{
							SkipUntilDeclaration(data_, it_, o);
						}
					}
					else
					{
						// TODO: splice
						throw NotImplementedException();

						/*
						auto markers = Data();
						{
							markers.push_back(Make<Token>(Make<Lexing2::Text>(nameValue)));
							markers.push_back(Make<Token>(Make<Lexing2::Text>(value.substr(nameValue.size()))));
						}

						throw MarkersReplaceRequired(o, it_, markers);
						*/
					}
				}
				else
				{
					throw Exception(); // TODO
				}
			}
		}

		throw Exception(); // TODO
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::Name> Nu::Parsing4::Parser::ParseName(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto name = ParseMarker<Markers::Name>(data_, it_))
	{
		return name;
	}
	else if (auto extracted = ExtractName(data_, it_, scope_))
	{
		MarkersContainer::Markers markers;
		{
			markers.push_back(extracted);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}
template<class T> inline Nu::Reference<typename T> Nu::Parsing4::Parser::ParseNamed(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto name = ParseName(data_, it_, scope_))
	{
		auto unit = name->GetUnit();

		if (auto casted = UpCast<T>(unit))
		{
			return casted;
		}
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Scopes::Space> Nu::Parsing4::Parser::ParseSpace(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto named = ParseNamed<Scopes::Space>(data_, it_, scope_))
	{
		return named;
	}
	else if (auto declaration = ParseSpaceDeclaration(data_, it_, scope_))
	{
		auto space = declaration->GetSpace();

		return space;
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Scopes::Space> Nu::Parsing4::Parser::ExtractSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, scope_, Keyword::Value::Space))
	{
		if (auto group = ParseMarker<Markers::Group>(data_, it_))
		{
			if (group->GetOpening() == Markers::Group::BraceType::Figure && group->GetClosing() == Markers::Group::BraceType::Figure)
			{
				auto &markers = group->GetMarkers();
				auto space = Make<Scopes::Space>(Move(markers));
				{
					context->SetParent(space, scope_);
					context->AddToPendingToParse(space);

					context->isChanged = true;
				}

				return Move(space);
			}
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::SpaceDeclaration> Nu::Parsing4::Parser::ParseSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto spaceDeclaration = ParseMarker<Markers::SpaceDeclaration>(data_, it_))
	{
		return spaceDeclaration;
	}
	else if (auto extracted = ExtractSpaceDeclaration(data_, it_, scope_))
	{
		auto newSpaceDeclaration = Make<Markers::SpaceDeclaration>(extracted);

		MarkersContainer::Markers markers;
		{
			markers.push_back(newSpaceDeclaration);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Scopes::Schema> Nu::Parsing4::Parser::ParseSchema(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto named = ParseNamed<Scopes::Schema>(data_, it_, scope_))
	{
		return named;
	}
	else if (auto declaration = ParseSchemaDeclaration(data_, it_, scope_))
	{
		auto schema = declaration->GetSchema();

		return schema;
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Scopes::Schema> Nu::Parsing4::Parser::ExtractSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, scope_, Keyword::Value::Schema))
	{
		if (auto group = ParseMarker<Markers::Group>(data_, it_))
		{
			if (group->GetOpening() == Markers::Group::BraceType::Figure && group->GetClosing() == Markers::Group::BraceType::Figure)
			{
				auto &markers = group->GetMarkers();
				auto schema = Make<Scopes::Schema>(Move(markers));
				{
					context->SetParent(schema, scope_);
					context->AddToPendingToParse(schema);

					context->isChanged = true;
				}

				return Move(schema);
			}
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::SchemaDeclaration> Nu::Parsing4::Parser::ParseSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto schemaDeclaration = ParseMarker<Markers::SchemaDeclaration>(data_, it_))
	{
		return schemaDeclaration;
	}
	else if (auto extracted = ExtractSchemaDeclaration(data_, it_, scope_))
	{
		auto newSchemaDeclaration = Make<Markers::SchemaDeclaration>(extracted);

		MarkersContainer::Markers markers;
		{
			markers.push_back(newSchemaDeclaration);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Keyword> Nu::Parsing4::Parser::ParseKeyword(Data& data_, It& it_, const Reference<Scope>& scope_, const Keyword::Value& value_)
{
	auto o = it_;

	if (auto keyword = ParseNamed<Keyword>(data_, it_, scope_))
	{
		if (value_ == Keyword::Value::None || keyword->GetValue() == value_)
		{
			return keyword;
		}
	}

	it_ = o;
	return nullptr;
}

void Nu::Parsing4::Parser::ParseContent(const Reference<Scopes::SpaceLikeScope>& space_)
{
	auto &markers = space_->GetMarkers();
	auto it = markers.begin();

	context->SetPosition(space_, &it);

	bool isChanged = false;
	bool isSkipped = false;

	while (it != markers.end())
	{
		try
		{
			if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
			{
				// do nothing
			}
			else if (auto spaceDeclaration = ParseSpaceDeclaration(markers, it, space_))
			{
				// do nothing
			}
			else if (auto schemaDeclaration = ParseSchemaDeclaration(markers, it, space_))
			{
				// do nothing
			}
			else if (auto declaration = ParseMarker<Markers::Declaration>(markers, it))
			{
				if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
				{
					throw NotImplementedException(); // TODO: should we support this?
				}
				else if (auto space = ParseSpace(markers, it, space_))
				{
					context->SetValue(declaration, space);
				}
				else if (auto schema = ParseSchema(markers, it, space_))
				{
					context->SetValue(declaration, schema);
				}
				else if (auto keyword = ParseKeyword(markers, it, space_))
				{
					context->SetValue(declaration, keyword);
				}
				else
				{
					throw Exception(); // TODO
				}
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		catch (MarkersReplaceRequired replace)
		{
			isChanged = true;
			context->isChanged = true;

			auto i = markers.erase(replace.begin, replace.end);

			for (auto &m : replace.markers)
			{
				i = markers.insert(i, m);
			}

			it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isSkipped = true;
			context->isSkipped = true;

			it = skip.end;
		}
	}

	context->ResetPosition(space_);

	if (!isSkipped)
	{
		context->RemoveFromPendingToParse(space_);
	}
}
void Nu::Parsing4::Parser::ParseContent(const Reference<Scopes::Schema>& schema_)
{
	auto &markers = schema_->GetMarkers();
	auto it = markers.begin();

	context->SetPosition(schema_, &it);

	bool isChanged = false;
	bool isSkipped = false;

	while (it != markers.end())
	{
		try
		{
			if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
			{
				// do nothing
			}
			else
			{
				throw Exception(); // TODO
			}
		}
		catch (MarkersReplaceRequired replace)
		{
			isChanged = true;
			context->isChanged = true;

			auto i = markers.erase(replace.begin, replace.end);

			for (auto &m : replace.markers)
			{
				i = markers.insert(i, m);
			}

			it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isSkipped = true;
			context->isSkipped = true;

			it = skip.end;
		}
	}

	context->ResetPosition(schema_);

	if (!isSkipped)
	{
		context->RemoveFromPendingToParse(schema_);
	}
}

Nu::Parsing4::Parser::Output Nu::Parsing4::Parser::Parse(const Input& input_)
{
	// prepare parsing context
	context = MakeReference<Context>();

	// prepare root object
	auto outer = Make<Scopes::Outer>();
	{
		outer->BindToContext(context);
	}
	auto root = Convert(input_);
	{
		context->SetRoot(root);
		context->SetParent(root, outer);
	}

	// parse
	context->AddToPendingToParse(root);

	while (true)
	{
		auto pending = Move(context->GetPendingToParse());
		
		if (!pending.empty())
		{
			context->isSkipped = false;
			context->isChanged = false;

			for (auto &scope : pending)
			{
				if (auto root = UpCast<Scopes::Root>(scope))
				{
					ParseContent(root);
				}
				else if (auto space = UpCast<Scopes::Space>(scope))
				{
					ParseContent(space);
				}
				else if (auto schema = UpCast<Scopes::Schema>(scope))
				{
					ParseContent(schema);
				}
				else
				{
					throw Exception(); // TODO
				}
			}

			// error, if pending scopes left, but no changes was done
			if (context->isSkipped && !context->isChanged)
			{
				throw Exception(); // TODO
			}
		}
		else
		{
			break;
		}
	}

	// return context
	auto result = context;

	context = nullptr;

	return result;
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















