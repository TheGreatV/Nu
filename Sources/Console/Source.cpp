#include <iostream>

#include <../Common/Header.hpp>


namespace Nu
{
	class Entity;

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
	}


	class Entity:
		public This<Entity>
	{
	public:
		inline Entity(const Reference<Entity>& this_);
		virtual ~Entity() = default;
	};

	namespace NamesDeclarationStage
	{
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
			inline Marker(const Reference<Marker>& this_);
			virtual ~Marker() override = default;
		};
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
		};
		class Assembly:
			public Entity
		{
		protected:
			Vector<Reference<Marker>> markers;
		public:
			inline Assembly(const Reference<Assembly>& this_);
			virtual ~Assembly() override = default;
		public:
			virtual void Add(const Reference<Marker>& marker_);
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
		public: // protected: // temporal
			Vector<Reference<Identifier>> identifiers;
			Vector<Reference<Unit>> units;
		public:
			inline Scope(const Reference<Scope>& this_, const Reference<Scope>& scope_);
			virtual ~Scope() override = default;
		public:
			virtual void Add(const Reference<Marker>& marker_); // C++ shit workaround
			virtual void Add(const Reference<Declaration>& declaration_);
			virtual void Add(const Reference<Unit>& unit_);
			virtual void Add(const Reference<Scope>& scope_); // C++ shit workaround
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
	}
}


bool IsDigit(const char& value_)
{
	switch(value_)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
		default:
			return false;
	}
}
bool IsSmallLetter(const char& value_)
{
	switch(value_)
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			return true;
		default:
			return false;
	}
}
bool IsCapitalLetter(const char& value_)
{
	switch(value_)
	{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return true;
		default:
			return false;
	}
};
bool IsLetter(const char& value_)
{
	return
		IsSmallLetter(value_) ||
		IsCapitalLetter(value_);
}
bool IsGlyph(const char& value_)
{
	return
		IsDigit(value_) ||
		IsLetter(value_) ||
		(value_ == '_')
		;
};
bool IsSign(const char& value_)
{
	switch(value_)
	{
		case '~':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case '/':
		case '|':
		case '\\':
		case '<':
		case '>':
		case '?':
			return true;
		default:
			return false;
	}
};
bool IsSymbol(const char& value_)
{
	return
		IsGlyph(value_) ||
		IsSign(value_);
}


#pragma region Nu

#pragma region Entity

inline Nu::Entity::Entity(const Reference<Entity>& this_):
	This(this_)
{
}

#pragma endregion

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

inline Nu::NamesDeclarationStage::Assembly::Assembly(const Reference<Assembly>& this_):
	Entity(this_),
	markers()
{
}

void Nu::NamesDeclarationStage::Assembly::Add(const Reference<Marker>& marker_)
{
	markers.push_back(marker_);
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
	Assembly(this_)
{
}

void Nu::NamesDeclarationStage::Scope::Add(const Reference<Marker>& marker_)
{
	Assembly::Add(marker_);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Declaration>& declaration_)
{
	Assembly::Add(declaration_);

	auto &identifier = declaration_->GetIdentifier();
	identifiers.push_back(identifier);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Unit>& unit_)
{
	Assembly::Add(unit_);

	units.push_back(unit_);
}
void Nu::NamesDeclarationStage::Scope::Add(const Reference<Scope>& scope_)
{
	Add(Cast<Unit>(scope_));
}

#pragma endregion

#pragma region Parser

inline Nu::NamesDeclarationStage::Parser::Parser(const Reference<Parser>& this_):
	This(this_)
{
}

inline void Nu::NamesDeclarationStage::Parser::ParseScope(const Source& source_, Iterator& it_, const Reference<Scope>& scope_)
{
	while(it_ < static_cast<Iterator>(source_.length()))
	{
		auto value = source_[it_];

		if(value == ':')
		{
			auto i = it_ > 0
				? it_ - 1
				: throw Exception("Illegal \":\"");

			if(IsSymbol(source_[i]))
			{
				while(i >= 0 && IsSymbol(source_[i]))
				{
					--i;
				}
				++i;

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
		else if(value == '{')
		{
			++it_;

			auto scope = Make<Scope>(scope_);

			ParseScope(source_, it_, scope);

			scope_->Add(scope);

			continue;
		}
		else if(value == '}')
		{
			++it_;

			return;
		}

		++it_;
	}
}

inline Nu::Reference<Nu::NamesDeclarationStage::Scope> Nu::NamesDeclarationStage::Parser::Parse(const Source& source_)
{
	auto mainScope = Make<Scope>(nullptr);

	int it = 0;

	ParseScope(source_, it, mainScope);

	return mainScope;
}

#pragma endregion

#pragma endregion

#pragma endregion


void print(const Nu::Reference<Nu::NamesDeclarationStage::Scope>& scope)
{
	static int tab = 0;

	for(int t = 0; t < tab; ++t) std::cout << '\t';
	std::cout << "{" << std::endl;

	++tab;

	for(auto &i : scope->identifiers)
	{
		for(int t = 0; t < tab; ++t) std::cout << '\t';

		std::cout << i->GetValue() << std::endl;
	}

	for(auto &i : scope->units)
	{
		if(auto s = Nu::UpCast<Nu::NamesDeclarationStage::Scope>(i))
		{
			print(s);
		}
	}

	--tab;

	for(int t = 0; t < tab; ++t) std::cout << '\t';
	std::cout << "}" << std::endl;
}


void main()
{
	using namespace Nu;
	using namespace NamesDeclarationStage;

	/*
	// "a: schema { b: a; }"
	auto mainScope = Make<Scope>(nullptr); // implicit outer scope
	{
		auto identifier = Make<Identifier>();
		auto declaration = Make<Declaration>(identifier); // representation of "a:"
		mainScope->Assembly::Add(declaration);

		auto value = "schema";
		auto text = Make<Text>(value); // representation of "schema"
		mainScope->Add(text);

		auto scope = Make<Scope>(mainScope); // representation of "{ b: a; }"
		{
			auto nestedIdentifier = Make<Identifier>();
			auto nestedDeclaration = Make<Declaration>(nestedIdentifier); //representation of "b:"
			scope->Add(nestedDeclaration);

			auto nestedValue = "a;";
			auto nestedText = Make<Text>(nestedValue); // representation of "a;"
			scope->Add(nestedText);
		}
		mainScope->Add(scope);
	}
	*/

	auto parser = Make<Parser>();
	auto scope = parser->Parse("a:{x:y:z:{vasya #pupkin:}}b:");

	print(scope);

	std::system("pause");
}


#pragma region
#pragma endregion
