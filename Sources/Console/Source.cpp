#include <iostream>

#include <../Common/Header.hpp>


namespace Nu
{
	class Entity;

	namespace NamesDeclarationStage
	{
		class Entity;

		class Text;
		class Assembly;

		class Unit;
		class Scope;
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

		class Name:
			public Entity
		{
		public:
			inline Name(const Reference<Name>& this_);
			virtual ~Name() override = default;
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
			const Reference<Name> name;
		public:
			inline Declaration(const Reference<Declaration>& this_, const Reference<Name>& name_);
			virtual ~Declaration() override = default;
		public:
			inline Reference<Name> GetName() const;
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
		protected:
			Vector<Reference<Name>> names;
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
	}
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

#pragma region Name

inline Nu::NamesDeclarationStage::Name::Name(const Reference<Name>& this_):
	Entity(this_)
{
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

inline Nu::NamesDeclarationStage::Declaration::Declaration(const Reference<Declaration>& this_, const Reference<Name>& name_):
	Marker(this_),
	name(name_)
{
}

inline Nu::Reference<Nu::NamesDeclarationStage::Name> Nu::NamesDeclarationStage::Declaration::GetName() const
{
	return name;
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

	auto &name = declaration_->GetName();
	names.push_back(name);
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

#pragma endregion

#pragma endregion


void main()
{
	using namespace Nu;
	using namespace NamesDeclarationStage;

	// "a: schema { b: a; }"
	auto mainScope = Make<Scope>(nullptr); // implicit outer scope
	{
		auto name = Make<Name>();
		auto declaration = Make<Declaration>(name); // representation of "a:"
		mainScope->Assembly::Add(declaration);

		auto value = "schema";
		auto text = Make<Text>(value); // representation of "schema"
		mainScope->Add(text);

		auto scope = Make<Scope>(mainScope); // representation of "{ b: a; }"
		{
			auto nestedName = Make<Name>();
			auto nestedDeclaration = Make<Declaration>(nestedName); //representation of "b:"
			scope->Add(nestedDeclaration);

			auto nestedValue = "a;";
			auto nestedText = Make<Text>(nestedValue); // representation of "a;"
			scope->Add(nestedText);
		}
		mainScope->Add(scope);
	}

	std::system("pause");
}


#pragma region
#pragma endregion
