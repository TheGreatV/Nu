#pragma once

#pragma region Include

#include <regex>

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Cleaning
	{
		class Cleaner;


		class Cleaner:
			public This<Cleaner>
		{
		public:
			using Content = String;
		public:
			const String COMMENT_OPENING	= "`\\";
			const String COMMENT_CLOSING	= "\\`";
		public:
			inline Cleaner(const Reference<Cleaner>& this_);
		public:
			inline Content Parse(const Content& source_);
		};
	}
}


#pragma region Nu

#pragma region Cleaner

inline Nu::Cleaning::Cleaner::Cleaner(const Reference<Cleaner>& this_):
	This(this_)
{
}

inline Nu::Cleaning::Cleaner::Content Nu::Cleaning::Cleaner::Parse(const Content& source_)
{
	auto source = std::regex_replace(source_, std::regex("`/.*(\n|$)"), "");

	Size nestingLevel = 0;
	Size i = 0;
	Size commentStart = 0;

	while(i < source.size())
	{
		auto opening = source.find(COMMENT_OPENING, i);
		auto closing = source.find(COMMENT_CLOSING, i);
		if(opening < source.size() && (!(closing < source.size()) || opening < closing))
		{
			if(nestingLevel == 0)
			{
				commentStart = opening;
			}

			++nestingLevel;
			i = opening + COMMENT_OPENING.size();
		}
		else if(closing < source.size())
		{
			if(nestingLevel > 0)
			{
				--nestingLevel;

				if(nestingLevel == 0)
				{
					auto commentEnd = closing + COMMENT_CLOSING.size();
					source = source.substr(0, commentStart) + source.substr(commentEnd, source.size() - commentEnd);
					i = commentStart;
				}
				else
				{
					i = closing + COMMENT_CLOSING.size();
				}
			}
			else
			{
				throw Exception("Invalid number of comment block closings");
			}
		}
		else
		{
			break;
		}
	}

	if(nestingLevel > 0)
	{
		throw Exception("Invalid number of comment block closings");
	}

	/*Size nesting = 0;
	Size i = 0;
	Size l;

	while(i < source.length())
	{
		i = source.find(COMMENT_BEGIN, i);

		if(i < source.length())
		{
			if(nesting == 0)
			{
				l = i;
			}

			++nesting;

			auto j = source.find(COMMENT_END, i + 1);
			auto i2 = source.find(COMMENT_BEGIN, i + 1);

			if(j < source.length())
			{
				if(i2 < source.length())
				{
					if(j < i2)
					{
						--nesting; // 'nesting' at least > 0 here
						// TODO: cut content
					}
					else
					{
						i = i + 1;
						continue;
					}
				}
				else
				{
					--nesting; // 'nesting' at least > 0 here

					if(nesting == 0)
					{
						auto k = j + COMMENT_END.size();
						source =
							source.substr(0, l) + 
							source.substr(k, source.size() - k);
						i = l;
						break;
					}
					else
					{
						throw Exception("Not enough comment block closings");
					}
				}
			}
			else
			{
				throw Exception("Not enclosed comment");
			}
		}
		else
		{
			if(nesting == 0)
			{
				break;
			}
			else
			{
				throw Exception("Invalid count of comment blocks closing");
			}
		}
	}*/

	return Move(source);
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















