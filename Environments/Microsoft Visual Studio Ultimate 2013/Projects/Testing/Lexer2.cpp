#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Lexer2/Lexer.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Lexer2
	{
		using namespace Nu;
		using namespace Lexing2;

		Lexer::Output Parse(const Lexer::Input& input_)
		{
			auto lexer = Make<Lexer>();
			auto output = lexer->Parse(input_);

			return Move(output);
		}

		TEST_CLASS(Smoke)
		{
		public:
			TEST_METHOD(Empty)
			{
				auto lexer = Make<Lexer>();

				Lexer::Input input =
					""
					;

				auto output = lexer->Parse(input);

				auto &tokens = output->GetTokens();

				Assert::IsTrue(
					tokens.size() == 0,
					L"Verify that tokens are empty"
				);
			}
		public:
			TEST_METHOD(SingleText)
			{
				Text::Value textAbc = "abc";
				{
					Lexer::Input input =
						"abc"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
						);

					auto token = tokens[0];
					auto text = UpCast<Text>(token);

					Assert::IsTrue(
						text != nullptr,
						L"Verify that token is Text"
						);

					auto textValue = text->GetValue();

					Assert::IsTrue(
						textValue == textAbc,
						L"Verify that Text Value is \"abc\""
					);
				}

				Text::Value textSymbols = "!@#";
				{
					Lexer::Input input =
						"!@#"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto text = UpCast<Text>(token);

					Assert::IsTrue(
						text != nullptr,
						L"Verify that token is Text"
					);

					auto textValue = text->GetValue();

					Assert::IsTrue(
						textValue == textSymbols,
						L"Verify that Text Value is \"!@#\""
					);
				}
			}
			TEST_METHOD(SingleSpecial)
			{
				auto specialDot = Special::Value::Dot;
				{
					Lexer::Input input =
						"."
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto special = UpCast<Special>(token);

					Assert::IsTrue(
						special != nullptr,
						L"Verify that token is Special"
					);

					auto specialValue = special->GetValue();

					Assert::IsTrue(
						specialValue == specialDot,
						L"Verify that Special Value is Dot"
					);
				}
				
				auto specialComma = Special::Value::Comma;
				{
					Lexer::Input input =
						","
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto special = UpCast<Special>(token);

					Assert::IsTrue(
						special != nullptr,
						L"Verify that token is Special"
					);

					auto specialValue = special->GetValue();

					Assert::IsTrue(
						specialValue == specialComma,
						L"Verify that Special Value is Comma"
					);
				}

				auto specialColon = Special::Value::Colon;
				{
					Lexer::Input input =
						":"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto special = UpCast<Special>(token);

					Assert::IsTrue(
						special != nullptr,
						L"Verify that token is Special"
					);

					auto specialValue = special->GetValue();

					Assert::IsTrue(
						specialValue == specialColon,
						L"Verify that Special Value is Colon"
					);
				}

				auto specialSemicolon = Special::Value::Semicolon;
				{
					Lexer::Input input =
						";"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto special = UpCast<Special>(token);

					Assert::IsTrue(
						special != nullptr,
						L"Verify that token is Special"
					);

					auto specialValue = special->GetValue();

					Assert::IsTrue(
						specialValue == specialSemicolon,
						L"Verify that Special Value is Semicolon"
					);
				}
			}
			TEST_METHOD(SingleGroup)
			{
				std::tuple<Group::BraceType> groupFigure;
				{
					Lexer::Input input =
						"{}"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto group = UpCast<Group>(token);

					Assert::IsTrue(
						group != nullptr,
						L"Verify that token is Group"
					);

					auto opening = group->GetOpening();
					
					Assert::IsTrue(
						opening == Group::BraceType::Figure,
						L"Verify that opening brace is Figure"
					);

					auto closing = group->GetClosing();
					
					Assert::IsTrue(
						closing == Group::BraceType::Figure,
						L"Verify that closing brace is Figure"
					);
				}

				std::tuple<Group::BraceType> groupRound;
				{
					Lexer::Input input =
						"()"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto group = UpCast<Group>(token);

					Assert::IsTrue(
						group != nullptr,
						L"Verify that token is Group"
					);

					auto opening = group->GetOpening();
					
					Assert::IsTrue(
						opening == Group::BraceType::Round,
						L"Verify that opening brace is Rounds"
					);

					auto closing = group->GetClosing();
					
					Assert::IsTrue(
						closing == Group::BraceType::Round,
						L"Verify that closing brace is Round"
					);
				}

				std::tuple<Group::BraceType> groupSquare;
				{
					Lexer::Input input =
						"[]"
						;

					auto output = Parse(input);

					auto &tokens = output->GetTokens();

					Assert::IsTrue(
						tokens.size() == 1,
						L"Verify that there is 1 token"
					);

					auto token = tokens[0];
					auto group = UpCast<Group>(token);

					Assert::IsTrue(
						group != nullptr,
						L"Verify that token is Group"
					);

					auto opening = group->GetOpening();
					
					Assert::IsTrue(
						opening == Group::BraceType::Square,
						L"Verify that opening brace is Square"
					);

					auto closing = group->GetClosing();
					
					Assert::IsTrue(
						closing == Group::BraceType::Square,
						L"Verify that closing brace is Square"
					);
				}
			}
		public:
			TEST_METHOD(SingleGroupWithSingleContent)
			{
				Lexer::Input input =
					"{abc}"
					;

				auto output = Parse(input);

				auto &tokens = output->GetTokens();
				auto token = tokens[0];
				auto group = UpCast<Group>(token);

				auto &groupTokens = group->GetTokens();

				Assert::IsTrue(
					groupTokens.size() == 1,
					L"Verify that group has exactly 1 token"
				);

				auto groupToken1 = groupTokens[0];
				{
					auto groupTokenText = UpCast<Text>(groupToken1);

					Assert::IsTrue(
						groupTokenText != nullptr,
						L"Verify that group token is Text"
					);

					auto groupTokenTextValue = groupTokenText->GetValue();

					Assert::IsTrue(
						groupTokenTextValue == "abc",
						L"Verify that group token Value is \"abc\""
					);
				}
			}
			TEST_METHOD(SingleGroupWithMultipleContent)
			{
				Lexer::Input input = Lexer::Input() +
					"{" +
					"	a: space {" +
					"	};" +
					"}"
					;

				auto output = Parse(input);

				auto &tokens = output->GetTokens();
				auto token = tokens[0];
				auto group = UpCast<Group>(token);

				auto &groupTokens = group->GetTokens();

				Assert::IsTrue(
					groupTokens.size() == 5,
					L"Verify that group has exactly 5 tokens"
				);

				auto groupToken1 = groupTokens[0];
				{
					auto groupTokenText = UpCast<Text>(groupToken1);

					Assert::IsTrue(
						groupTokenText != nullptr,
						L"Verify that group token is Text"
					);

					auto groupTokenTextValue = groupTokenText->GetValue();

					Assert::IsTrue(
						groupTokenTextValue == "a",
						L"Verify that group token Value is \"a\""
					);
				}
				auto groupToken2 = groupTokens[1];
				{
					auto groupTokenSpecial = UpCast<Special>(groupToken2);

					Assert::IsTrue(
						groupTokenSpecial != nullptr,
						L"Verify that group token is Special"
					);

					auto groupTokenSpecialValue = groupTokenSpecial->GetValue();

					Assert::IsTrue(
						groupTokenSpecialValue == Special::Value::Colon,
						L"Verify that group token Value is Colon"
					);
				}
				auto groupToken3 = groupTokens[2];
				{
					auto groupTokenText = UpCast<Text>(groupToken3);

					Assert::IsTrue(
						groupTokenText != nullptr,
						L"Verify that group token is Text"
					);

					auto groupTokenTextValue = groupTokenText->GetValue();

					Assert::IsTrue(
						groupTokenTextValue == "space",
						L"Verify that group token Value is \"space\""
					);
				}
				auto groupToken4 = groupTokens[3];
				{
					auto groupTokenGroup = UpCast<Group>(groupToken4);

					Assert::IsTrue(
						groupTokenGroup != nullptr,
						L"Verify that group token is Group"
					);

					auto &groupTokenGroupTokens = groupTokenGroup->GetTokens();
					{
						auto size = groupTokenGroupTokens.size();

						Assert::IsTrue(
							size == 0,
							L"Verify that group token has no content"
						);
					}
				}
				auto groupToken5 = groupTokens[4];
				{
					auto groupTokenSpecial = UpCast<Special>(groupToken5);

					Assert::IsTrue(
						groupTokenSpecial != nullptr,
						L"Verify that group token is Special"
					);

					auto groupTokenSpecialValue = groupTokenSpecial->GetValue();

					Assert::IsTrue(
						groupTokenSpecialValue == Special::Value::Semicolon,
						L"Verify that group token Value is Semicolon"
					);
				}
			}
		};
	}
}