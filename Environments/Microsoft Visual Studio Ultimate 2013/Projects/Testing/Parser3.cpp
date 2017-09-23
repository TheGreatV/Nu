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
			TEST_METHOD(ScopeEmpty)
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
			TEST_METHOD(ScopeSingleName)
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
			TEST_METHOD(ScopeDuplicatedName)
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
			TEST_METHOD(ScopeSeveralNames)
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
			TEST_METHOD(ScopeDuplicatedNameWithOtherNameBetween)
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
			TEST_METHOD(ParenthoodManagerEmpty)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto scope1 = Make<Parsing3::Scope>();

				auto parent = parenthoodManager->GetParent(scope1);

				Assert::IsTrue(
					parent == nullptr,
					L"Verify that parent is nullptr"
				);

				auto names = parenthoodManager->GetNames(scope1);

				Assert::IsTrue(
					names.empty(),
					L"Verify that names is empty"
				);
			}
			/* Requirement: TODO
			 */
			TEST_METHOD(ParenthoodManagerUnitParent)
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
			}
			/* Requirement: TODO
			 */
			TEST_METHOD(ParenthoodManagerSingleScopeNames)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto scope1 = Make<Parsing3::Scope>();

				auto nameValue1 = "a";
				auto name1 = scope1->Add(nameValue1);
				auto nameValue2 = "b";
				auto name2 = scope1->Add(nameValue2);
				{
					auto names = parenthoodManager->GetNames(scope1);

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
				auto name3 = scope1->Add(nameValue3);
				{
					auto names = parenthoodManager->GetNames(scope1);

					Assert::IsTrue(
						names[nameValue1][1] == name1,
						L"Verify that name is as expected"
					);
					Assert::IsTrue(
						names[nameValue3][0] == name3,
						L"Verify that name is as expected"
					);
				}
			}
			/* Requirement: TODO
			 */
			TEST_METHOD(ParenthoodManagerTwoNestedScopeNames)
			{
				auto parenthoodManager = Make<ParenthoodManager>();
				auto scope1 = Make<Parsing3::Scope>();
				auto scope2 = Make<Parsing3::Scope>();
				{
					parenthoodManager->SetParent(scope2, scope1);
				}

				auto nameValue1 = "a";
				auto name1 = scope1->Add(nameValue1);
				auto nameValue2 = "b";
				auto name2 = scope1->Add(nameValue2);
				auto nameValue3 = nameValue1;
				auto name3 = scope1->Add(nameValue3);
				{
					auto names = parenthoodManager->GetNames(scope2);

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
				auto name4 = scope1->Add(nameValue4);
				auto nameValue5 = nameValue2;
				auto name5 = scope1->Add(nameValue5);
				{
					auto names = parenthoodManager->GetNames(scope2);

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
			}
		};
	}
}