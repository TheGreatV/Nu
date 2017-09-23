#pragma once

#pragma region Include

#include "Header.hpp"

#include <../Lexer2/Lexer.hpp>

#pragma endregion


namespace Nu
{
	namespace Parsing3
	{
		class Name;
		class Scope;
		class ParenthoodManager;

		class Name:
			public Entity
		{
		public:
			using Value = String;
			using Level = Size;
		public:
			inline Name() = delete;
			inline Name(const Reference<Name>& this_);
			inline Name(const Name&) = delete;
			virtual ~Name() override = default;
		public:
			inline Name& operator = (const Name&) = delete;
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
		class Scope:
			public Unit
		{
		public:
			using Names = Map<Name::Value, Map<Name::Level, Reference<Name>>>;
		protected:
			Names names;
		public:
			inline Scope() = delete;
			inline Scope(const Reference<Scope>& this_);
			inline Scope(const Scope&) = delete;
			virtual ~Scope() override = default;
		public:
			inline Scope& operator = (const Scope&) = delete;
		public:
			inline Names GetNames() const;
			inline Reference<Name> Add(const Name::Value& value_);
		};
		class ParenthoodManager:
			public Entity
		{
		protected:
			Map<Reference<Unit>, Reference<Scope>> parenthoodLookup;
		public:
			inline ParenthoodManager() = delete;
			inline ParenthoodManager(const Reference<ParenthoodManager>& this_);
			inline ParenthoodManager(const ParenthoodManager&) = delete;
			virtual ~ParenthoodManager() override = default;
		public:
			inline ParenthoodManager& operator = (const ParenthoodManager&) = delete;
		public:
			inline Reference<Scope> GetParent(const Reference<Unit>& unit_) const;
			inline void SetParent(const Reference<Unit>& unit_, const Reference<Scope>& scope_);
			inline Scope::Names GetNames(const Reference<Scope>& scope_);
		};
	}
}


#pragma region Nu

#pragma region Parsing3

#pragma region Name

inline Nu::Parsing3::Name::Name(const Reference<Name>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Unit

inline Nu::Parsing3::Unit::Unit(const Reference<Unit>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Scope

inline Nu::Parsing3::Scope::Scope(const Reference<Scope>& this_):
	Unit(this_)
{
}

inline Nu::Parsing3::Scope::Names Nu::Parsing3::Scope::GetNames() const
{
	return names;
}
inline Nu::Reference<Nu::Parsing3::Name> Nu::Parsing3::Scope::Add(const Name::Value& value_)
{
	if (!value_.empty())
	{
		auto name = Make<Name>();

		auto &levels = names[value_];
		auto newLevels = Map<Name::Level, Reference<Name>>();

		newLevels[0] = name;

		for (auto &i : levels)
		{
			auto &sourceLevel = i.first;
			auto sourceName = i.second;

			newLevels[sourceLevel + 1] = sourceName;
		}

		names[value_] = newLevels;

		return name;
	}
	else
	{
		throw Exception(); // TODO
	}
}

#pragma endregion

#pragma region ParenthoodManager

inline Nu::Parsing3::ParenthoodManager::ParenthoodManager(const Reference<ParenthoodManager>& this_):
	Entity(this_)
{
}

inline Nu::Reference<Nu::Parsing3::Scope> Nu::Parsing3::ParenthoodManager::GetParent(const Reference<Unit>& unit_) const
{
	auto it = parenthoodLookup.find(unit_);

	if (it != parenthoodLookup.end())
	{
		auto parent = (*it).second;

		return parent;
	}
	else
	{
		return nullptr;
	}
}
inline void Nu::Parsing3::ParenthoodManager::SetParent(const Reference<Unit>& unit_, const Reference<Scope>& scope_)
{
	parenthoodLookup[unit_] = scope_;
}
inline Nu::Parsing3::Scope::Names Nu::Parsing3::ParenthoodManager::GetNames(const Reference<Scope>& scope_)
{
	auto names = Scope::Names();
	auto scope = scope_;

	while (scope != nullptr)
	{
		auto scopeNames = scope->GetNames();

		for (auto &i : scopeNames)
		{
			auto &value = i.first;
			auto &scopeLevels = i.second;
			auto &levels = names[value];
			auto levelDifference = levels.size();

			for (auto &j : scopeLevels)
			{
				auto level = j.first;
				auto name = j.second;

				levels[levelDifference + level] = name;
			}
		}

		scope = GetParent(scope);
	}

	return Move(names);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















