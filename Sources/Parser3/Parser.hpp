#pragma once

#pragma region Include

#include "Header.hpp"

#include <../Lexer2/Lexer.hpp>

#pragma endregion


namespace Nu
{
	namespace Parsing3
	{
		class Marker;
		class MarkersContainer;
		class Name;
		class Scope;
		class ParenthoodManager;
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
			public Marker
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
			Map<Reference<Name>, Reference<Unit>> valueLookup;
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
			inline Reference<Unit> GetValue(const Reference<Name>& name_) const;
			inline void SetValue(const Reference<Name>& name_, const Reference<Unit>& unit_);
		};
		class Parser:
			public Entity
		{
		public:
			using Input = Lexing2::Lexer::Output;
			// TODO // using Output = Reference<Root>;
		protected:
			using Data = MarkersContainer::Markers;
			using It = Data::iterator;
		public:
			class MarkersDivisionRequired;
			class MarkersSkipRequired;
		public:
			template<class T> inline static Reference<T> ParseMarker(Data& data_, It& it_);
			template<class T> inline static Reference<T> ParseToken(Data& data_, It& it_);
			inline static Reference<Name> ExtractName(Data& data_, It& it_, const Reference<Scope>& scope_, const Reference<ParenthoodManager>& parenthoodManager_);
		public:
			inline Parser() = delete;
			inline Parser(const Reference<Parser>& this_);
			inline Parser(const Parser&) = delete;
			virtual ~Parser() override = default;
		public:
			inline Parser& operator = (const Parser&) = delete;
		};
		class Parser::MarkersDivisionRequired
		{
		public:
			const It begin;
			const It end;
			const Data markers;
		public:
			inline MarkersDivisionRequired(const It& begin_, const It& end_, const Data& markers_);
		};
		class Parser::MarkersSkipRequired
		{
		public:
			const It begin;
			const It end;
		public:
			inline MarkersSkipRequired(const It& begin_, const It& end_);
		};
	}
}


#pragma region Nu

#pragma region Parsing3

#pragma region Marker

inline Nu::Parsing3::Marker::Marker(const Reference<Marker>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma region Markers

#pragma region Token

inline Nu::Parsing3::Markers::Token::Token(const Reference<Token>& this_, const Value& value_):
	Marker(this_),
	value(value_)
{
}

inline Nu::Parsing3::Markers::Token::Value Nu::Parsing3::Markers::Token::GetValue() const
{
	return value;
}

#pragma endregion

#pragma endregion

#pragma region MarkersContainer

inline Nu::Parsing3::MarkersContainer::MarkersContainer(const Reference<MarkersContainer>& this_, const Markers& markers_):
	Entity(this_),
	markers(markers_)
{
}

inline Nu::Parsing3::MarkersContainer::Markers& Nu::Parsing3::MarkersContainer::GetMarkers()
{
	return markers;
}

#pragma endregion

#pragma region Name

inline Nu::Parsing3::Name::Name(const Reference<Name>& this_):
	Marker(this_)
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
inline Nu::Reference<Nu::Parsing3::Unit> Nu::Parsing3::ParenthoodManager::GetValue(const Reference<Name>& name_) const
{
	auto it = valueLookup.find(name_);

	if (it != valueLookup.end())
	{
		auto value = (*it).second;

		return value;
	}
	else
	{
		return nullptr;
	}
}
inline void Nu::Parsing3::ParenthoodManager::SetValue(const Reference<Name>& name_, const Reference<Unit>& unit_)
{
	valueLookup[name_] = unit_;
}

#pragma endregion

#pragma region Parser

#pragma region MarkersDivisionRequired

inline Nu::Parsing3::Parser::MarkersDivisionRequired::MarkersDivisionRequired(const It& begin_, const It& end_, const Data& markers_):
	begin(begin_),
	end(end_),
	markers(markers_)
{
}

#pragma endregion

#pragma region MarkersSkipRequired

inline Nu::Parsing3::Parser::MarkersSkipRequired::MarkersSkipRequired(const It& begin_, const It& end_):
	begin(begin_),
	end(end_)
{
}

#pragma endregion

template<class T>
inline typename Nu::Reference<T> Nu::Parsing3::Parser::ParseMarker(Data& data_, It& it_)
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
inline typename Nu::Reference<T> Nu::Parsing3::Parser::ParseToken(Data& data_, It& it_)
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
inline Nu::Reference<Nu::Parsing3::Name> Nu::Parsing3::Parser::ExtractName(Data& data_, It& it_, const Reference<Scope>& scope_, const Reference<ParenthoodManager>& parenthoodManager_)
{
	auto o = it_;

	Size dotsCount = 0;
	{
		while (true)
		{
			if (auto specialMarker = ParseToken<Lexing2::Special>(data_, it_))
			{
				if (specialMarker->GetValue() == Lexing2::Special::Value::Dot)
				{
					++dotsCount;

					continue;
				}
			}

			break;
		}
	}

	if (auto text = ParseToken<Lexing2::Text>(data_, it_))
	{
		auto value = text->GetValue();
		auto names = parenthoodManager_->GetNames(scope_);
		auto namesByLength = Vector<Name::Value>();
		{
			for (auto &i : names)
			{
				auto &value = i.first;

				if (std::find(namesByLength.begin(), namesByLength.end(), value) == namesByLength.end())
				{
					namesByLength.push_back(value);
				}
			}

			std::sort(namesByLength.begin(), namesByLength.end(), [](const Name::Value& a, const Name::Value& b) { return a.length() > b.length(); });
		}

		for (auto &nameValue : namesByLength)
		{
			if (value.find(nameValue) == 0)
			{
				auto &levels = names[nameValue];
				auto j = levels.find(dotsCount);
				
				if (j == levels.end())
				{
					throw Exception(); // TODO
				}

				auto name = (*j).second;

				if (value.size() == nameValue.size())
				{
					auto lastName = name;

					// child chain
					while (true)
					{
						if (auto special = ParseToken<Lexing2::Special>(data_, it_))
						{
							if (special->GetValue() == Lexing2::Special::Value::Dot)
							{
								auto o2 = it_;

								if (auto text = ParseToken<Lexing2::Text>(data_, it_))
								{
									auto textValue = text->GetValue();
									auto parentUnit = parenthoodManager_->GetValue(lastName);

									if (parentUnit)
									{
										auto scope = UpCast<Scope>(parentUnit);

										if (scope)
										{
											auto names = parenthoodManager_->GetNames(scope);
											auto namesByLength = Vector<Name::Value>();
											{
												for (auto &i : names)
												{
													auto &value = i.first;

													if (std::find(namesByLength.begin(), namesByLength.end(), value) == namesByLength.end())
													{
														namesByLength.push_back(value);
													}
												}

												std::sort(namesByLength.begin(), namesByLength.end(), [](const Name::Value& a, const Name::Value& b)
												{
													return a.length() > b.length();
												});
											}

											lastName = [&]()
											{
												for (auto &nameValue : namesByLength)
												{
													if (textValue.find(nameValue) == 0)
													{
														auto &levels = names[nameValue];
														auto j = levels.find(0);

														if (j == levels.end())
														{
															throw Exception(); // TODO
														}

														auto childName = (*j).second;

														if (textValue.size() == nameValue.size())
														{
															return childName;
														}
														else
														{
															auto markers = Data();
															{
																markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(nameValue)));
																markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(textValue.substr(nameValue.size()))));
															}

															throw MarkersDivisionRequired(o2, it_, markers);
														}
													}
												}

												// no matches found
												throw Exception(); // TODO
											}();
										}
										else
										{
											throw Exception(); // TODO
										}
									}
									else
									{
										while (true)
										{
											if (auto special = ParseToken<Lexing2::Special>(data_, it_))
											{
												if (special->GetValue() == Lexing2::Special::Value::Dot)
												{
													auto o2 = it_;

													if (auto text = ParseToken<Lexing2::Text>(data_, it_))
													{
														continue;
													}
													else
													{
														throw Exception();
													}
												}
												else
												{
													break;
												}
											}
											else
											{
												break;
											}
										}

										throw MarkersSkipRequired(o2, it_);
									}
								}
								else
								{
									throw Exception(); // TODO
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}

					return lastName;
				}
				else
				{
					auto markers = Data();
					{
						markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(nameValue)));
						markers.push_back(Make<Markers::Token>(Make<Lexing2::Text>(value.substr(nameValue.size()))));
					}

					throw MarkersDivisionRequired(o, it_, markers);
				}
			}
		}

		throw Exception(); // TODO
	}

	it_ = o;
	return nullptr;
}

inline Nu::Parsing3::Parser::Parser(const Reference<Parser>& this_):
	Entity(this_)
{
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















