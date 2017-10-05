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
		namespace Markers
		{
			class Token;
			class DeclarationHeader;
			class Declaration;
		}
		class MarkersContainer;
		class Name;
		class Unit;
		class Keyword;
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
		class Keyword:
			public Unit
		{
		public:
			enum class Value
			{
				None,
				Space,
			};
		protected:
			const Value value;
		public:
			inline Keyword() = delete;
			inline Keyword(const Reference<Keyword>& this_, const Value& value_);
			inline Keyword(const Keyword&) = delete;
			virtual ~Keyword() override = default;
		public:
			inline Keyword& operator = (const Keyword&) = delete;
		public:
			inline Value GetValue() const;
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
		class Space:
			public Marker,
			public Scope,
			public MarkersContainer
		{
		public:
			inline Space() = delete;
			inline Space(const Reference<Space>& this_, const Markers& markers_ = Markers());
			inline Space(const Space&) = delete;
			virtual ~Space() override = default;
		public:
			inline Space& operator = (const Space&) = delete;
		};
		class Root:
			public Scope,
			public MarkersContainer
		{
		public:
			inline Root() = delete;
			inline Root(const Reference<Root>& this_, const Markers& markers_ = Markers());
			inline Root(const Root&) = delete;
			virtual ~Root() override = default;
		public:
			inline Root& operator = (const Root&) = delete;
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
			using Output = Reference<Root>;
		protected:
			using Data = MarkersContainer::Markers;
			using It = Data::iterator;
		public:
			class MarkersReplaceRequired;
			class MarkersSkipRequired;
		public:
			inline static Reference<Markers::Token> Convert(const Reference<Lexing2::Token>& value_);
			inline static MarkersContainer::Markers Convert(const Lexing2::Container::Tokens& source_);
			template<class T> inline static Reference<T> ParseMarker(Data& data_, It& it_);
			template<class T> inline static Reference<T> ParseToken(Data& data_, It& it_);
			inline static Reference<Name> ExtractName(Data& data_, It& it_, const Reference<Scope>& scope_, const Reference<ParenthoodManager>& parenthoodManager_);
		protected:
			bool isMarkerSkipped;
		public:
			const Reference<ParenthoodManager> parenthoodManager = Make<ParenthoodManager>();
		public:
			inline Parser() = delete;
			inline Parser(const Reference<Parser>& this_);
			inline Parser(const Parser&) = delete;
			virtual ~Parser() override = default;
		public:
			inline Parser& operator = (const Parser&) = delete;
		protected:
			inline Reference<Name> ParseName(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Keyword> ParseKeyword(Data& data_, It& it_, const Reference<Scope>& scope_, const Keyword::Value& value_ = Keyword::Value::None);
			inline Reference<Markers::DeclarationHeader> ExtractDeclarationHeader(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Markers::Declaration> ParseDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Space> ExtractSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline Reference<Space> ParseSpace(Data& data_, It& it_, const Reference<Scope>& scope_);
			inline void Preparse(const Reference<Root>& root_);
			inline void Parse(const Reference<Root>& root_);
		public:
			inline Output Parse(const Input& input_);
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

#pragma region DeclarationHeader

inline Nu::Parsing3::Markers::DeclarationHeader::DeclarationHeader(const Reference<DeclarationHeader>& this_, const Reference<Name>& name_):
	Marker(this_),
	name(name_)
{
}

inline Nu::Reference<Nu::Parsing3::Name> Nu::Parsing3::Markers::DeclarationHeader::GetName() const
{
	return name;
}

#pragma endregion

#pragma region Declaration

inline Nu::Parsing3::Markers::Declaration::Declaration(const Reference<Declaration>& this_, const Reference<Name>& name_, const Reference<Unit>& unit_):
	DeclarationHeader(this_, name_),
	unit(unit_)
{
}

inline Nu::Reference<Nu::Parsing3::Unit> Nu::Parsing3::Markers::Declaration::GetUnit() const
{
	return unit;
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

#pragma region Keyword

inline Nu::Parsing3::Keyword::Keyword(const Reference<Keyword>& this_, const Value& value_):
	Unit(this_),
	value(value_)
{
}

inline Nu::Parsing3::Keyword::Value Nu::Parsing3::Keyword::GetValue() const
{
	return value;
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

#pragma region Space

inline Nu::Parsing3::Space::Space(const Reference<Space>& this_, const Markers& markers_):
	Marker(this_),
	Scope(this_),
	MarkersContainer(this_, markers_)
{
}

#pragma endregion

#pragma region Root

inline Nu::Parsing3::Root::Root(const Reference<Root>& this_, const Markers& markers_):
	Scope(this_),
	MarkersContainer(this_, markers_)
{
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

#pragma region MarkersReplaceRequired

inline Nu::Parsing3::Parser::MarkersReplaceRequired::MarkersReplaceRequired(const It& begin_, const It& end_, const Data& markers_):
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

inline Nu::Reference<Nu::Parsing3::Markers::Token> Nu::Parsing3::Parser::Convert(const Reference<Lexing2::Token>& value_)
{
	auto token = Make<Markers::Token>(value_);

	return token;
}
inline Nu::Parsing3::MarkersContainer::Markers Nu::Parsing3::Parser::Convert(const Lexing2::Container::Tokens& source_)
{
	MarkersContainer::Markers markers;

	for (auto &rawToken : source_)
	{
		auto token = Convert(rawToken);

		markers.push_back(token);
	}

	return Move(markers);
}
template<class T> inline typename Nu::Reference<T> Nu::Parsing3::Parser::ParseMarker(Data& data_, It& it_)
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
template<class T> inline typename Nu::Reference<T> Nu::Parsing3::Parser::ParseToken(Data& data_, It& it_)
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

															throw MarkersReplaceRequired(o2, it_, markers);
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

					throw MarkersReplaceRequired(o, it_, markers);
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

inline Nu::Reference<Nu::Parsing3::Name> Nu::Parsing3::Parser::ParseName(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto name = ParseMarker<Name>(data_, it_))
	{
		return name;
	}
	else if (auto name = ExtractName(data_, it_, scope_, parenthoodManager))
	{
		MarkersContainer::Markers markers;
		{
			markers.push_back(name);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing3::Keyword> Nu::Parsing3::Parser::ParseKeyword(Data& data_, It& it_, const Reference<Scope>& scope_, const Keyword::Value& value_)
{
	auto o = it_;

	if (auto name = ParseName(data_, it_, scope_))
	{
		auto value = parenthoodManager->GetValue(name);

		if (auto keyword = UpCast<Keyword>(value))
		{
			if (value_ == Keyword::Value::None || keyword->GetValue() == value_)
			{
				return keyword;
			}
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing3::Markers::DeclarationHeader> Nu::Parsing3::Parser::ExtractDeclarationHeader(Data& data_, It& it_, const Reference<Scope>& scope_)
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
				auto name = scope_->Add(textValue);
				auto declarationHeader = Make<Markers::DeclarationHeader>(name);

				return declarationHeader;
			}
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing3::Markers::Declaration> Nu::Parsing3::Parser::ParseDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;
	
	if (auto declaration = ParseMarker<Markers::Declaration>(data_, it_))
	{
		return declaration;
	}
	else if (auto declarationHeader = ParseMarker<Markers::DeclarationHeader>(data_, it_))
	{
		auto declarationName = declarationHeader->GetName();

		if (auto space = ParseSpace(data_, it_, scope_))
		{
			auto declaration = Make<Markers::Declaration>(declarationName, space);

			parenthoodManager->SetValue(declarationName, space);

			MarkersContainer::Markers markers;
			{
				markers.push_back(declaration);
			}

			throw MarkersReplaceRequired(o, it_, markers);
		}
		else if (auto keyword = ParseKeyword(data_, it_, scope_))
		{
			auto declaration = Make<Markers::Declaration>(declarationName, keyword);

			parenthoodManager->SetValue(declarationName, keyword);

			MarkersContainer::Markers markers;
			{
				markers.push_back(declaration);
			}

			throw MarkersReplaceRequired(o, it_, markers);
		}
		else if (auto name = ParseName(data_, it_, scope_))
		{
			auto value = parenthoodManager->GetValue(name);

			if (value)
			{
				auto declaration = Make<Markers::Declaration>(declarationName, value);

				parenthoodManager->SetValue(declarationName, value);

				MarkersContainer::Markers markers;
				{
					markers.push_back(declaration);
				}

				throw MarkersReplaceRequired(o, it_, markers);
			}
			else
			{
				// isMarkerSkipped
				auto it = it_;

				while (it != data_.end() && !UpCast<Markers::DeclarationHeader>(*it))
				{
					++it;
				}

				throw MarkersSkipRequired(o, it);
			}
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing3::Space> Nu::Parsing3::Parser::ExtractSpaceDeclaration(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto keyword = ParseKeyword(data_, it_, scope_, Keyword::Value::Space))
	{
		if (auto group = ParseToken<Lexing2::Group>(data_, it_))
		{
			if (group->GetOpening() == Lexing2::Group::BraceType::Figure && group->GetClosing() == Lexing2::Group::BraceType::Figure)
			{
				// replace with RepaceRequire?
				auto markers = Move(Convert(group->GetTokens()));
				auto space = Make<Space>(Move(markers));
				{
					parenthoodManager->SetParent(space, scope_);
				}

				return space;
			}
			else
			{
				throw Exception();
			}
		}
	}

	it_ = o;
	return nullptr;
}
inline Nu::Reference<Nu::Parsing3::Space> Nu::Parsing3::Parser::ParseSpace(Data& data_, It& it_, const Reference<Scope>& scope_)
{
	auto o = it_;

	if (auto space = ParseMarker<Space>(data_, it_))
	{
		// TODO: parse space

		return space;
	}
	else if (auto spaceDeclaration = ExtractSpaceDeclaration(data_, it_, scope_))
	{
		MarkersContainer::Markers markers;
		{
			markers.push_back(spaceDeclaration);
		}

		throw MarkersReplaceRequired(o, it_, markers);
	}

	it_ = o;
	return nullptr;
}
inline void Nu::Parsing3::Parser::Preparse(const Reference<Root>& root_)
{
	auto &markers = root_->GetMarkers();
	auto it = markers.begin();

	while (it != markers.end())
	{
		try
		{
			auto o = it;

			if (auto declarationHeader = ExtractDeclarationHeader(markers, it, root_))
			{
				MarkersContainer::Markers markers;
				{
					markers.push_back(declarationHeader);
				}

				throw MarkersReplaceRequired(o, it, markers);
			}
			else
			{
				++it;
			}
		}
		catch (MarkersReplaceRequired replace)
		{
			auto i = markers.erase(replace.begin, replace.end);

			for (auto &m : replace.markers)
			{
				i = markers.insert(i, m);
			}

			it = markers.begin();
		}
	}
}

inline void Nu::Parsing3::Parser::Parse(const Reference<Root>& root_)
{
	Preparse(root_);

	auto &markers = root_->GetMarkers();
	auto it = markers.begin();

	while (it != markers.end())
	{
		try
		{
			auto o = it;

			if (auto space = ParseSpace(markers, it, root_))
			{
				// do nothing
			}
			else if (auto declaration = ParseDeclaration(markers, it, root_))
			{
				// do nothing
			}
			else
			{
				throw Exception();
			}
		}
		catch (MarkersReplaceRequired replace)
		{
			auto i = markers.erase(replace.begin, replace.end);

			for (auto &m : replace.markers)
			{
				i = markers.insert(i, m);
			}

			it = markers.begin();
		}
		catch (MarkersSkipRequired skip)
		{
			isMarkerSkipped = true;

			it = skip.end;
		}
	}
}

inline Nu::Parsing3::Parser::Output Nu::Parsing3::Parser::Parse(const Input& input_)
{
	auto root = Make<Root>();

	auto spaceNameValue = Name::Value("space");
	{
		auto spaceName = root->Add(spaceNameValue);
		auto spaceKeyword = Make<Keyword>(Keyword::Value::Space);

		parenthoodManager->SetValue(spaceName, spaceKeyword);
	}

	auto mainNameValue = Name::Value(".main");
	{
		auto mainName = root->Add(mainNameValue);

		auto markers = Move(Convert(input_->GetTokens()));
		auto main = Make<Root>(Move(markers));
		{
			parenthoodManager->SetParent(main, root);
		}

		do
		{
			isMarkerSkipped = false;

			Parse(main);
		}
		while (isMarkerSkipped);

		return main;
	}
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















