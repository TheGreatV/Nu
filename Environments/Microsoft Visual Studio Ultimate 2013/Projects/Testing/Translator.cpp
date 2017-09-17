#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Translator/Translator.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Translator
	{
		using namespace Nu;

		const String SPACE_NAME = "space";
		const String MAIN_SPACE_NAME = "<main>";

		inline Nu::Translator::Output Translate(const Nu::Translator::Input& input_)
		{
			auto translator = Make<Nu::Translator>();
			auto output = Move(translator->Translate(input_));

			return output;
		}
		inline Reference<Space> ExtractMain(const Nu::Translator::Output& output_)
		{
			auto names = output_->GetNames();
			auto mainSpaceNameSearchResult = std::find_if(names.begin(), names.end(), [](const Reference<Name>& x) { return x->GetValue() == MAIN_SPACE_NAME; });
			auto mainSpaceUnit = (*mainSpaceNameSearchResult)->GetUnit();
			auto mainSpace = UpCast<Space>(mainSpaceUnit);

			return mainSpace;
		}
		inline Reference<Unit> ExtractUnit(const Reference<Scope>& scope_, const Name::Value& nameValue_)
		{
			auto names = scope_->GetNames();
			auto nameSearchResult = std::find_if(names.begin(), names.end(), [&](const Reference<Name>& x) { return x->GetValue() == nameValue_; });
			auto unit = (*nameSearchResult)->GetUnit();

			return unit;
		}

		TEST_CLASS(Smoke)
		{
		public:
			TEST_METHOD(GeneralScopeContent)
			{
				auto translator = Make<Nu::Translator>();

				Nu::Translator::Input input = String() +
					"";

				auto root = Move(translator->Translate(input));

				Assert::IsTrue(
					root != nullptr,
					L"Verify that output is not a nullptr"
				);

				auto names = root->GetNames();

				SPACE_NAME;
				{
					auto spaceNameCounter = std::count_if(names.begin(), names.end(), [](const Reference<Name>& x) { return x->GetValue() == SPACE_NAME; });

					Assert::IsTrue(
						spaceNameCounter == 1,
						L"Verify that general scope contains only one Name \"space\""
					);

					auto spaceNameSearchResult = std::find_if(names.begin(), names.end(), [](const Reference<Name>& x) { return x->GetValue() == SPACE_NAME; });
					auto spaceUnit = (*spaceNameSearchResult)->GetUnit();
					auto spaceKeyword = UpCast<Keyword>(spaceUnit);

					Assert::IsTrue(
						spaceKeyword != nullptr,
						L"Verify that unit of \"space\" Name is a Keyword"
					);

					auto spaceKeywordType = spaceKeyword->GetType();

					Assert::IsTrue(
						spaceKeywordType == Keyword::Type::Space,
						L"Verify that unit type of \"space\" Name is Space"
					);
				}

				MAIN_SPACE_NAME;
				{
					auto mainSpaceNameCounter = std::count_if(names.begin(), names.end(), [](const Reference<Name>& x) { return x->GetValue() == MAIN_SPACE_NAME; });

					Assert::IsTrue(
						mainSpaceNameCounter == 1,
						L"Verify that general scope contains only one Name \"<main>\""
					);

					auto mainSpaceNameSearchResult = std::find_if(names.begin(), names.end(), [](const Reference<Name>& x) { return x->GetValue() == MAIN_SPACE_NAME; });
					auto mainSpaceUnit = (*mainSpaceNameSearchResult)->GetUnit();
					auto mainSpace = UpCast<Space>(mainSpaceUnit);

					Assert::IsTrue(
						mainSpace != nullptr,
						L"Verify that unit of \"<main>\" Name is a Space"
					);
				}
			}
			TEST_METHOD(SingleSpaceDeclaration)
			{
				Name::Value aName = "a";

				Nu::Translator::Input input = String() +
					"a: space {};";

				auto output = Move(Translate(input));
				auto main = Move(ExtractMain(output));

				auto names = main->GetNames();

				auto aNameCounter = std::count_if(names.begin(), names.end(), [&](const Reference<Name>& x) { return x->GetValue() == aName; });

				Assert::IsTrue(
					aNameCounter == 1,
					L"Verify that general scope contains only one Name \"a\""
				);

				auto aNameSearchResult = std::find_if(names.begin(), names.end(), [&](const Reference<Name>& x) { return x->GetValue() == aName; });
				auto aUnit = (*aNameSearchResult)->GetUnit();
				auto a = UpCast<Space>(aUnit);

				Assert::IsTrue(
					a != nullptr,
					L"Verify that unit of \"a\" Name is a Space"
				);
			}
		};
	}
}