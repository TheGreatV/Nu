#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Parser4/Parser.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Parser4
	{
		using namespace Nu;
		using namespace Parsing4;

		Reference<Lexing2::Container> Tokenize(const String& code_)
		{
			auto lexer = Make<Nu::Lexing2::Lexer>();
			auto container = lexer->Parse(code_);

			return Move(container);
		}
		Lexing2::Container::Tokens Tokenize2(const String& code_)
		{
			auto lexer = Make<Nu::Lexing2::Lexer>();
			auto container = lexer->Parse(code_);

			return container->GetTokens();
		}

		bool IsDelimiter(const Reference<Marker>& marker_)
		{
			if (auto delimiter = UpCast<Markers::Delimiter>(marker_))
			{
				return true;
			}

			return false;
		}
		bool IsText(const Reference<Marker>& marker_, const String& value_)
		{
			if (auto token = UpCast<Markers::Token>(marker_))
			{
				if (auto text = UpCast<Lexing2::Text>(token->GetValue()))
				{
					return text->GetValue() == value_;
				}
			}

			return false;
		}
		bool IsDeclaration(const Reference<Marker>& marker_, const String& value_)
		{
			if (auto declration = UpCast<Markers::Declaration>(marker_))
			{
				return declration->GetValue() == value_;
			}

			return false;
		}
		bool IsGroup(const Reference<Marker>& marker_)
		{
			if (auto group = UpCast<Markers::Group>(marker_))
			{
				return true;
			}

			return false;
		}
		bool IsSpecial(const Reference<Marker>& marker_, const Lexing2::Special::Value& value_)
		{
			if (auto token = UpCast<Markers::Token>(marker_))
			{
				if (auto special = UpCast<Lexing2::Special>(token->GetValue()))
				{
					return special->GetValue() == value_;
				}
			}

			return false;
		}
		bool IsKeyword(const Reference<Marker>& marker_, const Keyword::Value& value_)
		{
			if (auto name = UpCast<Markers::Name>(marker_))
			{
				auto unit = name->GetUnit();

				if (auto keyword = UpCast<Keyword>(unit))
				{
					return keyword->GetValue() == value_;
				}
			}

			return false;
		}
		bool IsSpace(const Reference<Marker>& marker_)
		{
			if (auto spaceDeclaration = UpCast<Markers::SpaceDeclaration>(marker_))
			{
				return true;
			}
			else if (auto name = UpCast<Markers::Name>(marker_))
			{
				auto unit = name->GetUnit();

				if (auto space = UpCast<Scopes::Space>(unit))
				{
					return true;
				}
			}

			return false;
		}
		bool IsSchema(const Reference<Marker>& marker_)
		{
			if (auto schemaDeclaration = UpCast<Markers::SchemaDeclaration>(marker_))
			{
				return true;
			}
			else if (auto name = UpCast<Markers::Name>(marker_))
			{
				auto unit = name->GetUnit();

				if (auto schema = UpCast<Scopes::Schema>(unit))
				{
					return true;
				}
			}

			return false;
		}

		namespace ContextT
		{
			TEST_CLASS(Smoke)
			{
			public:
				TEST_METHOD(MergeNames)
				{
					auto x1 = Make<Markers::Declaration>("x");
					auto x2 = Make<Markers::Declaration>("x");
					auto y1 = Make<Markers::Declaration>("y");
					auto y2 = Make<Markers::Declaration>("y");

					auto e = Context::UnorderedNames();
					auto nx1 = Context::UnorderedNames();
					{
						nx1["x"].push_front(x1);
					}
					auto nx2 = Context::UnorderedNames();
					{
						nx2["x"].push_front(x2);
					}
					auto ny1 = Context::UnorderedNames();
					{
						ny1["y"].push_front(y1);
					}
					auto nx1y1 = Context::UnorderedNames();
					{
						nx1y1["x"].push_front(x1);
						nx1y1["y"].push_front(y1);
					}

					auto r1 = Context::MergeNames(e, e);
					{
						Assert::IsTrue(r1.empty());
					}
					auto r2 = Context::MergeNames(nx1, e);
					{
						Assert::IsTrue(r2.size() == 1);
						Assert::IsTrue(r2["x"].size() == 1);
						Assert::IsTrue(ToVector(r2["x"])[0] == x1);
					}
					auto r3 = Context::MergeNames(e, nx1);
					{
						Assert::IsTrue(r3.size() == 1);
						Assert::IsTrue(r3["x"].size() == 1);
						Assert::IsTrue(ToVector(r3["x"])[0] == x1);
					}
					auto r4 = Context::MergeNames(nx1, ny1);
					{
						Assert::IsTrue(r4.size() == 2);
						Assert::IsTrue(r4["x"].size() == 1);
						Assert::IsTrue(ToVector(r4["x"])[0] == x1);
						Assert::IsTrue(r4["y"].size() == 1);
						Assert::IsTrue(ToVector(r4["y"])[0] == y1);
					}
					auto r5 = Context::MergeNames(nx1, nx2);
					{
						Assert::IsTrue(r5.size() == 1);
						Assert::IsTrue(r5["x"].size() == 2);
						Assert::IsTrue(ToVector(r5["x"])[0] == x1);
						Assert::IsTrue(ToVector(r5["x"])[1] == x2);
					}
				}
			};
		}

		namespace ParserT
		{
			TEST_CLASS(Smoke)
			{
			protected:
				static inline Parser::Output Parse(const String& code_)
				{
					auto container = Tokenize(code_);
					auto parser = Make<Parser>();
					auto output = parser->Parse(container);

					return Move(output);
				}
			public:
				TEST_METHOD(Convert_TokensToMarkers)
				{
					auto tokens = Tokenize2("A: schema { algorithm none() body { a: make A; } }");
					auto markers = ToVector(Parser::Convert(tokens));
					
					Assert::IsTrue(IsDeclaration(markers[0], "A"), L"");
					Assert::IsTrue(IsText(markers[1], "schema"), L"");
					Assert::IsTrue(IsGroup(markers[2]), L"");

					auto markers1 = ToVector(UpCast<Markers::Group>(markers[2])->GetMarkers());

					Assert::IsTrue(IsText(markers1[0], "algorithm"), L"");
					Assert::IsTrue(IsText(markers1[1], "none"), L"");
					Assert::IsTrue(IsGroup(markers1[2]), L"");
					Assert::IsTrue(IsText(markers1[3], "body"), L"");
					Assert::IsTrue(IsGroup(markers1[4]), L"");

					auto markers2 = ToVector(UpCast<Markers::Group>(markers1[4])->GetMarkers());
					
					Assert::IsTrue(IsDeclaration(markers2[0], "a"), L"");
					Assert::IsTrue(IsText(markers2[1], "make"), L"");
					Assert::IsTrue(IsText(markers2[2], "A"), L"");
					Assert::IsTrue(IsDelimiter(markers2[3]), L"");

					// TODO
				}
			public:
				TEST_METHOD(Parse_SingleDelimiter)
				{
					auto context = Parse(";");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 1, L"");

					Assert::IsTrue(IsDelimiter(markers[0]), L"");
				}
				TEST_METHOD(Parse_SeveralDelimiters)
				{
					auto context = Parse(";;");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());
					
					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDelimiter(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
				}
				
				TEST_METHOD(Parse_SingleKeywordAlias_WithoutDelimiter)
				{
					auto context = Parse("x: space");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());
					
					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SingleKeywordAlias_WithDelimiter)
				{
					auto context = Parse("x: space;");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 3, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDelimiter(markers[2]), L"");
				}
				TEST_METHOD(Parse_DoubleForwardKeywordAlias)
				{
					auto context = Parse("x: space y: x");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 4, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_DoubleBackwardKeywordAlias)
				{
					auto context = Parse("x: y y: space");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 4, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_TripleForwardKeywordAlias)
				{
					auto context = Parse("x: space y: x z: y");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 6, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[4], "z"), L"");
					Assert::IsTrue(IsKeyword(markers[5], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_TripleBackwardKeywordAlias)
				{
					auto context = Parse("x: y y: z z: space");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 6, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[4], "z"), L"");
					Assert::IsTrue(IsKeyword(markers[5], Keyword::Value::Space), L"");
				}

				TEST_METHOD(Parse_SingleUnnamedSpaceDeclaration_WithoutDelimiter)
				{
					auto context = Parse("space {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());
					
					Assert::IsTrue(markers.size() == 1, L"");

					Assert::IsTrue(IsSpace(markers[0]), L"");
				}
				TEST_METHOD(Parse_SingleUnnamedSpaceDeclaration_WithDelimiter)
				{
					auto context = Parse("space {};");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsSpace(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
				}
				TEST_METHOD(Parse_DoubleUnnamedSpaceDeclaration_WithoutDelimiter)
				{
					auto context = Parse("space {} space {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsSpace(markers[0]), L"");
					Assert::IsTrue(IsSpace(markers[1]), L"");
				}
				TEST_METHOD(Parse_DoubleUnnamedSpaceDeclaration_WithDelimiter)
				{
					auto context = Parse("space {}; space {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 3, L"");

					Assert::IsTrue(IsSpace(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
					Assert::IsTrue(IsSpace(markers[2]), L"");
				}
				TEST_METHOD(Parse_SingleNamedSpaceDeclaration_WithoutDelimiter)
				{
					auto context = Parse("x: space {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsSpace(markers[1]), L"");
				}

				TEST_METHOD(Parse_SingleUnnamedSchemaDeclaration_WithoutDelimiter)
				{
					auto context = Parse("schema {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 1, L"");

					Assert::IsTrue(IsSchema(markers[0]), L"");
				}
				TEST_METHOD(Parse_SingleUnnamedSchemaDeclaration_WithDelimiter)
				{
					auto context = Parse("schema {};");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsSchema(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
				}
				TEST_METHOD(Parse_DoubleUnnamedSchemaDeclaration_WithoutDelimiter)
				{
					auto context = Parse("schema {} schema {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsSchema(markers[0]), L"");
					Assert::IsTrue(IsSchema(markers[1]), L"");
				}
				TEST_METHOD(Parse_DoubleUnnamedSchemaDeclaration_WithDelimiter)
				{
					auto context = Parse("schema {}; schema {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 3, L"");

					Assert::IsTrue(IsSchema(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
					Assert::IsTrue(IsSchema(markers[2]), L"");
				}
				TEST_METHOD(Parse_SingleNamedSchemaDeclaration_WithoutDelimiter)
				{
					auto context = Parse("x: schema {}");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsSchema(markers[1]), L"");
				}
			public:
				TEST_METHOD(Parse_Keyword_Space)
				{
					auto context = Parse("x: space");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_Keyword_Schema)
				{
					auto context = Parse("x: schema");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Schema), L"");
				}
				TEST_METHOD(Parse_Keyword_Algorithm)
				{
					auto context = Parse("x: algorithm");
					auto root = context->GetRoot();

					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Algorithm), L"");
				}
			public:
				TEST_METHOD(Parse_SpaceContent_SingleDelimiter)
				{
					auto context = Parse("space {;}");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());
					
					Assert::IsTrue(markers.size() == 1, L"");
					
					Assert::IsTrue(IsDelimiter(markers[0]), L"");
				}
				TEST_METHOD(Parse_SpaceContent_DoubleDelimiter)
				{
					auto context = Parse("space {;;}");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDelimiter(markers[0]), L"");
					Assert::IsTrue(IsDelimiter(markers[1]), L"");
				}

				TEST_METHOD(Parse_SpaceContent_SingleKeywordAlias_WithoutDelimiter)
				{
					auto context = Parse("space { x: space }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 2, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SpaceContent_SingleKeywordAlias_WithDelimiter)
				{
					auto context = Parse("space { x: space; }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 3, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDelimiter(markers[2]), L"");
				}
				TEST_METHOD(Parse_SpaceContent_DoubleForwardKeywordAlias)
				{
					auto context = Parse("space { x: space y: x }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 4, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SpaceContent_DoubleBackwardKeywordAlias)
				{
					auto context = Parse("space { x: y y: space }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 4, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SpaceContent_TripleForwardKeywordAlias)
				{
					auto context = Parse("space { x: space y: x z: y }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 6, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[4], "z"), L"");
					Assert::IsTrue(IsKeyword(markers[5], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SpaceContent_TripleBackwardKeywordAlias)
				{
					auto context = Parse("space { x: y y: z z: space }");
					auto root = context->GetRoot();
					auto rootMarkers = ToVector(root->GetMarkers());
					auto space = UpCast<Markers::SpaceDeclaration>(rootMarkers[0])->GetSpace();
					auto markers = ToVector(space->GetMarkers());

					Assert::IsTrue(markers.size() == 6, L"");

					Assert::IsTrue(IsDeclaration(markers[0], "x"), L"");
					Assert::IsTrue(IsKeyword(markers[1], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[2], "y"), L"");
					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
					Assert::IsTrue(IsDeclaration(markers[4], "z"), L"");
					Assert::IsTrue(IsKeyword(markers[5], Keyword::Value::Space), L"");
				}
			public:
				TEST_METHOD(Parse_SpaceAccess_SingleNestedElement_ForwardAccess)
				{
					auto context = Parse("x: space { y: space } a: x.y");
					auto root = context->GetRoot();
					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
				TEST_METHOD(Parse_SpaceAccess_DoubleNestedElement_ForwardAccess)
				{
					auto context = Parse("x: space { y: space { z: space } } a: x.y.z");
					auto root = context->GetRoot();
					auto markers = ToVector(root->GetMarkers());

					Assert::IsTrue(IsKeyword(markers[3], Keyword::Value::Space), L"");
				}
			};
		}
	}
}