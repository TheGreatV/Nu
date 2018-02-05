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
		// Declarations
		class Marker;
		namespace Markers
		{
			class Token;
			class Delimiter;
			class Group;
			class Declaration;
			class Name;
			class SpaceDeclaration;
			class SchemaDeclaration;
			class AlgorithmDeclaration;
			class BodyDeclaration;
			class SequenceReference;
		}
		class MarkersContainer;

		class Unit;
		class Keyword;
		class Scope;
		namespace Scopes
		{
			class EmptyAccessScope;
			class ThroughAccessScope;
			class ForwardAccessScope;
			class AlgorithmicScope;

			class Outer;
			class Root;
			class Space;
			class Schema;
			class Body;
			class Instance;
			class Sequence;
		}
		class Algorithm;
		namespace Algorithms
		{
			class Brace;
		}
		class AlgorithmsContainer;
		class Argument;
		namespace Arguments
		{
			class CopyInstance;
		}
		class Command;
		namespace Commands
		{
			class Argument;
			namespace Arguments
			{
				class CopyInstance;
				class CopyResultInstance;
			}
			class CreateInstance;
			class CopyInstance;
			class ResultInstance;
			class AlgorithmCall;
		}

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
			class AlgorithmDeclaration:
				public Marker
			{
			protected:
				const Reference<Algorithm> algorithm;
			public:
				inline AlgorithmDeclaration() = delete;
				inline AlgorithmDeclaration(const Reference<AlgorithmDeclaration>& this_, const Reference<Algorithm>& algorithm_);
				inline AlgorithmDeclaration(const AlgorithmDeclaration&) = delete;
				inline virtual ~AlgorithmDeclaration() override = default;
			public:
				inline AlgorithmDeclaration& operator = (const AlgorithmDeclaration&) = delete;
			public:
				inline Reference<Algorithm> GetAlgorithm() const;
			};
			class BodyDeclaration:
				public Marker
			{
			protected:
				const Reference<Scopes::Body> algorithm;
			public:
				inline BodyDeclaration() = delete;
				inline BodyDeclaration(const Reference<BodyDeclaration>& this_, const Reference<Scopes::Body>& algorithm_);
				inline BodyDeclaration(const BodyDeclaration&) = delete;
				inline virtual ~BodyDeclaration() override = default;
			public:
				inline BodyDeclaration& operator = (const BodyDeclaration&) = delete;
			public:
				inline Reference<Scopes::Body> GetBody() const;
			};
			class SequenceReference:
				public Marker
			{
			protected:
				const Reference<Scopes::Sequence> sequence;
			public:
				inline SequenceReference() = delete;
				inline SequenceReference(const Reference<SequenceReference>& this_, const Reference<Scopes::Sequence>& sequence_);
				inline SequenceReference(const SequenceReference&) = delete;
				inline virtual ~SequenceReference() override = default;
			public:
				inline SequenceReference& operator = (const SequenceReference&) = delete;
			public:
				inline Reference<Scopes::Sequence> GetSequence() const;
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
				Body,
				Make,
				Copy,
				Return,
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
		class AlgorithmsContainer
		{
		public:
			inline AlgorithmsContainer() = default;
			inline AlgorithmsContainer(const AlgorithmsContainer&) = delete;
			inline virtual ~AlgorithmsContainer() = default;
		public:
			inline AlgorithmsContainer& operator = (const AlgorithmsContainer&) = delete;
		};
		namespace Scopes
		{
			class EmptyAccessScope:
				public Scope
			{
			public:
				inline EmptyAccessScope() = delete;
				inline EmptyAccessScope(const Reference<EmptyAccessScope>& this_, const Markers& markers_ = Markers());
				inline EmptyAccessScope(const EmptyAccessScope&) = delete;
				inline virtual ~EmptyAccessScope() override = default;
			public:
				inline EmptyAccessScope& operator = (const EmptyAccessScope&) = delete;
			};
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
			class ForwardAccessScope:
				public Scope
			{
			public:
				inline ForwardAccessScope() = delete;
				inline ForwardAccessScope(const Reference<ForwardAccessScope>& this_, const Markers& markers_ = Markers());
				inline ForwardAccessScope(const ForwardAccessScope&) = delete;
				inline virtual ~ForwardAccessScope() override = default;
			public:
				inline ForwardAccessScope& operator = (const ForwardAccessScope&) = delete;
			};
			class AlgorithmicScope:
				public ThroughAccessScope,
				public AlgorithmsContainer
			{
			public:
				inline AlgorithmicScope() = delete;
				inline AlgorithmicScope(const Reference<AlgorithmicScope>& this_, const Markers& markers_ = Markers());
				inline AlgorithmicScope(const AlgorithmicScope&) = delete;
				inline virtual ~AlgorithmicScope() override = default;
			public:
				inline AlgorithmicScope& operator = (const AlgorithmicScope&) = delete;
			};

			class Outer:
				public ThroughAccessScope
			{
			protected:
				const Reference<Parsing4::Markers::Declaration> declarationSpace = Make<Parsing4::Markers::Declaration>("space");
				const Reference<Parsing4::Markers::Declaration> declarationSchema = Make<Parsing4::Markers::Declaration>("schema");
				const Reference<Parsing4::Markers::Declaration> declarationAlgorithm = Make<Parsing4::Markers::Declaration>("algorithm");
				const Reference<Parsing4::Markers::Declaration> declarationBody = Make<Parsing4::Markers::Declaration>("body");
				const Reference<Parsing4::Markers::Declaration> declarationMake = Make<Parsing4::Markers::Declaration>("make");
				const Reference<Parsing4::Markers::Declaration> declarationCopy = Make<Parsing4::Markers::Declaration>("copy");
				const Reference<Parsing4::Markers::Declaration> declarationReturn = Make<Parsing4::Markers::Declaration>("return");
				const Reference<Parsing4::Markers::Declaration> declarationNone = Make<Parsing4::Markers::Declaration>("none");
				const Reference<Keyword> keywordSpace = Make<Keyword>(Keyword::Value::Space);
				const Reference<Keyword> keywordSchema = Make<Keyword>(Keyword::Value::Schema);
				const Reference<Keyword> keywordAlgorithm = Make<Keyword>(Keyword::Value::Algorithm);
				const Reference<Keyword> keywordBody = Make<Keyword>(Keyword::Value::Body);
				const Reference<Keyword> keywordMake = Make<Keyword>(Keyword::Value::Make);
				const Reference<Keyword> keywordCopy = Make<Keyword>(Keyword::Value::Copy);
				const Reference<Keyword> keywordReturn = Make<Keyword>(Keyword::Value::Return);
				const Reference<Scopes::Schema> schemaNone = Make<Scopes::Schema>();
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
				public ThroughAccessScope
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
				public AlgorithmicScope
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
				public EmptyAccessScope
			{
			public:
				inline Schema() = delete;
				inline Schema(const Reference<Schema>& this_, const Markers& markers_ = Markers());
				inline Schema(const Schema&) = delete;
				inline virtual ~Schema() override = default;
			public:
				inline Schema& operator = (const Schema&) = delete;
			};
			class Body:
				public ForwardAccessScope
			{
			public:
				inline Body() = delete;
				inline Body(const Reference<Body>& this_, const Markers& markers_ = Markers());
				inline Body(const Body&) = delete;
				inline virtual ~Body() override = default;
			public:
				inline Body& operator = (const Body&) = delete;
			};
			class Instance:
				public EmptyAccessScope
			{
			public:
				inline Instance() = delete;
				inline Instance(const Reference<Instance>& this_, const Markers& markers_ = Markers());
				inline Instance(const Instance&) = delete;
				inline virtual ~Instance() override = default;
			public:
				inline Instance& operator = (const Instance&) = delete;
			};
			class Sequence:
				public EmptyAccessScope
			{
			public:
				using BraceType = Parsing4::Markers::Group::BraceType;
			protected:
				const BraceType opening;
				const BraceType closing;
			public:
				inline Sequence() = delete;
				inline Sequence(const Reference<Sequence>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_ = Markers());
				inline Sequence(const Sequence&) = delete;
				inline virtual ~Sequence() override = default;
			public:
				inline Sequence& operator = (const Sequence&) = delete;
			public:
				inline BraceType GetOpening() const;
				inline BraceType GetClosing() const;
			};
		}
		class Algorithm:
			public Scopes::ThroughAccessScope
		{
		public:
			using Result = Reference<Scopes::Schema>;
		protected:
			const Result result;
		public:
			inline Algorithm() = delete;
			inline Algorithm(const Reference<Algorithm>& this_, const Result& result_, const Markers& markers_ = Markers());
			inline Algorithm(const Algorithm&) = delete;
			inline virtual ~Algorithm() override = default;
		public:
			inline Algorithm& operator = (const Algorithm&) = delete;
		public:
			inline Result GetResult() const;
		};
		namespace Algorithms
		{
			class Brace:
				public Algorithm
			{
			public:
				using BraceType = Lexing2::Group::BraceType;
			protected:
				const BraceType opening;
				const BraceType closing;
			public:
				inline Brace() = delete;
				inline Brace(const Reference<Brace>& this_, const BraceType& opening_, const BraceType& closing_, const Result& result_, const Markers& markers_ = Markers());
				inline Brace(const Brace&) = delete;
				inline virtual ~Brace() override = default;
			public:
				inline Brace& operator = (const Brace&) = delete;
			public:
				inline BraceType GetOpening() const;
				inline BraceType GetClosing() const;
			};
		}
		class Argument:
			public Marker
		{
		public:
			inline Argument() = delete;
			inline Argument(const Reference<Argument>& this_);
			inline Argument(const Argument&) = delete;
			inline virtual ~Argument() override = default;
		public:
			inline Argument& operator = (const Argument&) = delete;
		};
		namespace Arguments
		{
			class CopyInstance:
				public Argument
			{
			protected:
				const Reference<Scopes::Instance> instance;
			public:
				inline CopyInstance() = delete;
				inline CopyInstance(const Reference<CopyInstance>& this_, const Reference<Scopes::Instance>& instance_);
				inline CopyInstance(const CopyInstance&) = delete;
				inline virtual ~CopyInstance() override = default;
			public:
				inline CopyInstance& operator = (const CopyInstance&) = delete;
			public:
				inline Reference<Scopes::Instance> GetInstance() const;
			};
		}
		class Command:
			public Marker
		{
		public:
			inline Command() = delete;
			inline Command(const Reference<Command>& this_);
			inline Command(const Command&) = delete;
			inline virtual ~Command() override = default;
		public:
			inline Command& operator = (const Command&) = delete;
		};
		namespace Commands
		{
			class Argument:
				public Command
			{
			public:
				inline Argument() = delete;
				inline Argument(const Reference<Argument>& this_);
				inline Argument(const Argument&) = delete;
				inline virtual ~Argument() override = default;
			public:
				inline Argument& operator = (const Argument&) = delete;
			};
			namespace Arguments
			{
				class CopyInstance:
					public Argument
				{
				protected:
					const Reference<Scopes::Instance> instance;
				public:
					inline CopyInstance() = delete;
					inline CopyInstance(const Reference<CopyInstance>& this_, const Reference<Scopes::Instance>& instance_);
					inline CopyInstance(const CopyInstance&) = delete;
					inline virtual ~CopyInstance() override = default;
				public:
					inline CopyInstance& operator = (const CopyInstance&) = delete;
				public:
					inline Reference<Scopes::Instance> GetInstance() const;
				};
				class CopyResultInstance:
					public CopyInstance
				{
				protected:
					const Reference<ResultInstance> result;
				public:
					inline CopyResultInstance() = delete;
					inline CopyResultInstance(const Reference<CopyResultInstance>& this_, const Reference<ResultInstance>& result_);
					inline CopyResultInstance(const CopyResultInstance&) = delete;
					inline virtual ~CopyResultInstance() override = default;
				public:
					inline CopyResultInstance& operator = (const CopyResultInstance&) = delete;
				public:
					inline Reference<ResultInstance> GetResult() const;
				};
			};
			class CreateInstance:
				public Command
			{
			protected:
				const Reference<Scopes::Instance> instance;
			public:
				inline CreateInstance() = delete;
				inline CreateInstance(const Reference<CreateInstance>& this_, const Reference<Scopes::Instance>& instance_);
				inline CreateInstance(const CreateInstance&) = delete;
				inline virtual ~CreateInstance() override = default;
			public:
				inline CreateInstance& operator = (const CreateInstance&) = delete;
			public:
				inline Reference<Scopes::Instance> GetInstance() const;
			};
			class ReturnInstance:
				public Command
			{
			protected:
				const Reference<Scopes::Instance> instance;
			public:
				inline ReturnInstance() = delete;
				inline ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Scopes::Instance>& instance_);
				inline ReturnInstance(const ReturnInstance&) = delete;
				inline virtual ~ReturnInstance() override = default;
			public:
				inline ReturnInstance& operator = (const ReturnInstance&) = delete;
			public:
				inline Reference<Scopes::Instance> GetInstance() const;
			};
			class ResultInstance:
				public Command
			{
			protected:
				const Reference<Scopes::Instance> result;
			public:
				inline ResultInstance() = delete;
				inline ResultInstance(const Reference<ResultInstance>& this_, const Reference<Scopes::Instance>& result_);
				inline ResultInstance(const ResultInstance&) = delete;
				inline virtual ~ResultInstance() override = default;
			public:
				inline ResultInstance& operator = (const ResultInstance&) = delete;
			public:
				inline Reference<Scopes::Instance> GetResult() const;
			};
			class AlgorithmCall:
				public ResultInstance
			{
			protected:
				const Reference<Algorithm> algorithm;
			public:
				inline AlgorithmCall() = delete;
				inline AlgorithmCall(const Reference<AlgorithmCall>& this_, const Reference<Algorithm>& algorithm_, const Reference<Scopes::Instance>& result_);
				inline AlgorithmCall(const AlgorithmCall&) = delete;
				inline virtual ~AlgorithmCall() override = default;
			public:
				inline AlgorithmCall& operator = (const AlgorithmCall&) = delete;
			public:
				inline Reference<Algorithm> GetAlgorithm() const;
			};
			class BraceAlgorithmCall:
				public AlgorithmCall
			{
			public:
				using Arguments = Vector<Reference<Argument>>;
			protected:
				const Arguments arguments;
			public:
				inline BraceAlgorithmCall() = delete;
				inline BraceAlgorithmCall(const Reference<BraceAlgorithmCall>& this_, const Arguments& arguments_, const Reference<Algorithms::Brace>& algorithm_, const Reference<Scopes::Instance>& result_);
				inline BraceAlgorithmCall(const BraceAlgorithmCall&) = delete;
				inline virtual ~BraceAlgorithmCall() override = default;
			public:
				inline BraceAlgorithmCall& operator = (const BraceAlgorithmCall&) = delete;
			public:
				inline Reference<Algorithms::Brace> GetAlgorithm() const;
				inline Arguments GetArguments() const;
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
			inline static Reference<Markers::SequenceReference> Convert(const Reference<Markers::Group>& group_, const Reference<Context>& context_);
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
			inline Reference<Unit>													ParseNamed(Data& data_, It& it_, const Reference<Scope>& scope_);
			template<class T> inline Reference<T>									ParseNamed(Data& data_, It& it_, const Reference<Scope>& scope_);
			// declarations
			inline Reference<Scopes::Space>											ParseSpace(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Space>											ExtractSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::SpaceDeclaration>								ParseSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			
			inline Reference<Scopes::Schema>										ParseSchema(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Schema>										ExtractSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::SchemaDeclaration>							ParseSchemaDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			
			inline Reference<Algorithms::Brace>										ExtractBraceAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_);
			inline Reference<Markers::AlgorithmDeclaration>							ParseAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_);
			inline Reference<Markers::AlgorithmDeclaration>							ParseFullAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_);

			inline Reference<Scopes::Body>											ExtractBodyDeclaration(Data& data_, It& it_, const Reference<Algorithm>& algorithm_, const Reference<Scope>& scope_);
			inline Reference<Markers::BodyDeclaration>								ParseBodyDeclaration(Data& data_, It& it_, const Reference<Algorithm>& algorithm_, const Reference<Scope>& scope_);
			// arguments
			inline Reference<Arguments::CopyInstance>								ExtractCopyInstanceArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_);
			inline Reference<Arguments::CopyInstance>								ParseCopyInstanceArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_);
			inline Reference<Argument>												ParseArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_);
			// commands
			inline Reference<Commands::CreateInstance>								ExtractCreateInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_);
			inline Reference<Commands::CreateInstance>								ParseCreateInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_);

			inline Reference<Commands::ReturnInstance>								ExtractReturnInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_);
			inline Reference<Commands::ReturnInstance>								ParseReturnInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_);

			inline Reference<Pair<Reference<Scopes::Sequence>, Commands::BraceAlgorithmCall::Arguments>> ParseBraceAlgorithmCallArguments(Data& data_, It& it_, const Reference<Scope>& body_);
			
			inline Reference<Commands::BraceAlgorithmCall>							ExtractBraceAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_);
			inline Reference<Commands::BraceAlgorithmCall>							ParseBraceAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_);
			inline Reference<Commands::AlgorithmCall>								ParseAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_);

			inline Reference<Scopes::Sequence>										ExtractSequence(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Scopes::Sequence>										ParseSequence(Data& data_, It& it_, const Reference<Scope>& scope_);

			inline Reference<Keyword>												ParseKeyword(Data& data_, It& it_, const Reference<Scope>& scope_, const Keyword::Value& value_ = Keyword::Value::None);
			// content of scopes
			inline void																ParseContent(const Reference<Scopes::Root>& root_);
			inline void																ParseContent(const Reference<Scopes::Space>& space_);
			inline void																ParseContent(const Reference<Scopes::Schema>& schema_);
			inline void																ParseContent(const Reference<Algorithms::Brace>& algorithm_);
			inline void																ParseContent(const Reference<Scopes::Body>& body_);
			inline void																ParseContent(const Reference<Scopes::Sequence>& sequence_);
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
			Map<Reference<MarkersContainer>, Parser::It*> currentPosition;
			Vector<Reference<Scope>> pendingToParse;
			Map<Reference<Unit>, Reference<Scope>> parentLookup;
			Map<Reference<Markers::Declaration>, Reference<Unit>> valueLookup;
			Map<Reference<AlgorithmsContainer>, Vector<Reference<Algorithm>>> algorithmsLookup;
			Map<Reference<Algorithms::Brace>, Size> braceAlgorithmArgumentIndex;
			Map<Reference<Algorithms::Brace>, Vector<Reference<Argument>>> braceAlgorithmArguments;
			Map<Reference<Scopes::Instance>, Reference<Scopes::Schema>> instancesSchemas;
			Map<Reference<Algorithm>, Reference<Scopes::Body>> bodiesLookup;
		protected:
			Reference<Scopes::Root> root = nullptr;
			Reference<Scopes::Schema> noneSchema = nullptr;
		public:
			// root
			inline Reference<Scopes::Root> GetRoot() const;
			inline void SetRoot(const Reference<Scopes::Root>& root_);
			inline Reference<Scopes::Schema> GetNoneSchema() const;
			inline void SetNoneSchema(const Reference<Scopes::Schema>& schema_);
			// parenthood
			inline void SetParent(const Reference<Unit>& unit_, const Reference<Scope>& scope_);
			inline Reference<Scope> GetParent(const Reference<Unit>& unit_);
			inline bool IsChild(const Reference<Unit>& unit_, const Reference<Scope>& scope_);
			inline void SetSchema(const Reference<Scopes::Instance>& instance_, const Reference<Scopes::Schema>& schema_);
			inline Reference<Scopes::Schema> GetSchema(const Reference<Scopes::Instance>& instance_);
			inline void SetBody(const Reference<Algorithm>& algorithm_, const Reference<Scopes::Body>& body_);
			inline Reference<Scopes::Body> GetBody(const Reference<Algorithm>& algorithm_);
			// declarations value
			inline void SetValue(const Reference<Markers::Declaration>& declaration_, const Reference<Unit>& unit_);
			inline Reference<Unit> GetValue(const Reference<Markers::Declaration>& declaration_);
			// algorithms
			inline void AddAlgorithm(const Reference<AlgorithmsContainer>& algorithmic_, const Reference<Algorithm>& algorithm_);
			inline Vector<Reference<Algorithm>> GetAlgorithms(const Reference<AlgorithmsContainer>& algorithmic_);
			inline void FlushBraceAlgorithmArguments(const Reference<Algorithms::Brace>& algorithm_);
			inline void SetBraceAlgorithmArgument(const Reference<Algorithms::Brace>& algorithm_, const Reference<Argument>& argument_);
			inline Vector<Reference<Argument>> GetArguments(const Reference<Algorithms::Brace>& algorithm_);
			// names
			inline UnorderedNames GetOwnNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_);
			inline UnorderedNames GetNames(const Reference<Scope>& target_, const Reference<Scope>& fromScope_, const It& fromIt_);
			inline Names GetNames(const Reference<Scope>& fromScope_, const It& fromIt_);
			// current position
			inline void SetPosition(const Reference<MarkersContainer>& markersContainer_, It* it_);
			inline void ResetPosition(const Reference<MarkersContainer>& markersContainer_);
			// pending to parse
			inline void AddToPendingToParse(const Reference<Scope>& scope_);
			inline void RemoveFromPendingToParse(const Reference<Scope>& scope_);
			inline Vector<Reference<Scope>> GetPendingToParse();
			inline bool IsPendingToParse(const Reference<Scope>& scope_) const;
			inline bool IsInterfaceComplete(const Reference<Scopes::AlgorithmicScope>& algorithmic_);
		};
	}
}


#pragma region Nu

#pragma region Parsing4

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

#pragma region AlgorithmDeclaration

Nu::Parsing4::Markers::AlgorithmDeclaration::AlgorithmDeclaration(const Reference<AlgorithmDeclaration>& this_, const Reference<Algorithm>& algorithm_):
	Marker(this_),
	algorithm(algorithm_)
{
}

Nu::Reference<Nu::Parsing4::Algorithm> Nu::Parsing4::Markers::AlgorithmDeclaration::GetAlgorithm() const
{
	return algorithm;
}

#pragma endregion

#pragma region BodyDeclaration

Nu::Parsing4::Markers::BodyDeclaration::BodyDeclaration(const Reference<BodyDeclaration>& this_, const Reference<Scopes::Body>& algorithm_):
	Marker(this_),
	algorithm(algorithm_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Body> Nu::Parsing4::Markers::BodyDeclaration::GetBody() const
{
	return algorithm;
}

#pragma endregion

#pragma region SequenceReference

Nu::Parsing4::Markers::SequenceReference::SequenceReference(const Reference<SequenceReference>& this_, const Reference<Scopes::Sequence>& sequence_):
	Marker(this_),
	sequence(sequence_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Sequence> Nu::Parsing4::Markers::SequenceReference::GetSequence() const
{
	return sequence;
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

#pragma region EmptyAccessScope

Nu::Parsing4::Scopes::EmptyAccessScope::EmptyAccessScope(const Reference<EmptyAccessScope>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma region ThroughAccessScope

Nu::Parsing4::Scopes::ThroughAccessScope::ThroughAccessScope(const Reference<ThroughAccessScope>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma region ForwardAccessScope

Nu::Parsing4::Scopes::ForwardAccessScope::ForwardAccessScope(const Reference<ForwardAccessScope>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma region AlgorithmicScope

Nu::Parsing4::Scopes::AlgorithmicScope::AlgorithmicScope(const Reference<AlgorithmicScope>& this_, const Markers& markers_):
	ThroughAccessScope(this_, markers_),
	AlgorithmsContainer()
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
	markers.push_back(declarationBody);
	markers.push_back(declarationMake);
	markers.push_back(declarationCopy);
	markers.push_back(declarationReturn);
	markers.push_back(declarationNone);
}

void Nu::Parsing4::Scopes::Outer::BindToContext(const Reference<Context>& context_)
{
	context_->SetValue(declarationSpace, keywordSpace);
	context_->SetValue(declarationSchema, keywordSchema);
	context_->SetValue(declarationAlgorithm, keywordAlgorithm);
	context_->SetValue(declarationBody, keywordBody);
	context_->SetValue(declarationMake, keywordMake);
	context_->SetValue(declarationCopy, keywordCopy);
	context_->SetValue(declarationReturn, keywordReturn);
	context_->SetValue(declarationNone, schemaNone);

	context_->SetNoneSchema(schemaNone);
}

#pragma endregion

#pragma region Root

Nu::Parsing4::Scopes::Root::Root(const Reference<Root>& this_, const Markers& markers_):
	ThroughAccessScope(this_, markers_)
{
}

#pragma endregion

#pragma region Space

Nu::Parsing4::Scopes::Space::Space(const Reference<Space>& this_, const Markers& markers_):
	AlgorithmicScope(this_, markers_)
{
}

#pragma endregion

#pragma region Schema

Nu::Parsing4::Scopes::Schema::Schema(const Reference<Schema>& this_, const Markers& markers_):
	EmptyAccessScope(this_, markers_)
{
}

#pragma endregion

#pragma region Body

Nu::Parsing4::Scopes::Body::Body(const Reference<Body>& this_, const Markers& markers_):
	ForwardAccessScope(this_, markers_)
{
}

#pragma endregion

#pragma region Instance

Nu::Parsing4::Scopes::Instance::Instance(const Reference<Instance>& this_, const Markers& markers_):
	EmptyAccessScope(this_, markers_)
{
}

#pragma endregion

#pragma region Sequence

Nu::Parsing4::Scopes::Sequence::Sequence(const Reference<Sequence>& this_, const BraceType& opening_, const BraceType& closing_, const Markers& markers_):
	EmptyAccessScope(this_, markers_),
	opening(opening_),
	closing(closing_)
{
}

Nu::Parsing4::Scopes::Sequence::BraceType Nu::Parsing4::Scopes::Sequence::GetOpening() const
{
	return opening;
}
Nu::Parsing4::Scopes::Sequence::BraceType Nu::Parsing4::Scopes::Sequence::GetClosing() const
{
	return closing;
}

#pragma endregion

#pragma endregion

#pragma region Algorithm

Nu::Parsing4::Algorithm::Algorithm(const Reference<Algorithm>& this_, const Result& result_, const Markers& markers_):
	ThroughAccessScope(this_, markers_),
	result(result_)
{
}

Nu::Parsing4::Algorithm::Result Nu::Parsing4::Algorithm::GetResult() const
{
	return result;
}

#pragma endregion

#pragma region Algorithms

#pragma region Brace

Nu::Parsing4::Algorithms::Brace::Brace(const Reference<Brace>& this_, const BraceType& opening_, const BraceType& closing_, const Result& result_, const Markers& markers_):
	Algorithm(this_, result_, markers_),
	opening(opening_),
	closing(closing_)
{
}

Nu::Parsing4::Algorithms::Brace::BraceType Nu::Parsing4::Algorithms::Brace::GetOpening() const
{
	return opening;
}
Nu::Parsing4::Algorithms::Brace::BraceType Nu::Parsing4::Algorithms::Brace::GetClosing() const
{
	return closing;
}

#pragma endregion

#pragma endregion

#pragma region AlgorithmsContainer

#pragma endregion

#pragma region Argument

Nu::Parsing4::Argument::Argument(const Reference<Argument>& this_):
	Marker(this_)
{
}

#pragma endregion

#pragma region Arguments

#pragma region CopyInstance

Nu::Parsing4::Arguments::CopyInstance::CopyInstance(const Reference<CopyInstance>& this_, const Reference<Scopes::Instance>& instance_):
	Argument(this_),
	instance(instance_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Instance> Nu::Parsing4::Arguments::CopyInstance::GetInstance() const
{
	return instance;
}

#pragma endregion

#pragma endregion

#pragma region Command

Nu::Parsing4::Command::Command(const Reference<Command>& this_):
	Marker(this_)
{
}

#pragma endregion

#pragma region Commands

#pragma region CreateInstance

Nu::Parsing4::Commands::CreateInstance::CreateInstance(const Reference<CreateInstance>& this_, const Reference<Scopes::Instance>& instance_):
	Command(this_),
	instance(instance_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Instance> Nu::Parsing4::Commands::CreateInstance::GetInstance() const
{
	return instance;
}

#pragma endregion

#pragma region Argument

Nu::Parsing4::Commands::Argument::Argument(const Reference<Argument>& this_):
	Command(this_)
{
}

#pragma endregion

#pragma region Arguments

#pragma region CopyInstance

Nu::Parsing4::Commands::Arguments::CopyInstance::CopyInstance(const Reference<CopyInstance>& this_, const Reference<Scopes::Instance>& instance_):
	Argument(this_),
	instance(instance_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Instance> Nu::Parsing4::Commands::Arguments::CopyInstance::GetInstance() const
{
	return instance;
}

#pragma endregion

#pragma region CopyResultInstance

Nu::Parsing4::Commands::Arguments::CopyResultInstance::CopyResultInstance(const Reference<CopyResultInstance>& this_, const Reference<ResultInstance>& result_):
	CopyInstance(this_, result_->GetResult()),
	result(result_)
{
}

Nu::Reference<Nu::Parsing4::Commands::ResultInstance> Nu::Parsing4::Commands::Arguments::CopyResultInstance::GetResult() const
{
	return result;
}

#pragma endregion

#pragma endregion

#pragma region ResultInstance

Nu::Parsing4::Commands::ResultInstance::ResultInstance(const Reference<ResultInstance>& this_, const Reference<Scopes::Instance>& result_):
	Command(this_),
	result(result_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Instance> Nu::Parsing4::Commands::ResultInstance::GetResult() const
{
	return result;
}

#pragma endregion

#pragma region ReturnInstance

Nu::Parsing4::Commands::ReturnInstance::ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Scopes::Instance>& instance_):
	Command(this_),
	instance(instance_)
{
}

Nu::Reference<Nu::Parsing4::Scopes::Instance> Nu::Parsing4::Commands::ReturnInstance::GetInstance() const
{
	return instance;
}

#pragma endregion

#pragma region AlgorithmCall

Nu::Parsing4::Commands::AlgorithmCall::AlgorithmCall(const Reference<AlgorithmCall>& this_, const Reference<Algorithm>& algorithm_, const Reference<Scopes::Instance>& result_):
	ResultInstance(this_, result_),
	algorithm(algorithm_)
{
}

Nu::Reference<Nu::Parsing4::Algorithm> Nu::Parsing4::Commands::AlgorithmCall::GetAlgorithm() const
{
	return algorithm;
}

#pragma endregion

#pragma region BraceAlgorithmCall

Nu::Parsing4::Commands::BraceAlgorithmCall::BraceAlgorithmCall(const Reference<BraceAlgorithmCall>& this_, const Arguments& arguments_, const Reference<Algorithms::Brace>& algorithm_, const Reference<Scopes::Instance>& result_):
	AlgorithmCall(this_, algorithm_, result_),
	arguments(arguments_)
{
}

Nu::Reference<Nu::Parsing4::Algorithms::Brace> Nu::Parsing4::Commands::BraceAlgorithmCall::GetAlgorithm() const
{
	auto a = UpCast<Algorithms::Brace>(algorithm);

	return a
		? a
		: throw Exception(); // TODO
}
Nu::Parsing4::Commands::BraceAlgorithmCall::Arguments Nu::Parsing4::Commands::BraceAlgorithmCall::GetArguments() const
{
	return arguments;
}

#pragma endregion

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
Nu::Reference<Nu::Parsing4::Scopes::Schema> Nu::Parsing4::Context::GetNoneSchema() const
{
	return noneSchema;
}
void Nu::Parsing4::Context::SetNoneSchema(const Reference<Scopes::Schema>& schema_)
{
	noneSchema = schema_;
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
		throw Exception(); // return nullptr;
	}
}
bool Nu::Parsing4::Context::IsChild(const Reference<Unit>& unit_, const Reference<Scope>& scope_)
{
	auto parent = GetParent(unit_);

	while (parent != nullptr && parent != scope_)
	{
		parent = GetParent(parent);
	}

	return parent == scope_;
}
void Nu::Parsing4::Context::SetSchema(const Reference<Scopes::Instance>& instance_, const Reference<Scopes::Schema>& schema_)
{
	auto it = instancesSchemas.find(instance_);

	if (it == instancesSchemas.end())
	{
		instancesSchemas[instance_] = schema_;
	}
	else
	{
		throw Exception(); // TODO
	}
}
Nu::Reference<Nu::Parsing4::Scopes::Schema> Nu::Parsing4::Context::GetSchema(const Reference<Scopes::Instance>& instance_)
{
	auto it = instancesSchemas.find(instance_);

	if (it != instancesSchemas.end())
	{
		return (*it).second;
	}
	else
	{
		throw Exception(); // TODO
	}
}
void Nu::Parsing4::Context::SetBody(const Reference<Algorithm>& algorithm_, const Reference<Scopes::Body>& body_)
{
	auto it = bodiesLookup.find(algorithm_);

	if (it == bodiesLookup.end())
	{
		bodiesLookup[algorithm_] = body_;
	}
	else
	{
		auto body = (*it).second;
		if (body_ != body)
		{
			throw Exception();
		}
	}
}
Nu::Reference<Nu::Parsing4::Scopes::Body> Nu::Parsing4::Context::GetBody(const Reference<Algorithm>& algorithm_)
{
	return bodiesLookup[algorithm_];
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

void Nu::Parsing4::Context::AddAlgorithm(const Reference<AlgorithmsContainer>& algorithmic_, const Reference<Algorithm>& algorithm_)
{
	algorithmsLookup[algorithmic_].push_back(algorithm_);
}
inline Nu::Vector<Nu::Reference<Nu::Parsing4::Algorithm>> Nu::Parsing4::Context::GetAlgorithms(const Reference<AlgorithmsContainer>& algorithmic_)
{
	return algorithmsLookup[algorithmic_];
}
void Nu::Parsing4::Context::FlushBraceAlgorithmArguments(const Reference<Algorithms::Brace>& algorithm_)
{
	braceAlgorithmArgumentIndex[algorithm_] = 0;

	auto it = braceAlgorithmArguments.find(algorithm_);

	if (it == braceAlgorithmArguments.end())
	{
		braceAlgorithmArguments[algorithm_] = Vector<Reference<Argument>>();
	}
}
void Nu::Parsing4::Context::SetBraceAlgorithmArgument(const Reference<Algorithms::Brace>& algorithm_, const Reference<Argument>& argument_)
{
	auto &i = braceAlgorithmArgumentIndex[algorithm_];
	auto &arguments = braceAlgorithmArguments[algorithm_];

	if (i >= arguments.size() || arguments[i] != argument_)
	{
		auto it = arguments.begin();

		for (Size j = 0; j < i; ++j)
		{
			++it;
		}

		arguments.insert(it, argument_);
	}

	++i;
}
Nu::Vector<Nu::Reference<Nu::Parsing4::Argument>> Nu::Parsing4::Context::GetArguments(const Reference<Algorithms::Brace>& algorithm_)
{
	auto it = braceAlgorithmArguments.find(algorithm_);

	if (it != braceAlgorithmArguments.end())
	{
		return (*it).second;
	}
	else
	{
		throw Exception();
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
	else if (auto forwardAccessScope = UpCast<Scopes::ForwardAccessScope>(target_))
	{
		auto &markers = forwardAccessScope->GetMarkers();

		auto getEntry = [&]()
		{
			auto last = fromScope_;
			auto parent = GetParent(last);

			while (parent != target_)
			{
				last = parent;
				parent = GetParent(parent);
			}

			return last;
		};
		auto getEntryIt = [&]()
		{
			auto entry = getEntry();

			if (auto sequence = UpCast<Scopes::Sequence>(entry))
			{
				for (auto it = markers.begin(); it != markers.end(); ++it)
				{
					auto marker = *it;

					if (auto sequenceReference = UpCast<Markers::SequenceReference>(marker))
					{
						if (sequenceReference->GetSequence() == sequence)
						{
							return it;
						}
					}
				}
			}

			throw NotImplementedException();
		};

		auto lastIt = (fromScope_ == target_) ? fromIt_ :
			IsChild(fromScope_, target_) ? getEntryIt() :
			markers.begin();

		UnorderedNames names;

		for (auto it = markers.begin(); it != lastIt; ++it)
		{
			auto &marker = *it;	

			if (auto declaration = UpCast<Markers::Declaration>(marker))
			{
				auto value = declaration->GetValue();

				names[value].push_front(declaration);
			}
		}

		return Move(names);
	}
	else if (auto emptyAccessScope = UpCast<Scopes::EmptyAccessScope>(target_))
	{
		return UnorderedNames();
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
	else
	{
		auto ownNames = GetOwnNames(target_, fromScope_, fromIt_);
		auto parent = GetParent(target_);
		auto parentNames = GetNames(parent, fromScope_, fromIt_);
		auto names = MergeNames(ownNames, parentNames);
		
		return Move(names);
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

	std::sort(ordered.begin(), ordered.end(), [](
		const Pair<String, Vector<Reference<Markers::Declaration>>>& a, 
		const Pair<String, Vector<Reference<Markers::Declaration>>>& b
	)
	{
		return a.first.length() > b.first.length();
	});
	
	return Move(ordered);
}

void Nu::Parsing4::Context::SetPosition(const Reference<MarkersContainer>& markersContainer_, It* it_)
{
	currentPosition[markersContainer_] = it_;
}
void Nu::Parsing4::Context::ResetPosition(const Reference<MarkersContainer>& markersContainer_)
{
	currentPosition.erase(markersContainer_);
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
bool Nu::Parsing4::Context::IsPendingToParse(const Reference<Scope>& scope_) const
{
	auto it = std::find(pendingToParse.begin(), pendingToParse.end(), scope_);

	return it != pendingToParse.end();
}
bool Nu::Parsing4::Context::IsInterfaceComplete(const Reference<Scopes::AlgorithmicScope>& algorithmic_)
{
	if (!IsPendingToParse(algorithmic_)) // interface is declared
	{
		auto algorithms = GetAlgorithms(algorithmic_);

		for (auto &algorithm : algorithms)
		{
			if (IsPendingToParse(algorithm))
			{
				return false;
			}
		}

		return true;
	}

	return false;
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
Nu::Reference<Nu::Parsing4::Markers::SequenceReference> Nu::Parsing4::Parser::Convert(const Reference<Markers::Group>& group_, const Reference<Context>& context_)
{
	auto &markers = group_->GetMarkers();
	
	MarkersContainer::Markers newMarkers;

	for (auto &marker : markers)
	{
		if (auto group = UpCast<Markers::Group>(marker))
		{
			auto sequenceReference = Convert(group, context_);

			newMarkers.push_back(sequenceReference);
		}
		else
		{
			newMarkers.push_back(marker);
		}
	}

	auto sequence = Make<Scopes::Sequence>(group_->GetOpening(), group_->GetClosing(), newMarkers);

	for (auto &marker : newMarkers)
	{
		if (auto sequenceReference = UpCast<Markers::SequenceReference>(marker))
		{
			context_->SetParent(sequenceReference->GetSequence(), sequence);
		}
	}

	auto reference = Make<Markers::SequenceReference>(sequence);

	return reference;
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
									// // TODO: splice
									// throw NotImplementedException();
									
									auto markers = Data();
									{
										markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(nameValue)));
										markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(value.substr(nameValue.size()))));
									}

									throw MarkersReplaceRequired(o, it_, markers);
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
						// // TODO: splice
						// throw NotImplementedException();

						auto markers = Data();
						{
							markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(nameValue)));
							markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(value.substr(nameValue.size()))));
						}

						throw MarkersReplaceRequired(o, it_, markers);
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
Nu::Reference<Nu::Parsing4::Unit> Nu::Parsing4::Parser::ParseNamed(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto name = ParseName(data_, it_, scope_))
	{
		auto unit = name->GetUnit();

		if (unit)
		{
			return unit;
		}
		else
		{
			SkipUntilDeclaration(data_, it_, o);
		}
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

Nu::Reference<Nu::Parsing4::Algorithms::Brace> Nu::Parsing4::Parser::ExtractBraceAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, algorithmicScope_, Keyword::Value::Algorithm))
	{
		if (auto resultType = ParseSchema(data_, it_, algorithmicScope_))
		{
			if (auto group = ParseMarker<Markers::Group>(data_, it_))
			{
				auto &markers = group->GetMarkers();

				auto braceAlgorithm = Make<Algorithms::Brace>(group->GetOpening(), group->GetClosing(), resultType, Move(markers));
				{
					context->isChanged = true;

					context->SetParent(braceAlgorithm, algorithmicScope_);
					context->AddToPendingToParse(braceAlgorithm);
					context->AddAlgorithm(algorithmicScope_, braceAlgorithm);
				}

				return Move(braceAlgorithm);
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
Nu::Reference<Nu::Parsing4::Markers::AlgorithmDeclaration> Nu::Parsing4::Parser::ParseAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_)
{
	auto o = it_;

	if (auto algorithmDeclaration = ParseMarker<Markers::AlgorithmDeclaration>(data_, it_))
	{
		return algorithmDeclaration;
	}
	else if (auto extracted = ExtractBraceAlgorithmDeclaration(data_, it_, algorithmicScope_))
	{
		auto newAlgorithmDeclaration = Make<Markers::AlgorithmDeclaration>(extracted);

		MarkersContainer::Markers markers;
		{
			markers.push_back(newAlgorithmDeclaration);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::AlgorithmDeclaration> Nu::Parsing4::Parser::ParseFullAlgorithmDeclaration(Data& data_, It& it_, const Reference<Scopes::AlgorithmicScope>& algorithmicScope_)
{
	auto o = it_;

	if (auto algorithmDeclaration = ParseAlgorithmDeclaration(data_, it_, algorithmicScope_))
	{
		auto algorithm = algorithmDeclaration->GetAlgorithm();

		if (auto delimiter = ParseMarker<Markers::Delimiter>(data_, it_))
		{
			return Move(algorithmDeclaration);
		}
		else if (auto bodyDeclaration = ParseBodyDeclaration(data_, it_, algorithm, algorithmicScope_))
		{
			auto body = bodyDeclaration->GetBody();

			context->SetParent(body, algorithm);
			context->SetBody(algorithm, body);

			return Move(algorithmDeclaration);
		}
		else
		{
			throw Exception(); // TODO
		}

		return algorithmDeclaration;
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Scopes::Body> Nu::Parsing4::Parser::ExtractBodyDeclaration(Data& data_, It& it_, const Reference<Algorithm>& algorithm_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, scope_, Keyword::Value::Body))
	{
		if (auto group = ParseMarker<Markers::Group>(data_, it_))
		{
			if (group->GetOpening() == Markers::Group::BraceType::Figure && group->GetClosing() == Markers::Group::BraceType::Figure)
			{
				auto &markers = group->GetMarkers();
				{
					for (auto it = markers.begin(); it != markers.end(); ++it)
					{
						auto &marker = *it;

						if (auto group = UpCast<Markers::Group>(marker))
						{
							auto sequenceReference = Convert(group, context);

							marker = sequenceReference;
						}
					}
				}
				auto body = Make<Scopes::Body>(Move(markers));
				{
					for (auto &marker : body->GetMarkers())
					{
						if (auto sequenceReference = UpCast<Markers::SequenceReference>(marker))
						{
							context->SetParent(sequenceReference->GetSequence(), body);
						}
					}

					context->SetParent(body, algorithm_);
					context->AddToPendingToParse(body);

					context->isChanged = true;
				}

				return Move(body);
			}
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Markers::BodyDeclaration> Nu::Parsing4::Parser::ParseBodyDeclaration(Data& data_, It& it_, const Reference<Algorithm>& algorithm_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto bodyDeclaration = ParseMarker<Markers::BodyDeclaration>(data_, it_))
	{
		return bodyDeclaration;
	}
	else if (auto extracted = ExtractBodyDeclaration(data_, it_, algorithm_, scope_))
	{
		auto newBodyDeclaration = Make<Markers::BodyDeclaration>(extracted);

		MarkersContainer::Markers markers;
		{
			markers.push_back(newBodyDeclaration);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Arguments::CopyInstance> Nu::Parsing4::Parser::ExtractCopyInstanceArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, algorithm_, Keyword::Value::Copy))
	{
		if (auto schema = ParseNamed<Scopes::Schema>(data_, it_, algorithm_))
		{
			auto instance = Make<Scopes::Instance>();
			{
				context->SetParent(instance, algorithm_);
				context->SetSchema(instance, schema);
			}
			auto argument = Make<Arguments::CopyInstance>(instance);

			return Move(argument);
		}
		else
		{
			throw NotImplementedException();
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Arguments::CopyInstance> Nu::Parsing4::Parser::ParseCopyInstanceArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_)
{
	auto o = it_;

	if (auto marker = ParseMarker<Arguments::CopyInstance>(data_, it_))
	{
		return marker;
	}
	else if (auto extracted = ExtractCopyInstanceArgument(data_, it_, algorithm_))
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
Nu::Reference<Nu::Parsing4::Argument> Nu::Parsing4::Parser::ParseArgument(Data& data_, It& it_, const Reference<Algorithm>& algorithm_)
{
	auto o = it_;

	if (auto copy = ParseCopyInstanceArgument(data_, it_, algorithm_))
	{
		return copy;
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Commands::CreateInstance> Nu::Parsing4::Parser::ExtractCreateInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, body_, Keyword::Value::Make))
	{
		if (auto schema = ParseNamed<Scopes::Schema>(data_, it_, body_))
		{
			auto instance = Make<Scopes::Instance>();
			{
				context->SetParent(instance, body_);
				context->SetSchema(instance, schema);
			}
			auto command = Make<Commands::CreateInstance>(instance);

			return Move(command);
		}
		else
		{
			throw NotImplementedException();
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Commands::CreateInstance> Nu::Parsing4::Parser::ParseCreateInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_)
{
	auto o = it_;

	if (auto marker = ParseMarker<Commands::CreateInstance>(data_, it_))
	{
		return marker;
	}
	else if (auto extracted = ExtractCreateInstanceCommand(data_, it_, body_))
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

Nu::Reference<Nu::Parsing4::Commands::ReturnInstance> Nu::Parsing4::Parser::ExtractReturnInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, body_, Keyword::Value::Return))
	{
		if (auto instance = ParseNamed<Scopes::Instance>(data_, it_, body_))
		{
			auto command = Make<Commands::ReturnInstance>(instance); // TODO: check if results types mathes

			return Move(command);
		}
		else
		{
			throw NotImplementedException();
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Commands::ReturnInstance> Nu::Parsing4::Parser::ParseReturnInstanceCommand(Data& data_, It& it_, const Reference<Scopes::Body>& body_)
{
	auto o = it_;

	if (auto marker = ParseMarker<Commands::ReturnInstance>(data_, it_))
	{
		return marker;
	}
	else if (auto extracted = ExtractReturnInstanceCommand(data_, it_, body_))
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

Nu::Reference<Nu::Pair<Nu::Reference<Nu::Parsing4::Scopes::Sequence>, Nu::Parsing4::Commands::BraceAlgorithmCall::Arguments>> Nu::Parsing4::Parser::ParseBraceAlgorithmCallArguments(Data& data_, It& it_, const Reference<Scope>& body_)
{
	auto o = it_;

	// if (auto group = ParseMarker<Markers::Group>(data_, it_))
	if (auto sequence = ParseSequence(data_, it_, body_))
	{
		auto &markers = sequence->GetMarkers();

		bool isChanged = false;
		bool isSkipped = false;

	begin:
		auto it = markers.begin();

		Commands::BraceAlgorithmCall::Arguments arguments;

		context->SetPosition(sequence, &it);

		while (it != markers.end())
		{
			try
			{
				if (!arguments.empty())
				{
					if (auto comma = ParseSpecialToken<Lexing2::Special::Value::Comma>(markers, it))
					{
						// do nothing
					}
					else
					{
						throw Exception(); // TODO
					}
				}

				if (auto namedInstance = ParseNamed<Scopes::Instance>(markers, it, sequence))
				{
					auto argument = Make<Commands::Arguments::CopyInstance>(namedInstance);
						
					arguments.push_back(argument);
				}
				else if (auto call = ParseAlgorithmCall(markers, it, sequence))
				{
					auto argument = Make<Commands::Arguments::CopyResultInstance>(call);

					arguments.push_back(argument);
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

				goto begin; // it = markers.begin();
			}
			catch (MarkersSkipRequired skip)
			{
				isSkipped = true;
				context->isSkipped = true;

				it = skip.end;
			}
		}

		context->ResetPosition(sequence);

		if (!isSkipped)
		{
			context->isChanged = true;

			return MakeReference<Pair<Reference<Scopes::Sequence>, Commands::BraceAlgorithmCall::Arguments>>(sequence, arguments);
		}
		else
		{
			// throw NotImplementedException(); // TODO
			SkipUntilDeclaration(data_, it_, o);
		}
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Commands::BraceAlgorithmCall> Nu::Parsing4::Parser::ExtractBraceAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_)
{
	auto o = it_;

	auto isArgumentsMatch = [this](const Reference<Algorithms::Brace>& algorithm_, const Reference<Pair<Reference<Scopes::Sequence>, Commands::BraceAlgorithmCall::Arguments>> arguments_) -> bool
	{
		if (algorithm_->GetOpening() == arguments_->first->GetOpening() && algorithm_->GetClosing() == arguments_->first->GetClosing())
		{
			auto arguments = context->GetArguments(algorithm_);
			
			if (arguments.size() == arguments_->second.size())
			{
				for (Size i = 0; i < arguments.size(); ++i)
				{
					auto &expected = arguments[i];
					auto &actual = arguments_->second[i];

					if (auto expectedCopy = UpCast<Arguments::CopyInstance>(expected))
					{
						if (auto actualCopy = UpCast<Commands::Arguments::CopyInstance>(actual))
						{
							auto expectedSchema = context->GetSchema(expectedCopy->GetInstance());
							auto actualSchema = context->GetSchema(actualCopy->GetInstance());

							if (expectedSchema != actualSchema)
							{
								return false;
							}
						}
						else
						{
							throw NotImplementedException();
						}
					}
					else
					{
						throw NotImplementedException();
					}
				}

				return true;
			}
		}

		return false;
	};

	if (auto unit = ParseNamed(data_, it_, body_))
	{
		if (auto algorithmic = UpCast<AlgorithmsContainer>(unit))
		{
			if (auto actualArguments = ParseBraceAlgorithmCallArguments(data_, it_, body_))
			{
				if (auto space = UpCast<Scopes::Space>(algorithmic))
				{
					if (context->IsInterfaceComplete(space)) // interface is declared
					{
						auto algorithms = context->GetAlgorithms(space);

						for (auto &algorithm : algorithms)
						{
							if (auto braceAlgorithm = UpCast<Algorithms::Brace>(algorithm))
							{
								if (isArgumentsMatch(braceAlgorithm, actualArguments))
								{
									auto result = Make<Scopes::Instance>();
									{
										context->SetParent(result, body_);
										context->SetSchema(result, braceAlgorithm->GetResult());
									}

									auto call = Make<Commands::BraceAlgorithmCall>(actualArguments->second, braceAlgorithm, result);

									MarkersContainer::Markers markers;
									{
										markers.push_back(call);
									}

									throw MarkersReplaceRequired(o, it_, markers);
								}
							}
						}

						throw Exception(); // TODO
					}
					else
					{
						// TODO: skip
						throw MarkersSkipRequired(o, it_);
					}
				}
				else
				{
					throw NotImplementedException(); // TODO
				}
			}
			else
			{
				// not algorithm call
			}
		}
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Commands::BraceAlgorithmCall> Nu::Parsing4::Parser::ParseBraceAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_)
{
	auto o = it_;

	if (auto marker = ParseMarker<Commands::BraceAlgorithmCall>(data_, it_))
	{
		return marker;
	}
	else if (auto extracted = ExtractBraceAlgorithmCall(data_, it_, body_))
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
Nu::Reference<Nu::Parsing4::Commands::AlgorithmCall> Nu::Parsing4::Parser::ParseAlgorithmCall(Data& data_, It& it_, const Reference<Scope>& body_)
{
	auto o = it_;

	if (auto brace = ParseBraceAlgorithmCall(data_, it_, body_))
	{
		return brace;
	}

	it_ = o;
	return nullptr;
}

Nu::Reference<Nu::Parsing4::Scopes::Sequence> Nu::Parsing4::Parser::ExtractSequence(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto group = ParseMarker<Markers::Group>(data_, it_))
	{
		auto &markers = group->GetMarkers();
		auto sequence = Make<Scopes::Sequence>(group->GetOpening(), group->GetClosing(), Move(markers));
		{
			context->SetParent(sequence, scope_);
			context->AddToPendingToParse(sequence);
		}

		return Move(sequence);
	}

	it_ = o;
	return nullptr;
}
Nu::Reference<Nu::Parsing4::Scopes::Sequence> Nu::Parsing4::Parser::ParseSequence(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto marker = ParseMarker<Markers::SequenceReference>(data_, it_))
	{
		auto sequence = marker->GetSequence();

		return sequence;
	}
	else if (auto extracted = ExtractSequence(data_, it_, scope_))
	{
		auto marker = Make<Markers::SequenceReference>(extracted);

		MarkersContainer::Markers markers;
		{
			markers.push_back(marker);
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

void Nu::Parsing4::Parser::ParseContent(const Reference<Scopes::Root>& root_)
{
	auto &markers = root_->GetMarkers();
	auto it = markers.begin();

	context->SetPosition(root_, &it);

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
			else if (auto spaceDeclaration = ParseSpaceDeclaration(markers, it, root_))
			{
				// do nothing
			}
			else if (auto schemaDeclaration = ParseSchemaDeclaration(markers, it, root_))
			{
				// do nothing
			}
			else if (auto declaration = ParseMarker<Markers::Declaration>(markers, it))
			{
				if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
				{
					throw NotImplementedException(); // TODO: should we support this?
				}
				else if (auto space = ParseSpace(markers, it, root_))
				{
					context->SetValue(declaration, space);
				}
				else if (auto schema = ParseSchema(markers, it, root_))
				{
					context->SetValue(declaration, schema);
				}
				else if (auto keyword = ParseKeyword(markers, it, root_))
				{
					context->SetValue(declaration, keyword);
				}
				else if (auto unit = ParseNamed(markers, it, root_))
				{
					context->SetValue(declaration, unit);
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

			markers.insert(i, replace.markers.begin(), replace.markers.end());

			it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isSkipped = true;
			context->isSkipped = true;

			it = skip.end;
		}
	}

	context->ResetPosition(root_);

	if (!isSkipped)
	{
		context->RemoveFromPendingToParse(root_);
		context->isChanged = true;
	}
}
void Nu::Parsing4::Parser::ParseContent(const Reference<Scopes::Space>& space_)
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
			else if (auto algorithmDeclaration = ParseFullAlgorithmDeclaration(markers, it, space_))
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
				else if (auto unit = ParseNamed(markers, it, space_))
				{
					context->SetValue(declaration, unit);
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

			markers.insert(i, replace.markers.begin(), replace.markers.end());

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
		context->isChanged = true;
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

			markers.insert(i, replace.markers.begin(), replace.markers.end());

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
		context->isChanged = true;
	}
}
void Nu::Parsing4::Parser::ParseContent(const Reference<Algorithms::Brace>& algorithm_)
{
	auto &markers = algorithm_->GetMarkers();
	auto it = markers.begin();

	context->SetPosition(algorithm_, &it);

	bool isChanged = false;
	bool isSkipped = false;

begin:
	it = markers.begin();
	context->FlushBraceAlgorithmArguments(algorithm_);
	Size argumentsCount = 0;
	
	while (it != markers.end())
	{
		try
		{
			if (argumentsCount > 0)
			{
				if (auto comma = ParseSpecialToken<Lexing2::Special::Value::Comma>(markers, it))
				{
					// do nothing
				}
				else
				{
					throw Exception();
				}
			}

			if (auto argument = ParseArgument(markers, it, algorithm_))
			{
				context->SetBraceAlgorithmArgument(algorithm_, argument);
				
				++argumentsCount;
			}
			else if (auto declaration = ParseMarker<Markers::Declaration>(markers, it))
			{
				if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
				{
					throw NotImplementedException(); // TODO: should we support this?
				}
				else if (auto argument = ParseArgument(markers, it, algorithm_))
				{
					context->SetBraceAlgorithmArgument(algorithm_, argument);
					
					++argumentsCount;

					if (auto copyArgument = UpCast<Arguments::CopyInstance>(argument))
					{
						auto instance = copyArgument->GetInstance();

						context->SetValue(declaration, instance);
					}
					else
					{
						throw Exception();
					}
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

			markers.insert(i, replace.markers.begin(), replace.markers.end());

			goto begin; // it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isSkipped = true;
			context->isSkipped = true;

			it = skip.end;
		}
	}

	context->ResetPosition(algorithm_);

	if (!isSkipped)
	{
		context->RemoveFromPendingToParse(algorithm_);
		context->isChanged = true;
	}
}
void Nu::Parsing4::Parser::ParseContent(const Reference<Scopes::Body>& body_)
{
	auto &markers = body_->GetMarkers();
	auto it = markers.begin();

	context->SetPosition(body_, &it);

	bool isChanged = false;
	bool isSkipped = false;

	while (it != markers.end())
	{
		try
		{
			auto o = it;

			if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
			{
				// do nothing
			}
			else if (auto createInstance = ParseCreateInstanceCommand(markers, it, body_))
			{
				// do nothing
			}
			else if (auto returnInstance = ParseReturnInstanceCommand(markers, it, body_))
			{
				// do nothing
			}
			else if (auto declaration = ParseMarker<Markers::Declaration>(markers, it))
			{
				if (auto delimiter = ParseMarker<Markers::Delimiter>(markers, it))
				{
					throw NotImplementedException(); // TODO: should we support this?
				}
				else if (auto createInstance = ParseCreateInstanceCommand(markers, it, body_))
				{
					auto instance = createInstance->GetInstance();

					context->SetValue(declaration, instance);
				}
				else if (auto call = ParseAlgorithmCall(markers, it, body_))
				{
					auto instance = call->GetResult();
					
					context->SetValue(declaration, instance);
				}
				else if (auto keyword = ParseKeyword(markers, it, body_))
				{
					context->SetValue(declaration, keyword);
				}
				else if (auto unit = ParseNamed(markers, it, body_))
				{
					context->SetValue(declaration, unit);
				}
				else
				{
					throw Exception(); // TODO
				}
			}
			else if (auto call = ParseAlgorithmCall(markers, it, body_))
			{
				// do nothing
			}
			/*else if (auto call = ParseMarker<Commands::AlgorithmCall>(markers, it))
			{
				// do nothing
			}
			else if (auto unit = ParseNamed(markers, it, body_))
			{
				if (auto algorithmic = UpCast<AlgorithmsContainer>(unit))
				{
					if (auto group = ParseMarker<Markers::Group>(markers, it))
					{
						if (auto space = UpCast<Scopes::Space>(algorithmic))
						{
							if (context->IsInterfaceComplete(space)) // interface is declared
							{
								auto algorithms = context->GetAlgorithms(space);

								for (auto &algorithm : algorithms)
								{
									if (auto braceAlgorithm = UpCast<Algorithms::Brace>(algorithm))
									{
										if (braceAlgorithm->GetOpening() == group->GetOpening() && braceAlgorithm->GetClosing() == group->GetClosing())
										{
											auto result = Make<Scopes::Instance>();
											{
												context->SetParent(result, body_);
											}

											auto call = Make<Commands::AlgorithmCall>(braceAlgorithm, result);

											MarkersContainer::Markers markers;
											{
												markers.push_back(call);
											}

											throw MarkersReplaceRequired(o, it, markers);
										}
									}
								}

								throw Exception(); // TODO
							}
							else
							{
								// TODO: skip
								throw MarkersSkipRequired(o, it);
							}
						}
						else
						{
							throw Exception(); // TODO
						}
					}
				}
				else
				{
					throw Exception();
				}
				
				// do nothing
			}*/
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

			markers.insert(i, replace.markers.begin(), replace.markers.end());

			it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isSkipped = true;
			context->isSkipped = true;

			it = skip.end;
		}
	}

	context->ResetPosition(body_);

	if (!isSkipped)
	{
		context->RemoveFromPendingToParse(body_);
		context->isChanged = true;
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
		context->SetParent(outer, nullptr);
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
			auto toParse = pending; // copy

			context->isSkipped = false;
			context->isChanged = false;

			for (auto &scope : toParse)
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
				else if (auto braceAlgorithm = UpCast<Algorithms::Brace>(scope))
				{
					ParseContent(braceAlgorithm);
				}
				else if (auto body = UpCast<Scopes::Body>(scope))
				{
					ParseContent(body);
				}
				/*else if (auto sequence = UpCast<Scopes::Sequence>(scope))
				{
					ParseContent(sequence);
				}*/
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




















