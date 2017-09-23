#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	class Name;
	class Unit;
	class Keyword;
	class Scope;
	class Translator;


	class Name:
		public Entity
	{
	public:
		using Value = String;
	public:
		inline Name() = delete;
		inline Name(const Name&) = delete;
		inline Name(const Reference<Name>& this_); // TODO: implement
		virtual ~Name() override = default;
	public:
		inline Value GetValue() const;
		inline Reference<Unit> GetUnit() const;
	};
	class Unit:
		public Entity
	{
	public:
		inline Unit() = delete;
		inline Unit(const Unit&) = delete;
		inline Unit(const Reference<Unit>& this_); // TODO: implement
		virtual ~Unit() override = default;
	};
	class Keyword:
		public Unit
	{
	public:
		enum class Type
		{
			None, // not in use

			Space,
		};
	public:
		inline Keyword() = delete;
		inline Keyword(const Keyword&) = delete;
		inline Keyword(const Reference<Keyword>& this_); // TODO: implement
		virtual ~Keyword() override = default;
	public:
		inline Type GetType() const;
	};
	class Scope:
		public Unit
	{
	public:
		using Names = Vector<Reference<Name>>;
	public:
		inline Scope() = delete;
		inline Scope(const Scope&) = delete;
		inline Scope(const Reference<Scope>& this_); // TODO: implement
		virtual ~Scope() override = default;
	public:
		inline Names GetNames() const;
	};
	class Root:
		public Scope
	{
	public:
		inline Root() = delete;
		inline Root(const Root&) = delete;
		inline Root(const Reference<Root>& this_); // TODO: implement
		virtual ~Root() override = default;
	};
	class Space:
		public Scope
	{
	public:
		inline Space() = delete;
		inline Space(const Space&) = delete;
		inline Space(const Reference<Space>& this_); // TODO: implement
		virtual ~Space() override = default;
	};
	class Translator :
		public Entity
	{
	public:
		using Input = String;
		using Output = Reference<Root>;
	public:
		inline Translator(const Reference<Translator>& this_);
	public:
		inline Output Translate(const Input& input_) const;
	};
}


#pragma region Nu

#pragma region Name

inline Nu::Name::Value Nu::Name::GetValue() const
{
	throw NotImplementedException();
}
inline Nu::Reference<Nu::Unit> Nu::Name::GetUnit() const
{
	throw NotImplementedException();
}

#pragma endregion

#pragma region Keyword

inline Nu::Keyword::Type Nu::Keyword::GetType() const
{
	throw NotImplementedException();
}

#pragma endregion

#pragma region Scope

inline Nu::Scope::Names Nu::Scope::GetNames() const
{
	throw NotImplementedException();
}

#pragma endregion

#pragma region Root

#pragma endregion

#pragma region Space

#pragma endregion

#pragma region Translator

inline Nu::Translator::Translator(const Reference<Translator>& this_):
	Entity(this_)
{
}

inline Nu::Translator::Output Nu::Translator::Translate(const Nu::Translator::Input& input_) const
{
	throw NotImplementedException();
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















