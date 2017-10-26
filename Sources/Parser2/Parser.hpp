#pragma once

#pragma region Include

#include "Header.hpp"

#include <../Lexer2/Lexer.hpp>

#pragma endregion


namespace Nu
{
	namespace Parsing2
	{
		class Marker;
		namespace Markers
		{
			class Delimiter;
			class Token; // Intermediate
			class DeclarationHeader; // Intermediate
			class Declaration;
		}
		class MarkersContainer; // Abstract
		class Name;
		class Unit;
		class Keyword;
		class Scope;
		class Space;
		class Parser;

		class Marker:
			public Entity
		{
		public:
			inline Marker() = delete;
			inline Marker(const Reference<Marker>& this_);
			inline Marker(const Marker&) = delete;
			virtual ~Marker() override = default;
		public:
			inline Marker& operator = (const Marker&) = delete;
		};
		namespace Markers
		{
			class Delimiter:
				public Marker
			{
			public:
				inline Delimiter() = delete;
				inline Delimiter(const Reference<Delimiter>& this_);
				inline Delimiter(const Delimiter&) = delete;
				virtual ~Delimiter() override = default;
			public:
				inline Delimiter& operator = (const Delimiter&) = delete;
			};
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
				virtual ~Token() override = default;
			public:
				inline Token& operator = (const Token&) = delete;
			public:
				inline Value GetValue() const;
			};
			class DeclarationHeader:
				public Marker
			{
			protected:
				const Reference<Name> name;
			public:
				inline DeclarationHeader() = delete;
				inline DeclarationHeader(const Reference<DeclarationHeader>& this_, const Reference<Name>& name_);
				inline DeclarationHeader(const DeclarationHeader&) = delete;
				virtual ~DeclarationHeader() override = default;
			public:
				inline DeclarationHeader& operator = (const DeclarationHeader&) = delete;
			public:
				inline Reference<Name> GetName() const;
			};
			class Declaration:
				public DeclarationHeader
			{
			protected:
				const Reference<Unit> unit;
			public:
				inline Declaration() = delete;
				inline Declaration(const Reference<Declaration>& this_, const Reference<Name>& name_, const Reference<Unit>& unit_);
				inline Declaration(const Declaration&) = delete;
				virtual ~Declaration() override = default;
			public:
				inline Declaration& operator = (const Declaration&) = delete;
			public:
				inline Reference<Unit> GetUnit() const;
			};
		}
		class MarkersContainer:
			public Entity
		{
		public:
			using Markers = List<Reference<Marker>>;
		protected:
			Markers markers;
		public:
			inline MarkersContainer() = delete;
			inline MarkersContainer(const Reference<MarkersContainer>& this_, const Markers& markers_ = Markers());
			inline MarkersContainer(const MarkersContainer&) = delete;
			virtual ~MarkersContainer() override = default;
		public:
			inline MarkersContainer& operator = (const MarkersContainer&) = delete;
		public:
			inline Markers& GetMarkers();
		};
		class Name:
			public Entity,
			public Marker
		{
		public:
			using Value = String;
		protected:
			const Value value;
		public:
			inline Name() = delete;
			inline Name(const Reference<Name>& this_, const Value& value_);
			inline Name(const Name&) = delete;
			virtual ~Name() override = default;
		public:
			inline Name& operator = (const Name&) = delete;
		public:
			inline Value GetValue() const;
		};
		class Unit:
			public Entity
		{
		public:
			inline Unit() = delete;
			inline Unit(const Reference<Unit>& this_);
			inline Unit(const Unit&) = delete;
			virtual ~Unit() override = default;
		public:
			inline Unit& operator = (const Unit&) = delete;
		};
		class Keyword:
			public Unit
		{
		public:
			inline Keyword() = delete;
			inline Keyword(const Reference<Keyword>& this_);
			inline Keyword(const Keyword&) = delete;
			virtual ~Keyword() override = default;
		public:
			inline Keyword& operator = (const Keyword&) = delete;
		};
		class Scope:
			public Unit,
			public MarkersContainer
		{
		public:
			using Names = List<Reference<Name>>;
			using Values = Map<Reference<Name>, Reference<Unit>>;
		protected:
			Names names;
			Values values;
		public:
			inline Scope() = delete;
			inline Scope(const Reference<Scope>& this_, const Markers& markers_ = Markers());
			inline Scope(const Scope&) = delete;
			virtual ~Scope() override = default;
		public:
			inline Scope& operator = (const Scope&) = delete;
		public:
			inline Names& GetNames();
			inline Values& GetValues();
		};
		class Root:
			public Scope
		{
		public:
			inline Root() = delete;
			inline Root(const Reference<Root>& this_, const Markers& markers_ = Markers());
			inline Root(const Root&) = delete;
			virtual ~Root() override = default;
		public:
			inline Root& operator = (const Root&) = delete;
		};
		class Space:
			public Scope
		{
		public:
			inline Space() = delete;
			inline Space(const Reference<Space>& this_);
			inline Space(const Space&) = delete;
			virtual ~Space() override = default;
		public:
			inline Space& operator = (const Space&) = delete;
		};
		class Parser:
			public Entity
		{
		public:
			using Input = Lexing2::Lexer::Output;
			using Output = Reference<Root>;
		protected:
			using Data = MarkersContainer::Markers;
			using It = Data::iterator;
		protected:
			inline static Reference<Markers::Token> Convert(const Reference<Lexing2::Token>& value_);
			inline static MarkersContainer::Markers Convert(const Lexing2::Container::Tokens& source_);
			inline static Reference<MarkersContainer> Convert(const Reference<Lexing2::Container>& source_);
		protected:
			Map<Reference<Unit>, Reference<Scope>> unitsParenthood;
		public:
			inline Parser() = delete;
			inline Parser(const Reference<Parser>& this_);
			inline Parser(const Parser&) = delete;
			virtual ~Parser() override = default;
		public:
			inline Parser& operator = (const Parser&) = delete;
		protected:
			template<class T>
			inline Reference<T> ParseMarker(Data& data_, It& it_);
			template<class T>
			inline Reference<T> ParseToken(Data& data_, It& it_);
		protected:
			inline void Preparse(const Reference<Scope>& scope_);
		protected:
			inline Reference<Markers::Delimiter> ExtractDelimiter(Data& data_, It& it_);
			inline Reference<Markers::DeclarationHeader> ExtractDeclarationHeader(Data& data_, It& it_);
			inline Reference<Markers::Declaration> ExtractDeclaration(Data& data_, It& it_);
			inline Reference<Space> ExtractSpaceDeclaration(Data& data_, It& it_);
			inline Reference<Name> ExtractName(Data& data_, It& it_);
		protected:
			inline void Parse(const Reference<Scope>& scope_);
		public:
			inline Output Parse(const Input& input_);
		};
	}
}


#pragma region Nu

#pragma region Parsing2

#pragma region Marker

inline Nu::Parsing2::Marker::Marker(const Reference<Marker>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Markers

#pragma region Delimiter

inline Nu::Parsing2::Markers::Delimiter::Delimiter(const Reference<Delimiter>& this_):
	Marker(this_)
{
}

#pragma endregion

#pragma region Token

inline Nu::Parsing2::Markers::Token::Token(const Reference<Token>& this_, const Value& value_):
	Marker(this_),
	value(value_)
{
}

inline Nu::Parsing2::Markers::Token::Value Nu::Parsing2::Markers::Token::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region DeclarationHeader

inline Nu::Parsing2::Markers::DeclarationHeader::DeclarationHeader(const Reference<DeclarationHeader>& this_, const Reference<Name>& name_):
	Marker(this_),
	name(name_)
{
}

inline Nu::Reference<Nu::Parsing2::Name> Nu::Parsing2::Markers::DeclarationHeader::GetName() const
{
	return name;
}

#pragma endregion

#pragma region Declaration

inline Nu::Parsing2::Markers::Declaration::Declaration(const Reference<Declaration>& this_, const Reference<Name>& name_, const Reference<Unit>& unit_):
	DeclarationHeader(this_, name_),
	unit(unit_)
{
}

inline Nu::Reference<Nu::Parsing2::Unit> Nu::Parsing2::Markers::Declaration::GetUnit() const
{
	return unit;
}

#pragma endregion

#pragma endregion

#pragma region MarkersContainer

inline Nu::Parsing2::MarkersContainer::MarkersContainer(const Reference<MarkersContainer>& this_, const Markers& markers_):
	Entity(this_),
	markers(markers_)
{
}

inline Nu::Parsing2::MarkersContainer::Markers& Nu::Parsing2::MarkersContainer::GetMarkers()
{
	return markers;
}

#pragma endregion

#pragma region Name

inline Nu::Parsing2::Name::Name(const Reference<Name>& this_, const Value& value_):
	Entity(this_),
	Marker(this_),
	value(value_)
{
}

inline Nu::Parsing2::Name::Value Nu::Parsing2::Name::GetValue() const
{
	return value;
}

#pragma endregion

#pragma region Unit

inline Nu::Parsing2::Unit::Unit(const Reference<Unit>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Keyword

inline Nu::Parsing2::Keyword::Keyword(const Reference<Keyword>& this_):
	Unit(this_)
{
}

#pragma endregion

#pragma region Scope

inline Nu::Parsing2::Scope::Scope(const Reference<Scope>& this_, const Markers& markers_):
	Unit(this_),
	MarkersContainer(this_, markers_)
{
}

inline Nu::Parsing2::Scope::Names& Nu::Parsing2::Scope::GetNames()
{
	return names;
}
inline Nu::Parsing2::Scope::Values& Nu::Parsing2::Scope::GetValues()
{
	return values;
}

#pragma endregion

#pragma region Root

inline Nu::Parsing2::Root::Root(const Reference<Root>& this_, const Markers& markers_):
	Scope(this_, markers_)
{
}

#pragma endregion

#pragma region Space

inline Nu::Parsing2::Space::Space(const Reference<Space>& this_):
	Scope(this_)
{
}

#pragma endregion

#pragma region Parser

inline Nu::Reference<Nu::Parsing2::Markers::Token> Nu::Parsing2::Parser::Convert(const Reference<Lexing2::Token>& value_)
{
	auto token = Make<Markers::Token>(value_);

	return token;
}
inline Nu::Parsing2::MarkersContainer::Markers Nu::Parsing2::Parser::Convert(const Lexing2::Container::Tokens& source_)
{
	MarkersContainer::Markers markers;

	for (auto &rawToken : source_)
	{
		auto token = Convert(rawToken);

		markers.push_back(token);
	}

	return Move(markers);
}
inline Nu::Reference<Nu::Parsing2::MarkersContainer> Nu::Parsing2::Parser::Convert(const Reference<Lexing2::Container>& source_)
{
	auto &tokens = source_->GetTokens();
	auto markers = Move(Convert(tokens));
	auto markersContainer = Make<MarkersContainer>(markers);

	return Move(markersContainer);
}

inline Nu::Parsing2::Parser::Parser(const Reference<Parser>& this_) :
	Entity(this_)
{
}

template<class T>
inline typename Nu::Reference<T> Nu::Parsing2::Parser::ParseMarker(Data& data_, It& it_)
{
	auto o = it_;

	if (it_ != data_.end())
	{
		auto marker = *it_;

		++it_;

		if (auto casted = UpCast<T>(marker))
		{
			return casted;
		}
	}

	it_ = o;
	return nullptr;
}
template<class T>
inline typename Nu::Reference<T> Nu::Parsing2::Parser::ParseToken(Data& data_, It& it_)
{
	auto o = it_;

	if (auto token = ParseMarker<Markers::Token>(data_, it_))
	{
		auto value = token->GetValue();

		if (auto casted = UpCast<T>(value))
		{
			return casted;
		}
	}

	it_ = o;
	return nullptr;
}

inline void Nu::Parsing2::Parser::Preparse(const Reference<Scope>& scope_)
{
	auto &markers = scope_->GetMarkers();
	auto it = markers.begin();

	while (it != markers.end())
	{
		auto o = it;

		if (auto declarationHeader = ExtractDeclarationHeader(markers, it))
		{
			auto name = declarationHeader->GetName();
			auto &names = scope_->GetNames();

			names.push_back(name);

			auto i = markers.erase(o, it);

			markers.insert(i, declarationHeader);
		}
		else
		{
			++it;
		}
	}
}

inline Nu::Reference<Nu::Parsing2::Markers::Delimiter> Nu::Parsing2::Parser::ExtractDelimiter(Data& data_, It& it_)
{
	auto o = it_;

	if (auto special = ParseToken<Lexing2::Special>(data_, it_))
	{
		if (special->GetValue() == Lexing2::Special::Value::Semicolon)
		{
			auto delimiter = Make<Markers::Delimiter>();

			return delimiter;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing2::Markers::DeclarationHeader> Nu::Parsing2::Parser::ExtractDeclarationHeader(Data& data_, It& it_)
{
	auto o = it_;

	if (auto text = ParseToken<Lexing2::Text>(data_, it_))
	{
		if (auto special = ParseToken<Lexing2::Special>(data_, it_))
		{
			auto specialValue = special->GetValue();

			if (specialValue == Lexing2::Special::Value::Colon)
			{
				auto textValue = text->GetValue();
				auto name = Make<Name>(textValue);
				auto declarationHeader = Make<Markers::DeclarationHeader>(name);

				return declarationHeader;
			}
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing2::Markers::Declaration> Nu::Parsing2::Parser::ExtractDeclaration(Data& data_, It& it_)
{
	auto o = it_;

	if (auto declarationHeader = ParseMarker<Markers::DeclarationHeader>(data_, it_))
	{
		auto name = declarationHeader->GetName();

		if (auto space = ExtractSpaceDeclaration(data_, it_))
		{
			auto declaration = Make<Markers::Declaration>(name, space);

			return declaration;
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing2::Space> Nu::Parsing2::Parser::ExtractSpaceDeclaration(Data& data_, It& it_)
{
	auto o = it_;

	if (auto name = ParseMarker<Name>(data_, it_))
	{

	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing2::Name> Nu::Parsing2::Parser::ExtractName(Data& data_, It& it_)
{
	auto o = it_;

	// TODO: perform dots

	if (auto text = ParseToken<Lexing2::Text>(data_, it_))
	{
		// TODO: perform names comparisons

		auto value = text->GetValue();
		auto name = Make<Name>(value);

		return name;
	}

	it_ = o;
	return nullptr;
}

inline void Nu::Parsing2::Parser::Parse(const Reference<Scope>& scope_)
{
	auto &markers = scope_->GetMarkers();
	auto it = markers.begin();

	while (it != markers.end())
	{
		auto o = it;

		if (auto delimiter = ExtractDelimiter(markers, it))
		{
			auto i = markers.erase(o, it);

			markers.insert(i, delimiter);
		}
		if (false)
		{
			[this](Data& data_, It& it_, const Reference<Scope>& scope_)
			{
				// ..a.b.c
				// #1 extract dots count
				// #2 extract main name
				// #3 extract child names and dots
				// count 
				Size dotsCount = 0;
				{
					while (true)
					{
						if (auto tokenSpecial = ParseToken<Lexing2::Special>(data_, it_))
						{
							auto value = tokenSpecial->GetValue();

							if (value == Lexing2::Special::Value::Dot)
							{
								++dotsCount;
								continue;
							}
						}

						break;
					}
				}

				// get all names
				/*Vector<Name::Value> uniqueNamesValues;
				{
					auto scope = scope_;
					
					while (scope != nullptr)
					{
						auto &s = scope_->GetNames();

						for (auto &n : s)
						{
							auto &v = n->GetValue();

							if (std::find(uniqueNamesValues.begin(), uniqueNamesValues.end(), v) == uniqueNamesValues.end())
							{
								uniqueNamesValues.push_back(v);
							}
						}

						// go to parent
						auto i = unitsParenthood.find(scope);
						if (i != unitsParenthood.end())
						{
							scope = (*i).second;
						}
						else
						{
							scope = nullptr;
						}
					}
				}*/
			};

			// if (auto markerText = ParseToken<Lexing2::Text>(markers, it))
			// {
			// 
			// }
		}
		/*else if (auto declaration = ExtractDeclaration(markers, it))
		{
			auto i = markers.erase(o, it);

			markers.insert(i, declaration);
		}*/
		else
		{
			++it;
		}
	}
}

inline Nu::Parsing2::Parser::Output Nu::Parsing2::Parser::Parse(const Input& input_)
{
	auto root = Make<Root>();

	auto &rootNames = root->GetNames();
	auto &rootValues = root->GetValues();

	auto spaceName = Make<Name>("space");
	{
		rootNames.push_back(spaceName);

		auto spaceKeyword = Make<Keyword>(); // TODO: add type

		rootValues[spaceName] = spaceKeyword;
	}

	auto mainName = Make<Name>(".main"); // TODO: is name for entry point is necessary?
	{
		rootNames.push_back(mainName);

		auto markersContainer = Move(Convert(input_));
		auto main = Make<Root>(markersContainer->GetMarkers());
		{
			unitsParenthood[main] = root;
		}

		Preparse(main);

		while (true)
		{
			Parse(main);

			break; // TODO: condition
		}

		rootValues[mainName] = main;

		return main;
	}

	// auto markersContainer = Move(Convert(input_));
	// auto root = Make<Root>(markersContainer->GetMarkers());
	// 
	// Preparse(root);
	// 
	// // TODO: #1 Preparse, names gathering
	// // TODO: #2 Parse
	// 
	// return root;

	throw NotImplementedException();
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















