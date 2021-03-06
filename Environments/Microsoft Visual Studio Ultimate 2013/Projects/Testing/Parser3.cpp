#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Parser3/Parser.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Parser3
	{
		using namespace Nu;
		using namespace Parsing3;

		TEST_CLASS(Smoke)
		{
		public:
			/* Requirement: SCP.01
			 * Barely created Scope should NOT contain any Names.
			 */
			TEST_METHOD(Scope_Empty)
			{
				auto scope = Make<Parsing3::Scope>();
				{
					auto names = scope->GetNames();

					Assert::IsTrue(
						names.size() == 0,
						L"Names in empty"
					);
				}
			}
			/* Requirement: SCP.02A
			 * If the Scope do not contain any Names under the Value "X", then,
			 * after the Name "Y" will be added to the Scope under Value "X" - 
			 * the Scope should contain Name "Y" under the Value "X" with the Level equals to 0.
			 */
			TEST_METHOD(Scope_SingleName)
			{
				auto scope = Make<Parsing3::Scope>();

				auto nameValue1 = "a";
				auto name1 = scope->Add(nameValue1);
				{
					auto names = scope->GetNames();

					auto levelsIt = names.find(nameValue1);

					Assert::IsTrue(
						levelsIt != names.end(),
						L"Verify name value"
					);

					auto levels = (*levelsIt).second;
					auto namesIt = levels.find(0);

					Assert::IsTrue(
						namesIt != levels.end(),
						L"Verify name level"
					);

					auto name = (*namesIt).second;

					Assert::IsTrue(
						name == name1,
						L"Verify name"
					);
				}
			}
			/* Requirement: SCP.02B
			 * If the Scope contain N Names under the Value "X", then,
			 * after the Name "Y" will be added to the Scope under the Value "X" -
			 * the Scope should contain previous Names under the Value "X"
			 * with corresponding Levels increased by 1,
			 * and the Name "Y" under the Value "X" with Level equal to 0.
			 */
			TEST_METHOD(Scope_DuplicatedName)
			{
				auto scope = Make<Parsing3::Scope>();

				auto nameValue1 = "a";
				auto name1 = scope->Add(nameValue1);

				auto duplicatedNameValue1 = "a";
				auto duplicatedName1 = scope->Add(duplicatedNameValue1);
				{
					auto names = scope->GetNames();

					auto levelsIt = names.find(duplicatedNameValue1);

					Assert::IsTrue(
						levelsIt != names.end(),
						L"Verify name value"
					);

					auto levels = (*levelsIt).second;
					auto namesIt = levels.find(0);

					Assert::IsTrue(
						namesIt != levels.end(),
						L"Verify name level"
					);

					auto name = (*namesIt).second;

					Assert::IsTrue(
						name == duplicatedName1,
						L"Verify name"
					);

					auto names2It = levels.find(1);

					Assert::IsTrue(
						names2It != levels.end(),
						L"Verify name level"
					);

					auto duplicatedName = (*names2It).second;

					Assert::IsTrue(
						duplicatedName == name1,
						L"Verify name"
					);
				}
			}
			/* Requirement: TODO
			 */
			TEST_METHOD(Scope_SeveralNames)
			{
				auto scope = Make<Parsing3::Scope>();

				auto nameValue1 = "a";
				auto nameValue2 = "b";
				auto name1 = scope->Add(nameValue1);
				auto name2 = scope->Add(nameValue2);
				{
					auto names = scope->GetNames();

					auto levels1It = names.find(nameValue1);

					Assert::IsTrue(
						levels1It != names.end(),
						L"Verify name value"
					);

					auto levels1 = (*levels1It).second;
					auto names1It = levels1.find(0);

					Assert::IsTrue(
						names1It != levels1.end(),
						L"Verify name level"
					);

					auto sourceName1 = (*names1It).second;

					Assert::IsTrue(
						sourceName1 == name1,
						L"Verify name"
					);

					auto levels2It = names.find(nameValue2);

					Assert::IsTrue(
						levels2It != names.end(),
						L"Verify name value"
					);

					auto levels2 = (*levels2It).second;
					auto names2It = levels2.find(0);

					Assert::IsTrue(
						names2It != levels2.end(),
						L"Verify name level"
					);

					auto sourceName2 = (*names2It).second;

					Assert::IsTrue(
						sourceName2 == name2,
						L"Verify name"
					);
				}
			}
			/* Requirement: TODO
			 */
			TEST_METHOD(Scope_DuplicatedNameWithOtherNameBetween)
			{
				auto scope = Make<Parsing3::Scope>();

				auto nameValue1 = "a";
				auto name1 = scope->Add(nameValue1);

				auto nameValue2 = "b";
				auto name2 = scope->Add(nameValue2);

				auto duplicatedNameValue1 = "a";
				auto duplicatedName1 = scope->Add(duplicatedNameValue1);
				{
					auto names = scope->GetNames();

					auto levelsIt = names.find(duplicatedNameValue1);

					Assert::IsTrue(
						levelsIt != names.end(),
						L"Verify name value"
					);

					auto levels = (*levelsIt).second;
					auto namesIt = levels.find(0);

					Assert::IsTrue(
						namesIt != levels.end(),
						L"Verify name level"
					);

					auto name = (*namesIt).second;

					Assert::IsTrue(
						name == duplicatedName1,
						L"Verify name"
					);

					auto names2It = levels.find(1);

					Assert::IsTrue(
						names2It != levels.end(),
						L"Verify name level"
					);

					auto duplicatedName = (*names2It).second;

					Assert::IsTrue(
						duplicatedName == name1,
						L"Verify name"
					);
				}
			}
		public:
			/* Requirement: TODO
			 */
			/*TEST_METHOD(ParenthoodManager_Empty)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto space1 = Make<Parsing3::Space>();

				auto parent = parenthoodManager->GetParent(space1);

				Assert::IsTrue(
					parent == nullptr,
					L"Verify that parent is nullptr"
				);

				auto names = parenthoodManager->GetNames(space1);

				Assert::IsTrue(
					names.empty(),
					L"Verify that names is empty"
				);
			}*/
			/* Requirement: TODO
			 */
			/*TEST_METHOD(ParenthoodManager_UnitParent)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto scope1 = Make<Parsing3::Scope>();
				auto unit1 = Make<Parsing3::Unit>();
				{
					parenthoodManager->SetParent(unit1, scope1);
				}

				auto parent = parenthoodManager->GetParent(unit1);

				Assert::IsTrue(
					parent == scope1,
					L"Verify that unit1 parent equal to scope1"
				);
			}*/
			/* Requirement: TODO
			 */
			/*TEST_METHOD(ParenthoodManager_SingleScopeNames)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto space1 = Make<Parsing3::Space>();

				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);
				auto nameValue2 = "b";
				auto name2 = space1->Add(nameValue2);
				{
					auto names = parenthoodManager->GetNames(space1);

					Assert::IsTrue(
						names[nameValue1][0] == name1,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue2][0] == name2,
						L"Verify that name is as expected"
					);
				}

				auto nameValue3 = nameValue1;
				auto name3 = space1->Add(nameValue3);
				{
					auto names = parenthoodManager->GetNames(space1);

					Assert::IsTrue(
						names[nameValue1][1] == name1,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue3][0] == name3,
						L"Verify that name is as expected"
					);
				}
			}*/
			/* Requirement: TODO
			 */
			/*TEST_METHOD(ParenthoodManager_TwoNestedScopeNames)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto space1 = Make<Parsing3::Space>();
				auto space2 = Make<Parsing3::Space>();
				{
					parenthoodManager->SetParent(space2, space1);
				}

				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);
				auto nameValue2 = "b";
				auto name2 = space1->Add(nameValue2);
				auto nameValue3 = nameValue1;
				auto name3 = space1->Add(nameValue3);
				{
					auto names = parenthoodManager->GetNames(space2);

					Assert::IsTrue(
						names[nameValue1][1] == name1,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue3][0] == name3,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue2][0] == name2,
						L"Verify that name is as expected"
					);
				}

				auto nameValue4 = nameValue3;
				auto name4 = space1->Add(nameValue4);
				auto nameValue5 = nameValue2;
				auto name5 = space1->Add(nameValue5);
				{
					auto names = parenthoodManager->GetNames(space2);

					Assert::IsTrue(
						names[nameValue1][2] == name1,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue1][1] == name3,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue3][0] == name4,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue2][1] == name2,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue2][0] == name5,
						L"Verify that name is as expected"
					);
				}
			}*/
		public: // experimental
			TEST_METHOD(ParenthoodManager_Merge_Empty)
			{
				Scope::Names a;
				Scope::Names b;

				auto c = ParenthoodManager::Merge(a, b);

				Assert::IsTrue(
					c.empty() == true,
					L"Verify that result is empty"
				);
			}
			TEST_METHOD(ParenthoodManager_Merge_EmptyOverlapping)
			{
				auto n1 = Make<Name>();

				Scope::Names a;
				{
					a["x"][0] = n1;
				}
				Scope::Names b;

				auto c = ParenthoodManager::Merge(a, b);

				Assert::IsTrue(
					c.size() == 1,
					L""
				);

				Assert::IsTrue(
					c["x"].size() == 1,
					L""
				);

				Assert::IsTrue(
					c["x"][0] == n1,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_Merge_EmptyPrevious)
			{
				auto n1 = Make<Name>();

				Scope::Names a;
				Scope::Names b;
				{
					b["x"][0] = n1;
				}

				auto c = ParenthoodManager::Merge(a, b);

				Assert::IsTrue(
					c.size() == 1,
					L""
				);

				Assert::IsTrue(
					c["x"].size() == 1,
					L""
				);

				Assert::IsTrue(
					c["x"][0] == n1,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_Merge_NotIntersecting)
			{
				auto n1 = Make<Name>();
				auto n2 = Make<Name>();

				Scope::Names a;
				{
					a["x"][0] = n1;
				}
				Scope::Names b;
				{
					b["y"][0] = n2;
				}

				auto c = ParenthoodManager::Merge(a, b);

				Assert::IsTrue(
					c.size() == 2,
					L""
				);

				Assert::IsTrue(
					c["x"].size() == 1,
					L""
				);
				Assert::IsTrue(
					c["x"][0] == n1,
					L""
				);


				Assert::IsTrue(
					c["y"].size() == 1,
					L""
				);
				Assert::IsTrue(
					c["y"][0] == n2,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_Merge_Intersecting)
			{
				auto n1 = Make<Name>();
				auto n2 = Make<Name>();

				Scope::Names a;
				{
					a["x"][0] = n1;
				}
				Scope::Names b;
				{
					b["x"][0] = n2;
				}

				auto c = ParenthoodManager::Merge(a, b);

				Assert::IsTrue(
					c.size() == 1,
					L""
				);

				Assert::IsTrue(
					c["x"].size() == 2,
					L""
				);
				Assert::IsTrue(
					c["x"][0] == n2,
					L""
				);
				Assert::IsTrue(
					c["x"][1] == n1,
					L""
				);
			}
		public:
			TEST_METHOD(ParenthoodManager_GetNames2_Empty)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto space1 = Make<Space>();
				auto &markers1 = space1->GetMarkers();

				auto names = parenthoodManager->GetNames2(space1, space1, markers1.end());

				Assert::IsTrue(
					names.empty() == true,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_GetNames2_SingleNameInsideSingleSpace)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto space1 = Make<Space>();
				auto &markers1 = space1->GetMarkers();

				Name::Value nameValue1 = "x";
				auto name1 = space1->Add(nameValue1);
				{
					markers1.push_back(Make<Declaration>(nameValue1, name1));
				}

				auto names = parenthoodManager->GetNames2(space1, space1, markers1.begin());
				
				Assert::IsTrue(
					names.size() == 1,
					L""
				);
				Assert::IsTrue(
					names["x"].size() == 1,
					L""
				);
				Assert::IsTrue(
					names["x"][0] == name1,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_GetNames2_SingleNameInsideBodyGetBeforeDeclaration)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto body1 = Make<Body>();
				auto &markers1 = body1->GetMarkers();

				Name::Value nameValue1 = "x";
				auto name1 = body1->Add(nameValue1);
				{
					markers1.push_back(Make<Declaration>(nameValue1, name1));
				}

				auto names = parenthoodManager->GetNames2(body1, body1, markers1.begin());
				
				Assert::IsTrue(
					names.size() == 0,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_GetNames2_SingleNameInsideBodyGetAfterDeclaration)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto body1 = Make<Body>();
				auto &markers1 = body1->GetMarkers();

				Name::Value nameValue1 = "x";
				auto name1 = body1->Add(nameValue1);
				{
					markers1.push_back(Make<Declaration>(nameValue1, name1));
				}

				auto names = parenthoodManager->GetNames2(body1, body1, markers1.end());
				
				Assert::IsTrue(
					names.size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue1].size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue1][0] == name1,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_GetNames2_SeveralNameInsideBodyGetAfterDeclarations)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto body1 = Make<Body>();
				auto &markers1 = body1->GetMarkers();

				Name::Value nameValue1 = "x";
				auto name1 = body1->Add(nameValue1);
				{
					markers1.push_back(Make<Declaration>(nameValue1, name1));
				}

				Name::Value nameValue2 = "y";
				auto name2 = body1->Add(nameValue2);
				{
					markers1.push_back(Make<Declaration>(nameValue2, name2));
				}

				auto names = parenthoodManager->GetNames2(body1, body1, markers1.end());
				
				Assert::IsTrue(
					names.size() == 2,
					L""
				);
				Assert::IsTrue(
					names[nameValue1].size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue1][0] == name1,
					L""
				);
				Assert::IsTrue(
					names[nameValue2].size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue2][0] == name2,
					L""
				);
			}
			TEST_METHOD(ParenthoodManager_GetNames2_SeveralNameInsideBodyGetBetweenDeclarations)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				
				auto body1 = Make<Body>();
				auto &markers1 = body1->GetMarkers();

				Name::Value nameValue1 = "x";
				auto name1 = body1->Add(nameValue1);
				{
					markers1.push_back(Make<Declaration>(nameValue1, name1));
				}

				auto itDelimiter = markers1.insert(markers1.end(), Make<Delimiter>());

				Name::Value nameValue2 = "y";
				auto name2 = body1->Add(nameValue2);
				{
					markers1.push_back(Make<Declaration>(nameValue2, name2));
				}

				auto names = parenthoodManager->GetNames2(body1, body1, itDelimiter);
				
				Assert::IsTrue(
					names.size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue1].size() == 1,
					L""
				);
				Assert::IsTrue(
					names[nameValue1][0] == name1,
					L""
				);
			}
		public:
			TEST_METHOD(Parser_ExtractName_SingleName)
			{
				auto space = Make<Parsing3::Space>();
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);

				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it = markers.begin();

				auto output = Parser::ExtractName(markers, it, space, parenthoodManager);

				Assert::IsTrue(
					output == name1,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_SingleNameWithTailText)
			{
				auto space = Make<Parsing3::Space>();
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);

				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("b")));
				};
				auto it = markers.begin();

				auto output = Parser::ExtractName(markers, it, space, parenthoodManager);

				Assert::IsTrue(
					output == name1,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_MultipleNames)
			{
				auto space = Make<Parsing3::Space>();
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);
				
				auto nameValue2 = "b";
				auto name2 = space->Add(nameValue2);

				MarkersContainer::Markers markers1;
				{
					markers1.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it1 = markers1.begin();

				auto output1 = Parser::ExtractName(markers1, it1, space, parenthoodManager);

				Assert::IsTrue(
					output1 == name1,
					L"Verify that name is as expected"
				);

				MarkersContainer::Markers markers2;
				{
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Text>("b")));
				};
				auto it2 = markers2.begin();

				auto output2 = Parser::ExtractName(markers2, it2, space, parenthoodManager);

				Assert::IsTrue(
					output2 == name2,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_SingleDuplicatedName)
			{
				auto space = Make<Parsing3::Space>();
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);
				auto name2 = space->Add(nameValue1);

				MarkersContainer::Markers markers1;
				{
					markers1.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it1 = markers1.begin();

				auto output1 = Parser::ExtractName(markers1, it1, space, parenthoodManager);

				Assert::IsTrue(
					output1 == name2,
					L"Verify that name is as expected"
				);

				MarkersContainer::Markers markers2;
				{
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it2 = markers2.begin();

				auto output2 = Parser::ExtractName(markers2, it2, space, parenthoodManager);

				Assert::IsTrue(
					output2 == name1,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_SeveralScopes)
			{
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();
				auto space1 = Make<Parsing3::Space>();
				auto space2 = Make<Parsing3::Space>();
				{
					parenthoodManager->SetParent(space2, space1);
				}

				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);
				auto name2 = space2->Add(nameValue1);

				MarkersContainer::Markers markers1;
				{
					markers1.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it1 = markers1.begin();

				auto output1 = Parser::ExtractName(markers1, it1, space2, parenthoodManager);

				Assert::IsTrue(
					output1 == name2,
					L"Verify that name is as expected"
				);

				MarkersContainer::Markers markers2;
				{
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it2 = markers2.begin();

				auto output2 = Parser::ExtractName(markers2, it2, space2, parenthoodManager);

				Assert::IsTrue(
					output2 == name1,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_LongName)
			{
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();
				auto space = Make<Parsing3::Space>();

				auto nameValue1 = "ab";
				auto name1 = space->Add(nameValue1);
				auto nameValue2 = "a";
				auto name2 = space->Add(nameValue2);

				MarkersContainer::Markers markers1;
				{
					markers1.push_back(Make<Token>(Make<Nu::Lexing2::Text>("ab")));
				};
				auto it1 = markers1.begin();

				auto output1 = Parser::ExtractName(markers1, it1, space, parenthoodManager);

				Assert::IsTrue(
					output1 == name1,
					L"Verify that name is as expected"
				);

				MarkersContainer::Markers markers2;
				{
					markers2.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
				};
				auto it2 = markers2.begin();

				auto output2 = Parser::ExtractName(markers2, it2, space, parenthoodManager);

				Assert::IsTrue(
					output2 == name2,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_NameDivision)
			{
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();
				auto space = Make<Parsing3::Space>();

				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);

				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("ab")));
				};
				auto it = markers.begin();

				try
				{
					Parser::ExtractName(markers, it, space, parenthoodManager);

					Assert::Fail(L"Exception fail");
				}
				catch (const Parser::MarkersReplaceRequired& division_)
				{
					auto m1 = *division_.markers.begin();
					auto m2 = *(++division_.markers.begin());

					Assert::IsTrue(
						division_.begin == markers.begin() &&
						division_.end == markers.end() &&
						UpCast<Lexing2::Text>(UpCast<Token>(m1)->GetValue())->GetValue() == "a" &&
						UpCast<Lexing2::Text>(UpCast<Token>(m2)->GetValue())->GetValue() == "b",
						L"Verify that correct exception is thrown"
					);
				}
			}
			TEST_METHOD(Parser_ExtractName_ChildNameDivision)
			{
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto space1 = Make<Parsing3::Space>();
				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);

				auto space2 = Make<Parsing3::Space>();
				{
					parenthoodManager->SetParent(space2, space1);
					parenthoodManager->SetValue(name1, space2);
				}
				auto nameValue2 = "b";
				auto name2 = space2->Add(nameValue2);

				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("bc")));
				};
				auto it = markers.begin();

				try
				{
					Parser::ExtractName(markers, it, space1, parenthoodManager);

					Assert::Fail(L"Exception fail");
				}
				catch (const Parser::MarkersReplaceRequired& division_)
				{
					auto m1 = *division_.markers.begin();
					auto m2 = *(++division_.markers.begin());

					Assert::IsTrue(
						division_.begin == (++(++markers.begin())) &&
						division_.end == (markers.end()) &&
						UpCast<Lexing2::Text>(UpCast<Token>(m1)->GetValue())->GetValue() == "b" &&
						UpCast<Lexing2::Text>(UpCast<Token>(m2)->GetValue())->GetValue() == "c",
						L"Verify that correct exception is thrown"
					);
				}
			}
			TEST_METHOD(Parser_ExtractName_ChildName)
			{
				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("b")));
				};
				auto it = markers.begin();

				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();
				
				auto space1 = Make<Parsing3::Space>();
				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);

				auto space2 = Make<Parsing3::Space>();
				{
					parenthoodManager->SetParent(space2, space1);
					parenthoodManager->SetValue(name1, space2);
				}
				auto nameValue2 = "b";
				auto name2 = space2->Add(nameValue2);

				auto output = Parser::ExtractName(markers, it, space1, parenthoodManager);

				Assert::IsTrue(
					output == name2,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_ChildNameWithTailText)
			{
				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("b")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("c")));
				};
				auto it = markers.begin();

				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();
				
				auto space1 = Make<Parsing3::Space>();
				auto nameValue1 = "a";
				auto name1 = space1->Add(nameValue1);

				auto space2 = Make<Parsing3::Space>();
				{
					parenthoodManager->SetParent(space2, space1);
					parenthoodManager->SetValue(name1, space2);
				}
				auto nameValue2 = "b";
				auto name2 = space2->Add(nameValue2);

				auto output = Parser::ExtractName(markers, it, space1, parenthoodManager);

				Assert::IsTrue(
					output == name2,
					L"Verify that name is as expected"
				);
			}
			TEST_METHOD(Parser_ExtractName_ChildNameSkip)
			{
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto space = Make<Parsing3::Space>();
				auto nameValue1 = "a";
				auto name1 = space->Add(nameValue1);

				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("a")));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("b")));
				};
				auto it = markers.begin();

				try
				{
					Parser::ExtractName(markers, it, space, parenthoodManager);

					Assert::Fail(L"Exception fail");
				}
				catch (const Parser::MarkersSkipRequired& skip_)
				{
					Assert::IsTrue(
						skip_.end == markers.end(),
						L"Verify that correct exception is thrown"
					);
				}
			}
			/*TEST_METHOD(Test1)
			{
				MarkersContainer::Markers markers;
				{
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Special>(Nu::Lexing2::Special::Value::Dot)));
					markers.push_back(Make<Token>(Make<Nu::Lexing2::Text>("ab")));
				};
				auto it = markers.begin();

				auto scope = Make<Parsing3::Scope>();
				auto parenthoodManager = Make<Parsing3::ParenthoodManager>();

				auto nameValue1 = "a";
				auto name1 = scope->Add(nameValue1);
				auto name2 = scope->Add(nameValue1); // fictive
				auto name3 = scope->Add(nameValue1); // fictive
				auto nameValue4 = "ab";
				auto name4 = scope->Add(nameValue4); // fictive

				auto output = Parser::ExtractName(markers, it, scope, parenthoodManager);
			}*/
		public:
			/*TEST_METHOD(Test1)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);

				Assert::IsTrue(
					output != nullptr,
					L""
				);
			}*/
			TEST_METHOD(Parser_Parse_Empty)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();

				auto output = parser->Parse(input);

				Assert::IsTrue(
					output != nullptr,
					L"Verify that parsing output in not a nullptr"
				);

				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 0,
					L"Verify that markers is empty"
				);
			}
			TEST_METHOD(Parser_Parse_SingleDelimiter)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);

				Assert::IsTrue(
					output != nullptr,
					L"Verify that parsing output in not a nullptr"
				);

				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 1,
					L"Verify that there is 1 marker"
				);

				auto delimiter = UpCast<Delimiter>(*markers.begin());

				Assert::IsTrue(
					delimiter != nullptr,
					L"Verify that marker is delimiter"
				);
			}
			
			TEST_METHOD(Parser_Parse_SingleSpace)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 1,
					L"Verify that there is 1 marker"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Space>(*markers.begin()) != nullptr,
					L"Verify that marker is space"
				);
			}
			TEST_METHOD(Parser_Parse_SingleSpaceWithDelimiter)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 2,
					L"Verify that there is 2 markers"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Space>(*markers.begin()) != nullptr,
					L"Verify that marker is space"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Delimiter>(*(++markers.begin())) != nullptr,
					L"Verify that marker is delimiter"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralSpaces)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 2,
					L"Verify that there is 2 markers"
				);

				auto space1 = UpCast<Parsing3::Space>(*markers.begin());
				Assert::IsTrue(
					space1 != nullptr,
					L"Verify that marker is space"
				);

				auto space2 = UpCast<Parsing3::Space>(*(++markers.begin()));
				Assert::IsTrue(
					space2 != nullptr,
					L"Verify that marker is space"
				);

				Assert::IsTrue(
					space1 != space2,
					L"Verify that spaces is different"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralSpacesWithDelimiter)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 3,
					L"Verify that there is 3 markers"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Space>(*markers.begin()) != nullptr,
					L"Verify that marker is space"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Delimiter>(*(++markers.begin())) != nullptr,
					L"Verify that marker is delimiter"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Space>(*(++(++markers.begin()))) != nullptr,
					L"Verify that marker is space"
				);
			}
			
			TEST_METHOD(Parser_Parse_SingleSchema)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 1,
					L"Verify that there is 1 marker"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Schema>(*markers.begin()) != nullptr,
					L"Verify that marker is schema"
				);
			}
			TEST_METHOD(Parser_Parse_SingleSchemaWithDelimiter)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 2,
					L"Verify that there is 2 markers"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Schema>(*markers.begin()) != nullptr,
					L"Verify that marker is schema"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Delimiter>(*(++markers.begin())) != nullptr,
					L"Verify that marker is delimiter"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralSchemas)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 2,
					L"Verify that there is 2 markers"
				);

				auto schema1 = UpCast<Parsing3::Schema>(*markers.begin());
				Assert::IsTrue(
					schema1 != nullptr,
					L"Verify that marker is schema"
				);

				auto schema2 = UpCast<Parsing3::Schema>(*(++markers.begin()));
				Assert::IsTrue(
					schema2 != nullptr,
					L"Verify that marker is schema"
				);

				Assert::IsTrue(
					schema1 != schema2,
					L"Verify that schemas is different"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralSchemasWithDelimiter)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 0,
					L"Verify that names is empty"
				);

				auto &markers = output->GetMarkers();

				Assert::IsTrue(
					markers.size() == 3,
					L"Verify that there is 3 markers"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Schema>(*markers.begin()) != nullptr,
					L"Verify that marker is schema"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Delimiter>(*(++markers.begin())) != nullptr,
					L"Verify that marker is delimiter"
				);

				Assert::IsTrue(
					UpCast<Parsing3::Schema>(*(++(++markers.begin()))) != nullptr,
					L"Verify that marker is schema"
				);
			}

			TEST_METHOD(Parser_Parse_SingleName_KeywordAlias)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is keyword"
				);
				Assert::IsTrue(
					keyword->GetValue() == Parsing3::Keyword::Value::Space,
					L"Verify that keyword value is \"space\""
				);
			}
			TEST_METHOD(Parser_Parse_SingleName_KeywordAliasForwardDeclaration)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();
				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is keyword"
				);
				Assert::IsTrue(
					keyword->GetValue() == Parsing3::Keyword::Value::Space,
					L"Verify that keyword value is \"space\""
				);
			}
			TEST_METHOD(Parser_Parse_SeveralNames_SequentialKeywordAlias)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("b");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"b\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is a keyword"
				);
				Assert::IsTrue(
					keyword->GetValue() == Parsing3::Keyword::Value::Space,
					L"Verify that keyword value is \"space\""
				);
			}
			TEST_METHOD(Parser_Parse_SingleName_SpaceDeclaration)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				Assert::IsTrue(
					space != nullptr,
					L"Verify that value is space"
				);
			}
			TEST_METHOD(Parser_Parse_SingleName_SchemaDeclaration)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				Assert::IsTrue(
					names.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto schema = UpCast<Parsing3::Schema>(value);

				Assert::IsTrue(
					schema != nullptr,
					L"Verify that value is schema"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralNames_SpaceAlias)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("b");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"b\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				Assert::IsTrue(
					space != nullptr,
					L"Verify that value is space"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralNames_SpaceAliasForwardDeclaration)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				Assert::IsTrue(
					space != nullptr,
					L"Verify that value is space"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralNames_SchemaAlias)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("b");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"b\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto schema = UpCast<Parsing3::Schema>(value);

				Assert::IsTrue(
					schema != nullptr,
					L"Verify that value is schema"
				);
			}
			TEST_METHOD(Parser_Parse_SeveralNames_SchemaAliasForwardDeclaration)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto schema = UpCast<Parsing3::Schema>(value);

				Assert::IsTrue(
					schema != nullptr,
					L"Verify that value is schema"
				);
			}
			
			TEST_METHOD(Parser_Parse_KeywordAliasAndUsage)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("s"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("s"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				Assert::IsTrue(
					space != nullptr,
					L"Verify that value is space"
				);
			}
			
			TEST_METHOD(Parser_Parse_NestedSpaceInsideSpace)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("b"));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						nested.push_back(Make<Lexing2::Text>("space"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				auto &names2 = space->GetNames();

				auto nameIt2 = names2.find("b");

				Assert::IsTrue(
					nameIt2 != names2.end(),
					L"Verify that there is name \"b\""
				);

				auto levels2 = (*nameIt2).second;
				auto levelsIt2 = levels2.find(0);

				Assert::IsTrue(
					levelsIt2 != levels2.end(),
					L"Verify that there is level 0"
				);

				auto name2 = (*levelsIt2).second;
				auto value2 = parser->parenthoodManager->GetValue(name2);
				auto space2 = UpCast<Parsing3::Space>(value2);

				Assert::IsTrue(
					space2 != nullptr,
					L"Verify that value is space"
				);
			}
			TEST_METHOD(Parser_Parse_NestedSchemaInsideSpace)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("b"));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						nested.push_back(Make<Lexing2::Text>("schema"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("a");

				Assert::IsTrue(
					nameIt != names.end(),
					L"Verify that there is name \"a\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto space = UpCast<Parsing3::Space>(value);

				auto &names2 = space->GetNames();

				auto nameIt2 = names2.find("b");

				Assert::IsTrue(
					nameIt2 != names2.end(),
					L"Verify that there is name \"b\""
				);

				auto levels2 = (*nameIt2).second;
				auto levelsIt2 = levels2.find(0);

				Assert::IsTrue(
					levelsIt2 != levels2.end(),
					L"Verify that there is level 0"
				);

				auto name2 = (*levelsIt2).second;
				auto value2 = parser->parenthoodManager->GetValue(name2);
				auto schema2 = UpCast<Parsing3::Schema>(value2);

				Assert::IsTrue(
					schema2 != nullptr,
					L"Verify that value is schema"
				);
			}
			
			TEST_METHOD(Parser_Parse_AccesingNestedUnit)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("b"));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						nested.push_back(Make<Lexing2::Text>("space"));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
					input->GetTokens().push_back(Make<Lexing2::Text>("c"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Dot));
					input->GetTokens().push_back(Make<Lexing2::Text>("b"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("c");
				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);
				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is keyword"
				);
			}
			TEST_METHOD(Parser_Parse_AccesingPreviousUnit)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Text>("c"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Dot));
					input->GetTokens().push_back(Make<Lexing2::Text>("a"));
				}

				auto output = parser->Parse(input);
				auto &names = output->GetNames();

				auto nameIt = names.find("c");
				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);
				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is keyword"
				);
			}

			TEST_METHOD(Parser_Parse_UnnamedSchema_AlgorithmDeclarationWithoutResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("none"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();

				auto schema = UpCast<Parsing3::Schema>(*markers.begin());
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				Assert::IsTrue(
					algorithm->GetResult() == parser->globalNoneSchema,
					L"Verify that algorithm arguments is empty"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_UnnamedSchema_AlgorithmDeclarationWithResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("A"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));

					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("A"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(*markers.rbegin());
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				auto resultSchema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["A"][0]));

				Assert::IsTrue(
					algorithm->GetResult() == resultSchema,
					L"Verify that algorithm result is as expected"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_UnnamedSchema_AlgorithmDeclarationWithForwardDeclarationResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("A"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
					
					input->GetTokens().push_back(Make<Lexing2::Text>("A"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(*markers.begin());
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				auto resultSchema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["A"][0]));

				Assert::IsTrue(
					algorithm->GetResult() == resultSchema,
					L"Verify that algorithm result is as expected"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_NamedSchema_AlgorithmDeclarationWithoutResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("none"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["X"][0]));
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				Assert::IsTrue(
					algorithm->GetResult() == parser->globalNoneSchema,
					L"Verify that algorithm arguments is empty"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_NamedSchema_AlgorithmDeclarationWithResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("A"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));

					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("A"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["X"][0]));
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				auto resultSchema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["A"][0]));

				Assert::IsTrue(
					algorithm->GetResult() == resultSchema,
					L"Verify that algorithm result is as expected"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_NamedSchema_AlgorithmDeclarationWithSelfResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("X"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["X"][0]));
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				Assert::IsTrue(
					algorithm->GetResult() == schema,
					L"Verify that algorithm result is same as schema"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}
			TEST_METHOD(Parser_Parse_NamedSchema_AlgorithmDeclarationWithForwardDeclarationResult)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("A"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
					
					input->GetTokens().push_back(Make<Lexing2::Text>("A"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["X"][0]));
				auto &algorithms = schema->GetAlgorithms();

				Assert::IsTrue(
					algorithms.size() == 1,
					L"Verify that there is exactly 1 algorithm"
				);

				auto algorithm = algorithms[0];

				auto resultSchema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["A"][0]));

				Assert::IsTrue(
					algorithm->GetResult() == resultSchema,
					L"Verify that algorithm result is as expected"
				);

				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);

				Assert::IsTrue(
					braceAlgorithm != nullptr,
					L"Verify that algorithm is Brace Algorithm"
				);

				Assert::IsTrue(
					braceAlgorithm->GetOpening() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm opening is Round"
				);
				Assert::IsTrue(
					braceAlgorithm->GetClosing() == Parsing3::BraceAlgorithm::BraceType::Round,
					L"Verify that algorithm closing is Round"
				);

				Assert::IsTrue(
					braceAlgorithm->GetArguments().empty(),
					L"Verify that algorithm arguments is empty"
				);
			}

			TEST_METHOD(Parser_Parse_BodyContent_KeywordAlias)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens x;
					{
						x.push_back(Make<Lexing2::Text>("x"));
						x.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						x.push_back(Make<Lexing2::Text>("space"));
					}

					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("none"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Text>("body"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, x));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(parser->parenthoodManager->GetValue(names["X"][0]));
				auto &algorithms = schema->GetAlgorithms();
				auto algorithm = algorithms[0];
				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);
				auto body = parser->parenthoodManager->GetBody(braceAlgorithm);
				auto algorithmsNames = body->GetNames();

				Assert::IsTrue(
					algorithmsNames.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = algorithmsNames.find("x");

				Assert::IsTrue(
					nameIt != algorithmsNames.end(),
					L"Verify that there is name \"x\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto keyword = UpCast<Parsing3::Keyword>(value);

				Assert::IsTrue(
					keyword != nullptr,
					L"Verify that value is keyword"
				);
				Assert::IsTrue(
					keyword->GetValue() == Parsing3::Keyword::Value::Space,
					L"Verify that keyword value is \"space\""
				);
			}
			TEST_METHOD(Parser_Parse_BodyContent_CreateUnnamedInstance)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens bodyContent;
					{
						// bodyContent.push_back(Make<Lexing2::Text>("x"));
						// bodyContent.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						bodyContent.push_back(Make<Lexing2::Text>("make"));
						bodyContent.push_back(Make<Lexing2::Text>("none"));
					}

					Lexing2::Container::Tokens schemaContent;
					{
						schemaContent.push_back(Make<Lexing2::Text>("algorithm"));
						schemaContent.push_back(Make<Lexing2::Text>("none"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						schemaContent.push_back(Make<Lexing2::Text>("body"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, bodyContent));
					}

					// input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					// input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, schemaContent));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(markers.front());
				auto &algorithms = schema->GetAlgorithms();
				auto algorithm = algorithms[0];
				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);
				auto body = parser->parenthoodManager->GetBody(braceAlgorithm);
				auto bodyMarkers = body->GetMarkers();

				Assert::IsTrue(
					bodyMarkers.size() == 1,
					L"Verify that there is 1 marker"
				);

				auto instanceCreationCommand = UpCast<InstanceCreationCommand>(bodyMarkers.front());

				Assert::IsTrue(
					instanceCreationCommand != nullptr,
					L"Verify that marker is InstanceCreationCommand"
				);

				auto instanceSchema = instanceCreationCommand->GetInstance()->GetSchema();

				Assert::IsTrue(
					instanceSchema == parser->globalNoneSchema,
					L"Verify that instance schema is \"none\""
				);
			}
			TEST_METHOD(Parser_Parse_BodyContent_CreateNamedInstance)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens bodyContent;
					{
						bodyContent.push_back(Make<Lexing2::Text>("x"));
						bodyContent.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						bodyContent.push_back(Make<Lexing2::Text>("make"));
						bodyContent.push_back(Make<Lexing2::Text>("none"));
					}

					Lexing2::Container::Tokens schemaContent;
					{
						schemaContent.push_back(Make<Lexing2::Text>("algorithm"));
						schemaContent.push_back(Make<Lexing2::Text>("none"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						schemaContent.push_back(Make<Lexing2::Text>("body"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, bodyContent));
					}

					// input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					// input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, schemaContent));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(markers.front());
				auto &algorithms = schema->GetAlgorithms();
				auto algorithm = algorithms[0];
				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);
				auto body = parser->parenthoodManager->GetBody(braceAlgorithm);
				auto bodyMarkers = body->GetMarkers();
				auto bodyNames = body->GetNames(); // parser->parenthoodManager->GetNames2(body, body, bodyMarkers.end());

				Assert::IsTrue(
					bodyNames.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = bodyNames.find("x");

				Assert::IsTrue(
					nameIt != bodyNames.end(),
					L"Verify that there is name \"x\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto instance = UpCast<Instance>(value);

				Assert::IsTrue(
					instance != nullptr,
					L"Verify that value is Instance"
				);
			}
			TEST_METHOD(Parser_Parse_BodyContent_AlgorithmCallNoResultNoArguments)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens bodyContent;
					{
						bodyContent.push_back(Make<Lexing2::Text>("x"));
						bodyContent.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						bodyContent.push_back(Make<Lexing2::Text>("make"));
						bodyContent.push_back(Make<Lexing2::Text>("X"));
						bodyContent.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
						
						bodyContent.push_back(Make<Lexing2::Text>("x"));
						bodyContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						bodyContent.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					Lexing2::Container::Tokens schemaContent;
					{
						schemaContent.push_back(Make<Lexing2::Text>("algorithm"));
						schemaContent.push_back(Make<Lexing2::Text>("none"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						schemaContent.push_back(Make<Lexing2::Text>("body"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, bodyContent));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("X"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, schemaContent));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				/*auto schema = UpCast<Parsing3::Schema>(markers.front());
				auto &algorithms = schema->GetAlgorithms();
				auto algorithm = algorithms[0];
				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);
				auto body = parser->parenthoodManager->GetBody(braceAlgorithm);
				auto bodyMarkers = body->GetMarkers();
				auto bodyNames = body->GetNames(); // parser->parenthoodManager->GetNames2(body, body, bodyMarkers.end());

				Assert::IsTrue(
					bodyNames.size() == 1,
					L"Verify that there is 1 name"
				);

				auto nameIt = bodyNames.find("x");

				Assert::IsTrue(
					nameIt != bodyNames.end(),
					L"Verify that there is name \"x\""
				);

				auto levels = (*nameIt).second;
				auto levelsIt = levels.find(0);

				Assert::IsTrue(
					levelsIt != levels.end(),
					L"Verify that there is level 0"
				);

				auto name = (*levelsIt).second;
				auto value = parser->parenthoodManager->GetValue(name);
				auto instance = UpCast<Instance>(value);

				Assert::IsTrue(
					instance != nullptr,
					L"Verify that value is Instance"
				);*/
			}

			TEST_METHOD(Parser_Test)
			{
				auto parser = Make<Parser>();
				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens x;
					{
						x.push_back(Make<Lexing2::Text>("make"));
						x.push_back(Make<Lexing2::Text>("none"));
					}

					Lexing2::Container::Tokens nested;
					{
						nested.push_back(Make<Lexing2::Text>("algorithm"));
						nested.push_back(Make<Lexing2::Text>("none"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round));
						nested.push_back(Make<Lexing2::Text>("body"));
						nested.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, x));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, nested));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				// auto &names = output->GetNames();

				auto schema = UpCast<Parsing3::Schema>(markers.front());
				auto &algorithms = schema->GetAlgorithms();
				auto algorithm = algorithms[0];
				auto braceAlgorithm = UpCast<Parsing3::BraceAlgorithm>(algorithm);
				auto algorithmBody = parser->parenthoodManager->GetBody(braceAlgorithm);
				auto algorithmBodyMarkers = algorithmBody->GetMarkers();

				Assert::IsTrue(
					algorithmBodyMarkers.size() == 1,
					L"Verify that body size is 1"
				);

				auto instanceCreationCommand = UpCast<Parsing3::InstanceCreationCommand>(algorithmBodyMarkers.front());

				Assert::IsTrue(
					instanceCreationCommand != nullptr,
					L"Verify that marker is InstanceCreationCommand"
				);
			}
		};

		TEST_CLASS(Regression)
		{
		public:
			TEST_METHOD(Bug01_ParsingContentOfUnnamedSpace)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));

					Lexing2::Container::Tokens x;
					{
						x.push_back(Make<Lexing2::Text>("b"));
						x.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
						x.push_back(Make<Lexing2::Text>("space"));
						x.push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
					}

					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, x));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				auto &names = output->GetNames();

				auto outerSpace = UpCast<Parsing3::Space>(*markers.begin());
				auto &outerSpaceNames = outerSpace->GetNames();

				auto b = parser->parenthoodManager->GetValue(outerSpaceNames["b"][0]);
				
				Assert::IsTrue(
					b != nullptr,
					L"Verify that value is not empty"
				);
			}
			TEST_METHOD(Bug02_MakingSpaceUsingForwardDeclarationKeyword)
			{
				auto parser = Make<Parser>();

				auto input = Make<Lexing2::Container>();
				{
					input->GetTokens().push_back(Make<Lexing2::Text>("x"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));

					input->GetTokens().push_back(Make<Lexing2::Text>("x"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Colon));
					input->GetTokens().push_back(Make<Lexing2::Text>("space"));
					input->GetTokens().push_back(Make<Lexing2::Special>(Lexing2::Special::Value::Semicolon));
				}

				auto output = parser->Parse(input);
				auto &markers = output->GetMarkers();
				
				auto space = UpCast<Parsing3::Space>(*markers.begin());

				Assert::IsTrue(
					space != nullptr,
					L"Verify that value is not empty"
				);
			}
		};

		TEST_CLASS(Test)
		{
			TEST_METHOD(Parser_Test)
			{
				auto parser = Make<Parser>();
				auto input = Make<Lexing2::Container>();
				{
					Lexing2::Container::Tokens algorithmContent;
					{
						algorithmContent.push_back(Make<Lexing2::Text>("copy"));
						algorithmContent.push_back(Make<Lexing2::Text>("none"));
					}

					Lexing2::Container::Tokens schemaContent;
					{
						schemaContent.push_back(Make<Lexing2::Text>("algorithm"));
						schemaContent.push_back(Make<Lexing2::Text>("none"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Round, Lexing2::Group::BraceType::Round, algorithmContent));
						schemaContent.push_back(Make<Lexing2::Text>("body"));
						schemaContent.push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure));
					}

					input->GetTokens().push_back(Make<Lexing2::Text>("schema"));
					input->GetTokens().push_back(Make<Lexing2::Group>(Lexing2::Group::BraceType::Figure, Lexing2::Group::BraceType::Figure, schemaContent));
				}

				auto output = parser->Parse(input);
			}
		};
	}
}